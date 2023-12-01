import os
from typing import Mapping, Optional, NewType
import logging
import json

logging.basicConfig(filename='/tmp/divvunspell-libreoffice.log', level=logging.DEBUG)

import utils # type: ignore

import uno # type: ignore
import unohelper  # type: ignore
from com.sun.star.linguistic2 import XSpellChecker, XLinguServiceEventBroadcaster, XSpellAlternatives, XProofreader, XSupportedLocales  # type: ignore
from com.sun.star.linguistic2.SpellFailure import SPELLING_ERROR  # type: ignore
from com.sun.star.lang import (  # type: ignore
    XServiceInfo, # type: ignore
    XInitialization, # type: ignore
    XServiceDisplayName, # type: ignore
    IllegalArgumentException, # type: ignore
    Locale, # type: ignore
    XServiceName, # type: ignore
)
from com.sun.star.text.TextMarkupType import PROOFREADING # type: ignore

logging.info("Loading divvunspell")

# This is a ctypes wrapper around the native DivvunSpell libraries build with
# FFI support enabled.

import ctypes
import os.path
from ctypes import (
    CDLL,
    CFUNCTYPE,
    c_long,
    c_ubyte,
    c_ulong,
    c_void_p,
    c_char_p,
)
from typing import List

with open(utils.locales_json_path(__file__)) as f:
    LOCALES = json.load(f)

# Time to import the dylib and hook things
try:
    lib = CDLL(utils.native_lib_path(__file__, "libdivvunspell"))
except Exception as e:
    print("Failed to load %s" % utils.native_lib_path(__file__, "libdivvunspell"))
    raise e
lib.divvun_speller_archive_open.restype = utils.TraitObjectPointer
lib.divvun_speller_archive_speller.restype = utils.TraitObjectPointer
lib.divvun_speller_is_correct.restype = c_ubyte
lib.divvun_speller_suggest.restype = utils.SlicePointer
lib.divvun_vec_suggestion_len.restype = c_ulong
lib.divvun_vec_suggestion_get_value.restype = utils.StringPointer


_last_error = None


def assert_no_error():
    global _last_error
    if _last_error is not None:
        e = _last_error
        _last_error = None
        raise utils.ForeignFuncError(e)

@CFUNCTYPE(c_void_p, c_void_p, c_void_p)
def error_callback(error: c_void_p, size: c_void_p):
    global _last_error
    _last_error = str(utils.StringPointer(error, size))

class SpellerArchive:
    @staticmethod
    def open(path: str):
        b_path = utils.PathPointer.from_path(path)
        handle = lib.divvun_speller_archive_open(b_path, error_callback)
        assert_no_error()
        return SpellerArchive(handle)

    def __init__(self, handle: utils.TraitObjectPointer):
        if not isinstance(handle, utils.TraitObjectPointer):
            raise TypeError("Invalid handle, got: %r" % type(handle))
        self._handle = handle

    def __del__(self):
        # TODO: there's no freeing functions for this, haha oh no
        pass

    def speller(self):
        handle = lib.divvun_speller_archive_speller(self._handle, error_callback)
        assert_no_error()
        return Speller(handle)


class Speller:
    def __init__(self, handle: utils.TraitObjectPointer):
        if not isinstance(handle, utils.TraitObjectPointer):
            raise TypeError("Invalid handle, got: %r" % type(handle))
        self._handle = handle

    def __del__(self):
        # TODO: there's no freeing functions for this, haha oh no
        pass

    def is_correct(self, input: str) -> bool:
        b_str = utils.StringPointer.from_str(input)
        res = lib.divvun_speller_is_correct(self._handle, b_str, error_callback)
        assert_no_error()
        return res != 0

    def suggest(self, input: str) -> List[str]:
        b_str = utils.StringPointer.from_str(input)
        suggs = lib.divvun_speller_suggest(self._handle, b_str, error_callback)
        assert_no_error()

        vec_len = lib.divvun_vec_suggestion_len(suggs, error_callback)
        assert_no_error()

        out = []
        for i in range(0, vec_len):
            res = lib.divvun_vec_suggestion_get_value(suggs, c_long(i), error_callback)
            assert_no_error()
            out.append(str(res))
        return out

logging.info("Loaded divvunspell")


logging.info("Loading divvunruntime")

try:
    divvun_runtime = ctypes.CDLL(utils.native_lib_path(__file__, "libdivvun_runtime"))
except Exception as e:
    logging.info(e)
    raise e
divvun_runtime.bundle_load.argtypes = [ctypes.c_char_p]
divvun_runtime.bundle_load.restype = ctypes.c_void_p
divvun_runtime.bundle_run_pipeline.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
divvun_runtime.bundle_run_pipeline.restype = ctypes.c_char_p
logging.info("Loading bundle...")
bundle = divvun_runtime.bundle_load(utils.box_path(__file__, "sme").encode("utf-8"))
logging.info("Bundle loaded")

logging.info("Loaded divvun_runtime")

# -------- SPELL CHECKER --------
class SpellAlternatives(unohelper.Base, XSpellAlternatives):
    def __init__(self, word, alternatives, locale):
        self.word = word
        self.alternatives = alternatives
        self.locale = locale

    def getWord(self):
        return self.word

    def getLocale(self):
        return self.locale

    def getFailureType(self):
        return SPELLING_ERROR

    def getAlternativesCount(self):
        return len(self.alternatives)

    def getAlternatives(self):
        return tuple(self.alternatives)


class SpellChecker(
    unohelper.Base,
    XServiceInfo,
    XSpellChecker,
    XLinguServiceEventBroadcaster,
    XInitialization,
    XServiceDisplayName,
):
    IMPLEMENTATION_NAME = "no.divvun.DivvunSpell"
    SUPPORTED_SERVICE_NAMES = ("com.sun.star.linguistic2.SpellChecker",)

    def __init__(self, ctx, *args):
        logging.info("Init happened")
        self.speller_paths: Mapping[utils.Bcp47Tag, os.PathLike] = utils.find_spellers()
        self.spellers: Mapping[Locale, Speller] = {}

    # XServiceInfo
    def getImplementationName(self):
        return SpellChecker.IMPLEMENTATION_NAME

    # XServiceInfo
    def supportsService(self, serviceName):
        return serviceName in self.getSupportedServiceNames()

    # XServiceInfo
    def getSupportedServiceNames(self):
        return SpellChecker.SUPPORTED_SERVICE_NAMES

    # XSupportedLocales
    def getLocales(self):
        return utils.get_locales(LOCALES, self.speller_paths)

    # XSupportedLocales
    def hasLocale(self, locale: Locale):
        return utils.has_locale(self.speller_paths, locale)

    # XSpellChecker
    def isValid(self, word: str, locale: Locale, properties):
        if not self.hasLocale(locale):
            raise IllegalArgumentException(locale)

        tag = utils.bcp47_tag(locale)
        speller = self.speller(tag)

        return speller.is_correct(word)

    # XSpellChecker
    def spell(self, word: str, locale: Locale, properties):
        if not self.hasLocale(locale):
            raise IllegalArgumentException(locale)

        tag = utils.bcp47_tag(locale)
        speller = self.speller(tag)

        results = speller.suggest(word)
        return SpellAlternatives(word, results, locale)

    # XLinguServiceEventBroadcaster
    def addLinguServiceEventListener(self, xLstnr):
        return False

    # XLinguServiceEventBroadcaster
    def removeLinguServiceEventListener(self, xLstnr):
        return False

    # XInitialization
    def initialize(self, arguments):
        # This seems to literally never get called.
        pass

    # XServiceDisplayName
    def getServiceDisplayName(self, locale):
        return "DivvunSpell"

    def speller(self, tag: utils.Bcp47Tag):
        base_tag = tag.split("-")[0]
        if tag not in self.speller_paths and base_tag not in self.speller_paths:
            raise IllegalArgumentException(tag)

        if tag not in self.speller_paths:
            tag = base_tag

        if tag not in self.spellers:
            ar = SpellerArchive.open(self.speller_paths[tag])
            self.spellers[tag] = ar.speller()

        return self.spellers[tag]

# -------- GRAMMAR CHECKER --------
class GrammarChecker( unohelper.Base, XProofreader, XServiceInfo, XServiceName, XServiceDisplayName, XSupportedLocales):
    IMPLEMENTATION_NAME = "no.divvun.DivvunGrammar"
    SUPPORTED_SERVICE_NAMES = ("com.sun.star.linguistic2.Proofreader",)

    def __init__( self, ctx, *args ):
        logging.info("Grammar checker init")
        self.speller_paths: Mapping[utils.Bcp47Tag, os.PathLike] = utils.find_spellers()

    # XProofreader
    def isSpellChecker(self):
        return False

    # XProofreader
    def doProofreading(self, docId, text, locale, startOfSentencePos, suggestedSentenceEndPos, properties):
        logging.info("Proofreading paragraph")
        result = uno.createUnoStruct("com.sun.star.linguistic2.ProofreadingResult")
        result.aDocumentIdentifier = docId
        result.aText = text
        result.aLocale = locale
        result.nStartOfSentencePosition = startOfSentencePos
        result.nStartOfNextSentencePosition = suggestedSentenceEndPos
        result.aProperties = ()
        result.xProofreader = self
        result.aErrors = ()

        logging.info("Running pipeline...")
        res = divvun_runtime.bundle_run_pipeline(c_void_p(bundle).value, text.encode("utf-8"))
        logging.info("Pipeline finished")

        bytes = c_char_p(res).value
        logging.info(bytes)
        grammarErrors = []
        if bytes:
            data = json.loads(bytes.decode())

            for err in data["errs"]:
                grammarErr = uno.createUnoStruct("com.sun.star.linguistic2.SingleProofreadingError")
                grammarErr.nErrorStart = err[1]
                grammarErr.nErrorLength = err[2] - err[1]
                grammarErr.nErrorType = PROOFREADING
                grammarErr.aRuleIdentifier = err[3]
                grammarErr.aShortComment = err[4]
                grammarErr.aSuggestions = err[5]

                grammarErrors.append(grammarErr)

        result.aErrors = tuple(grammarErrors) # All grammar errors

        return result

    # XProofreader
    def ignoreRule(self, ruleId, locale):
        # TODO: Save ignored rules
        logging.info("Ignore rule")

    # XProofreader
    def resetIgnoreRules(self):
        # TODO: Clear ignored rules
        logging.info("Reset ignore rules")

    # XSupportedLocales
    def getLocales(self):
        return utils.get_locales(LOCALES, self.speller_paths)

    # XSupportedLocales
    def hasLocale(self, locale: Locale):
        return utils.has_locale(self.speller_paths, locale)

    # XServiceName
    def getServiceName(self):
        return GrammarChecker.IMPLEMENTATION_NAME

    # XServiceInfo
    def getImplementationName (self):
        return GrammarChecker.IMPLEMENTATION_NAME

    # XServiceInfo
    def supportsService(self, name):
        return (name in self.getSupportedServiceNames())
    # XServiceInfo
    def getSupportedServiceNames (self):
        return self.SUPPORTED_SERVICE_NAMES

    # XServiceDisplayName
    def getServiceDisplayName(self, locale):
        return "DivvunGrammar"

# -------- REGISTER SERVICES --------
try:
    g_ImplementationHelper = unohelper.ImplementationHelper()
    g_ImplementationHelper.addImplementation(
        SpellChecker, SpellChecker.IMPLEMENTATION_NAME, SpellChecker.SUPPORTED_SERVICE_NAMES
    )
    g_ImplementationHelper.addImplementation(
        GrammarChecker, GrammarChecker.IMPLEMENTATION_NAME, GrammarChecker.SUPPORTED_SERVICE_NAMES
    )
except Exception as e:
    logging.error(e)
