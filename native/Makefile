# Build the divvunspell.uno.dylib UNO C++ component for macOS.
#
# Headers are vendored under vendor/include/ (see tools/regen-vendor-headers.sh).
# Link libs come from /Applications/LibreOffice.app/Contents/Frameworks/.
# We use -undefined dynamic_lookup so symbols bind at load time inside LO.

LO_FRAMEWORKS ?= /Applications/LibreOffice.app/Contents/Frameworks

VENDOR_INC = vendor/include
VENDOR_NLOHMANN = vendor

CXX        ?= clang++
CXXSTD     ?= -std=c++17
OPT        ?= -O2
ARCH       ?= -arch arm64

CXXFLAGS = $(CXXSTD) $(OPT) $(ARCH) -fPIC -fvisibility=hidden \
           -DUNX -DMACOSX -D_PTHREADS \
           -I$(VENDOR_INC) -I$(VENDOR_NLOHMANN) -I.

LDFLAGS = -shared $(ARCH) \
          -Wl,-undefined,dynamic_lookup \
          -install_name @rpath/divvunspell.uno.dylib

SRCS = component.cxx DivvunProofreader.cxx DivvunSpellChecker.cxx SettingsDialog.cxx Engine.cxx RuntimeBridge.cxx
OBJS = $(SRCS:.cxx=.o)

TARGET = divvunspell.uno.dylib

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
