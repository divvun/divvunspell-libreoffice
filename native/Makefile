# Build the divvunspell.uno.dylib UNO C++ component for macOS.
#
# Headers are vendored under vendor/include/ (see tools/regen-vendor-headers.sh).
# UNO symbols bind at load time inside LO via -undefined dynamic_lookup.
# libdivvun_runtime.a is statically linked in; system frameworks/libs come
# from `otool -L libdivvun_runtime.dylib` on the matching cdylib build.

LO_FRAMEWORKS ?= /Applications/LibreOffice.app/Contents/Frameworks

ifndef RUNTIME_LIB
  ifndef DIVVUN_RUNTIME_DIR
    $(error Set DIVVUN_RUNTIME_DIR (or RUNTIME_LIB and RUNTIME_INC) to point at the divvun-runtime checkout)
  endif
  RUNTIME_LIB := $(DIVVUN_RUNTIME_DIR)/target/release
endif
ifndef RUNTIME_INC
  ifndef DIVVUN_RUNTIME_DIR
    $(error Set DIVVUN_RUNTIME_DIR (or RUNTIME_LIB and RUNTIME_INC) to point at the divvun-runtime checkout)
  endif
  RUNTIME_INC := $(DIVVUN_RUNTIME_DIR)/bindings/c
endif
RUNTIME_LIB_FILE = $(RUNTIME_LIB)/libdivvun_runtime.a

VENDOR_INC = vendor/include
VENDOR_NLOHMANN = vendor

CXX        ?= clang++
CXXSTD     ?= -std=c++17
OPT        ?= -O2
ARCH       ?= -arch arm64

CXXFLAGS = $(CXXSTD) $(OPT) $(ARCH) -fPIC -fvisibility=hidden \
           -DUNX -DMACOSX -D_PTHREADS \
           -I$(VENDOR_INC) -I$(VENDOR_NLOHMANN) -I$(RUNTIME_INC) -I.

LDFLAGS = -shared $(ARCH) \
          -Wl,-undefined,dynamic_lookup \
          -install_name @rpath/divvunspell.uno.dylib

RUNTIME_FRAMEWORKS = -framework CoreFoundation \
                     -framework Foundation \
                     -framework CoreML \
                     -framework Accelerate \
                     -framework CoreGraphics
RUNTIME_LIBS = -lc++ -lobjc -lsqlite3 -liconv

SRCS = component.cxx DivvunProofreader.cxx DivvunSpellChecker.cxx SettingsDialog.cxx Engine.cxx RuntimeBridge.cxx Platform.cxx
OBJS = $(SRCS:.cxx=.o)

TARGET = divvunspell.uno.dylib

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) $(RUNTIME_LIB_FILE)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(RUNTIME_LIB_FILE) $(RUNTIME_FRAMEWORKS) $(RUNTIME_LIBS)

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
