# Flags for the C/C++ preprocessor
CPPFLAGS += -I. -I/usr/include
# Flags for the C compiler
CFLAGS   ?= -std=gnu99
# Flags for the linker
LDFLAGS  += -lm -lfftw3

# Some variables used to install the products of compilation:
#  * `prefix`: prefix where the executable and the shared library will be
#    installed
#  * `bindir`: directory where the executable will be installed
#  * `libdir`: directory where the shared library will be installed
# These variables are preset in the BinaryBuilder environment.
prefix ?= /usr/local
bindir ?= $(prefix)/bin
libdir ?= $(prefix)/lib

# `dlext` is the extension of shared libraries, `exeext` is the extension,
# including the dot, of executables.  These variables are preset in the
# BinaryBuilder environment.
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	dlext  ?= dylib
	exeext ?=
else ifeq ($(UNAME), Windows)
	dlext  ?= dll
	exeext ?= .exe
else
	dlext  ?= so
	exeext ?=
endif

# Names of files we want to generate
SINE_EXE     := sine$(exeext)
SPECTRUM_EXE := spectrum$(exeext)
SINEWAVE_LIB := libsinewave.$(dlext)

.PHONY: all clean

all: $(SINEWAVE_LIB) $(SINE_EXE) $(SPECTRUM_EXE)

install: all
	mkdir -p $(bindir)
	mkdir -p $(libdir)
	cp $(SINEWAVE_LIB) $(libdir)
	cp $(SINE_EXE) $(bindir)

$(SINEWAVE_LIB): sinewave.c sinewave.h
	cc $(CPPFLAGS) $(CFLAGS) -shared -fPIC -o $@ $< $(LDFLAGS)

$(SINE_EXE): $(SINEWAVE_LIB) examples/fill_and_print_buffer.c
	cc $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(SPECTRUM_EXE): $(SINEWAVE_LIB) examples/show_spectrum.c
	cc $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(SINEWAVE_LIB) $(SINE_EXE) $(SPECTRUM_EXE)
