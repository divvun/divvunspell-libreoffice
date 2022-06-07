import os
from typing import Mapping, NamedTuple, Optional, NewType
import logging

# logging.basicConfig(filename='/tmp/divvunspell-libreoffice.log', level=logging.DEBUG)
logging.info("Started")

import unohelper  # type: ignore
from com.sun.star.linguistic2 import XSpellChecker, XLinguServiceEventBroadcaster, XSpellAlternatives  # type: ignore
from com.sun.star.linguistic2.SpellFailure import SPELLING_ERROR  # type: ignore
from com.sun.star.lang import (  # type: ignore
    XServiceInfo,
    XInitialization,
    XServiceDisplayName,
    IllegalArgumentException,
    Locale,
)

def _find_spellers(speller_base_path):
    speller_paths = {}
    for (path, _dirs, files) in os.walk(speller_base_path):
        speller_files = [x for x in files if x.endswith(".zhfst") or x.endswith(".bhfst")]
        for f in speller_files:
            p = os.path.join(path, f)
            tag = os.path.splitext(f)[0].replace("_", "-")
            if "-" in tag:
                base_tag = tag.split("-")[0]
                speller_paths[base_tag] = p
            speller_paths[tag] = p
    return speller_paths

def find_spellers():
    if sys.platform == "win32":
        return _find_spellers("C:\\Program Files\\WinDivvun\\spellers")
    elif sys.platform == "darwin":
        return _find_spellers("/Library/Services")

logging.info("Loading divvunspell")

# This is a ctypes wrapper around the native DivvunSpell libraries build with
# FFI support enabled.

import ctypes
import platform
import sys
from os import PathLike
import os.path
from ctypes import (
    CDLL,
    CFUNCTYPE,
    c_long,
    c_ubyte,
    c_ulong,
    c_void_p,
    create_string_buffer,
    create_unicode_buffer,
    pointer,
    sizeof,
)
from typing import List


def python_arch_name():
    return "%s-%s" % (sys.platform, platform.machine().lower())


def python_lib_name():
    s = sys.platform
    l = "libdivvunspell"
    if s == "darwin":
        return "%s.dylib" % l
    elif s == "win32":
        return "divvunspell.dll"
    else:
        return "%s.so" % l


def native_lib_path():
    return os.path.abspath(
        os.path.join(os.path.dirname(__file__), "lib", python_arch_name(), python_lib_name())
    )


class ForeignFuncError(Exception):
    pass


class StringPointer(ctypes.Structure):
    data: c_void_p
    len: c_void_p

    _fields_ = [
        ("data", c_void_p),
        ("len", c_void_p),
    ]

    @staticmethod
    def from_str(input: str):
        str_bytes = input.encode("utf-8")
        data = ctypes.cast(
            pointer(create_string_buffer(str_bytes, size=len(str_bytes))), c_void_p
        )
        ptr = StringPointer(data, c_void_p(len(str_bytes)))
        return ptr

    def as_bytes(self) -> bytes:
        return ctypes.string_at(self.data, self.len)

    def __str__(self) -> str:
        return self.as_bytes().decode("utf-8")


class PathPointer(ctypes.Structure):
    data: c_void_p
    len: c_void_p

    _fields_ = [
        ("data", c_void_p),
        ("len", c_void_p),
    ]

    @staticmethod
    def from_path(input: PathLike):
        if sys.platform == "win32":
            str_bytes = input.encode("utf-16-le")
            data = ctypes.cast(
                pointer(create_string_buffer(str_bytes, size=len(str_bytes))), c_void_p
            )
            str_len = int(len(str_bytes) / 2)
            print(str_len)
        else:
            str_bytes = input.encode("utf-8")
            data = ctypes.cast(
                pointer(create_string_buffer(str_bytes, size=len(str_bytes))), c_void_p
            )
            str_len = len(str_bytes)
        ptr = PathPointer(data, c_void_p(str_len))
        return ptr

    def as_bytes(self) -> bytes:
        return ctypes.string_at(self.data, self.len)

    def __str__(self) -> str:
        if sys.platform == "win32":
            return self.as_bytes().decode("utf-16-le")
        else:
            return self.as_bytes().decode("utf-8")


class SlicePointer(ctypes.Structure):
    data: c_void_p
    len: c_void_p

    _fields_ = [
        ("data", c_void_p),
        ("len", c_void_p),
    ]


class TraitObjectPointer(ctypes.Structure):
    _fields_ = [
        ("data", c_void_p),
        ("vtable", c_void_p),
    ]

    @staticmethod
    def from_return_value(ptr: c_void_p):
        return TraitObjectPointer(ptr, ptr + sizeof(c_void_p))


# Time to import the dylib and hook things
try:
    lib = CDLL(native_lib_path())
except Exception as e:
    print("Failed to load %s" % native_lib_path())
    raise e
lib.divvun_speller_archive_open.restype = TraitObjectPointer
lib.divvun_speller_archive_speller.restype = TraitObjectPointer
lib.divvun_speller_is_correct.restype = c_ubyte
lib.divvun_speller_suggest.restype = SlicePointer
lib.divvun_vec_suggestion_len.restype = c_ulong
lib.divvun_vec_suggestion_get_value.restype = StringPointer


_last_error = None


def assert_no_error():
    global _last_error
    if _last_error is not None:
        e = _last_error
        _last_error = None
        raise ForeignFuncError(e)


@CFUNCTYPE(c_void_p, c_void_p, c_void_p)
def error_callback(error: c_void_p, size: c_void_p):
    global _last_error
    _last_error = str(StringPointer(error, size))


class SpellerArchive:
    @staticmethod
    def open(path: str):
        b_path = PathPointer.from_path(path)
        handle = lib.divvun_speller_archive_open(b_path, error_callback)
        assert_no_error()
        return SpellerArchive(handle)

    def __init__(self, handle: TraitObjectPointer):
        if not isinstance(handle, TraitObjectPointer):
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
    def __init__(self, handle: TraitObjectPointer):
        if not isinstance(handle, TraitObjectPointer):
            raise TypeError("Invalid handle, got: %r" % type(handle))
        self._handle = handle

    def __del__(self):
        # TODO: there's no freeing functions for this, haha oh no
        pass

    def is_correct(self, input: str) -> bool:
        b_str = StringPointer.from_str(input)
        res = lib.divvun_speller_is_correct(self._handle, b_str, error_callback)
        assert_no_error()
        return res != 0

    def suggest(self, input: str) -> List[str]:
        b_str = StringPointer.from_str(input)
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

Bcp47Tag = NewType("Bcp47Tag", str)


def bcp47_tag(locale: Locale) -> Optional[Bcp47Tag]:
    if locale.Language == "qlt":
        return locale.Variant
    if locale.Language == "" or locale.Language is None:
        return None
    if locale.Country == "" or locale.Country is None:
        return locale.Language
    return "%s-%s" % (locale.Language, locale.Country)


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
        self.speller_paths: Mapping[Bcp47Tag, os.PathLike] = find_spellers()
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
        # Iterate the directories for the .bhfst or .zhfst files
        # raise NotImplementedError()
        locales = []

        for tag in self.speller_paths.keys():
            if tag.count("-") > 1:
                # This is a special one, we can't handle it yet.
                continue
            elif tag.count("-") == 1:
                # Language and country
                [lang, country] = tag.split("-")
                locales.append(Locale(lang, country, ""))
            else:
                # Just language
                locales.append(Locale(tag, "", ""))

                if tag == "se":
                    locales.append(Locale("se", "NO", ""))
                    locales.append(Locale("se", "SE", ""))
                    locales.append(Locale("se", "FI", ""))
                elif tag == "sma":
                    locales.append(Locale("sma", "NO", ""))
                    locales.append(Locale("sma", "SE", ""))
                elif tag == "sms":
                    locales.append(Locale("sms", "FI", ""))
                elif tag == "smn":
                    locales.append(Locale("smn", "FI", ""))
        
        return locales

    # XSupportedLocales
    def hasLocale(self, locale: Locale):
        tag = bcp47_tag(locale)
        if tag in self.speller_paths:
            return True
        if locale.Language in self.speller_paths:
            return True
        return False

    # XSpellChecker
    def isValid(self, word: str, locale: Locale, properties):
        if not self.hasLocale(locale):
            raise IllegalArgumentException(locale)

        tag = bcp47_tag(locale)
        speller = self.speller(tag)

        return speller.is_correct(word)

    # XSpellChecker
    def spell(self, word: str, locale: Locale, properties):
        if not self.hasLocale(locale):
            raise IllegalArgumentException(locale)

        tag = bcp47_tag(locale)
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

    def speller(self, tag: Bcp47Tag):
        base_tag = tag.split("-")[0]
        if tag not in self.speller_paths and base_tag not in self.speller_paths:
            raise IllegalArgumentException(tag)

        if tag not in self.speller_paths:
            tag = base_tag

        if tag not in self.spellers:
            ar = SpellerArchive.open(self.speller_paths[tag])
            self.spellers[tag] = ar.speller()

        return self.spellers[tag]


# This is the registration point for the speller.
try:
    g_ImplementationHelper = unohelper.ImplementationHelper()
    g_ImplementationHelper.addImplementation(
        SpellChecker, SpellChecker.IMPLEMENTATION_NAME, SpellChecker.SUPPORTED_SERVICE_NAMES
    )
except Exception as e:
    logging.error(e)
