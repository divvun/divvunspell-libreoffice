import os
import os.path
import sys
import platform
from os import PathLike
from typing import Mapping, Optional, NewType, List
import ctypes
import logging
from pathlib import Path

from com.sun.star.lang import ( Locale ) # type: ignore 

PARENT_DIR = Path(__file__).parent

# -------- Speller files --------
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


# -------- File paths --------
def _python_arch_name():
    return "%s-%s" % (sys.platform, platform.machine().lower())

def _python_lib_name(libname: str):
    s = sys.platform
    if s == "darwin":
        return "%s.dylib" % libname
    elif s == "win32":
        return "divvunspell.dll"
    else:
        return "%s.so" % libname

def native_lib_path(libname: str):
    return os.path.abspath(
        os.path.join(os.path.dirname(PARENT_DIR), "lib", _python_arch_name(), _python_lib_name(libname))
    )

def box_path(filename: str):
    return os.path.abspath(
        os.path.join(os.path.dirname(PARENT_DIR), "resources", "%s.drb" % filename)
    )

def locales_json_path():
    return os.path.abspath(
        os.path.join(os.path.dirname(PARENT_DIR), "locales.json")
    )


# -------- Locales --------
Bcp47Tag = NewType("Bcp47Tag", str)

def bcp47_tag(locale: Locale) -> Optional[Bcp47Tag]:
    if locale.Language == "qlt":
        return locale.Variant
    if locale.Language == "" or locale.Language is None:
        return None
    if locale.Country == "" or locale.Country is None:
        return locale.Language
    return "%s-%s" % (locale.Language, locale.Country)

def has_locale(speller_paths: Mapping[Bcp47Tag, PathLike], locale: Locale) -> bool:
    logging.info("Has locale? %r" % locale)
    tag = bcp47_tag(locale)
    if tag in speller_paths:
        return True
    if locale.Language in speller_paths:
        return True
    return False

def get_locales(LOCALES, speller_paths: Mapping[Bcp47Tag, PathLike]) -> List:
    # Iterate the directories for the .bhfst or .zhfst files
    locales = []
    for tag in speller_paths.keys():
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

            lo_countries = LOCALES.get(tag, None)
            if lo_countries is not None:
                for country in lo_countries:
                    locales.append(Locale(tag, country, ""))

    logging.info("Locales:")
    for locale in locales:
        logging.info("%r" % locale)
    
    return locales


# -------- FFI --------
class ForeignFuncError(Exception):
    pass


class StringPointer(ctypes.Structure):
    data: ctypes.c_void_p
    len: ctypes.c_void_p

    _fields_ = [
        ("data", ctypes.c_void_p),
        ("len", ctypes.c_void_p),
    ]

    @staticmethod
    def from_str(input: str):
        str_bytes = input.encode("utf-8")
        data = ctypes.cast(
            ctypes.pointer(ctypes.create_string_buffer(str_bytes, size=len(str_bytes))), ctypes.c_void_p
        )
        ptr = StringPointer(data, ctypes.c_void_p(len(str_bytes)))
        return ptr

    def as_bytes(self) -> bytes:
        return ctypes.string_at(self.data, self.len)

    def __str__(self) -> str:
        return self.as_bytes().decode("utf-8")
    

class PathPointer(ctypes.Structure):
    data: ctypes.c_void_p
    len: ctypes.c_void_p

    _fields_ = [
        ("data", ctypes.c_void_p),
        ("len", ctypes.c_void_p),
    ]

    @staticmethod
    def from_path(input: PathLike):
        if sys.platform == "win32":
            str_bytes = input.encode("utf-16-le")
            data = ctypes.cast(
                ctypes.pointer(ctypes.create_string_buffer(str_bytes, size=len(str_bytes))), ctypes.c_void_p
            )
            str_len = int(len(str_bytes) / 2)
            print(str_len)
        else:
            str_bytes = input.encode("utf-8")
            data = ctypes.cast(
                ctypes.pointer(ctypes.create_string_buffer(str_bytes, size=len(str_bytes))), ctypes.c_void_p
            )
            str_len = len(str_bytes)
        ptr = PathPointer(data, ctypes.c_void_p(str_len))
        return ptr

    def as_bytes(self) -> bytes:
        return ctypes.string_at(self.data, self.len)

    def __str__(self) -> str:
        if sys.platform == "win32":
            return self.as_bytes().decode("utf-16-le")
        else:
            return self.as_bytes().decode("utf-8")


class SlicePointer(ctypes.Structure):
    data: ctypes.c_void_p
    len: ctypes.c_void_p

    _fields_ = [
        ("data", ctypes.c_void_p),
        ("len", ctypes.c_void_p),
    ]


class TraitObjectPointer(ctypes.Structure):
    _fields_ = [
        ("data", ctypes.c_void_p),
        ("vtable", ctypes.c_void_p),
    ]

    @staticmethod
    def from_return_value(ptr: ctypes.c_void_p):
        return TraitObjectPointer(ptr, ptr + ctypes.sizeof(ctypes.c_void_p))
    