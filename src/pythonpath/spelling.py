import os
from typing import Mapping
import logging
import ctypes
import os.path
from typing import Mapping, List

import unohelper  # type: ignore
from com.sun.star.linguistic2 import XSpellChecker, XLinguServiceEventBroadcaster, XSpellAlternatives  # type: ignore
from com.sun.star.linguistic2.SpellFailure import SPELLING_ERROR  # type: ignore
from com.sun.star.lang import (  # type: ignore
    XServiceInfo, # type: ignore
    XInitialization, # type: ignore
    XServiceDisplayName, # type: ignore
    IllegalArgumentException, # type: ignore
    Locale, # type: ignore
)
import utils

logging.info("Loading divvunspell")

# Import the dylib
try:
    lib = ctypes.CDLL(utils.native_lib_path("libdivvunspell"))
except Exception as e:
    print("Failed to load %s" % utils.native_lib_path("libdivvunspell"))
    raise e
lib.divvun_speller_archive_open.restype = utils.TraitObjectPointer
lib.divvun_speller_archive_speller.restype = utils.TraitObjectPointer
lib.divvun_speller_is_correct.restype = ctypes.c_ubyte
lib.divvun_speller_suggest.restype = utils.SlicePointer
lib.divvun_vec_suggestion_len.restype = ctypes.c_ulong
lib.divvun_vec_suggestion_get_value.restype = utils.StringPointer


_last_error = None


def assert_no_error():
    global _last_error
    if _last_error is not None:
        e = _last_error
        _last_error = None
        raise utils.ForeignFuncError(e)

@ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p)
def error_callback(error: ctypes.c_void_p, size: ctypes.c_void_p):
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
            res = lib.divvun_vec_suggestion_get_value(suggs, ctypes.c_long(i), error_callback)
            assert_no_error()
            out.append(str(res))
        return out

logging.info("Loaded divvunspell")

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
        return utils.get_locales(self.speller_paths)

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
    