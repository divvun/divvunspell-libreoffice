import os
from typing import Mapping
import logging
import json
import ctypes
import os.path
from ctypes import (
    c_void_p,
    c_char_p,
)

import uno # type: ignore
import unohelper  # type: ignore
from com.sun.star.linguistic2 import XProofreader, XSupportedLocales  # type: ignore
from com.sun.star.lang import (  # type: ignore
    XServiceInfo, # type: ignore
    XServiceDisplayName, # type: ignore
    Locale, # type: ignore
    XServiceName, # type: ignore
)
from com.sun.star.text.TextMarkupType import PROOFREADING # type: ignore
import utils

logging.info("Loading divvunruntime")
try:
    divvun_runtime = ctypes.CDLL(utils.native_lib_path("libdivvun_runtime"))
except Exception as e:
    logging.info(e)
    raise e
divvun_runtime.bundle_load.argtypes = [ctypes.c_char_p]
divvun_runtime.bundle_load.restype = ctypes.c_void_p
divvun_runtime.bundle_run_pipeline.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
divvun_runtime.bundle_run_pipeline.restype = ctypes.c_char_p
logging.info("Loading bundle...")
bundle = divvun_runtime.bundle_load(utils.box_path("sme").encode("utf-8"))
logging.info("Bundle loaded")
logging.info("Loaded divvun_runtime")

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
        return utils.get_locales(self.speller_paths)

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
    