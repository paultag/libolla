BUILDCHAIN=../meta/buildchain/
include $(BUILDCHAIN)/library-info.mk

LIB=../lib/
INC=../include/

TARGETS=$(shell ls *.c | sed s/.c$$/.o/g)
CFLAGS=-Wall -c -fPIC -I$(INC)
CC=gcc

LDFLAGS=-shared \
		-Wl,--no-as-needed \
		-ldl \
		-Wl,-soname,$(LIBRARY_NAME).so.$(LIBRARY_VERSION_MAJOR)
# For some god-forsaken reason, ld needs --no-as-needed to know that libdl is
# actually needed, even though we both include it's header *and* actually
# use a symbol from libdl. Gah. Anyway, forcing old lazy behavior since
# I'm actually controlling the imports here. Sorry for the static.
#
# Thanks to some part of git for breaking the call by not linking against ldl :)

OUTPUT=$(LIB)$(LIBRARY_NAME).so.$(LIBRARY_VERSION_MINOR)

all: $(TARGETS) link

clean:
	rm -f *.o
	rm -f $(OUTPUT)

include $(BUILDCHAIN)build.mk
