BUILDCHAIN=../meta/buildchain/
include $(BUILDCHAIN)/library-info.mk

LIB=../lib/
INC=../include/

TARGETS=$(shell ls *.c | sed s/.c/.o/g)
CFLAGS=-Wall -c -fPIC -I$(INC)
CC=gcc

LDFLAGS=-lncurses -lpanel -lutil -shared \
	-Wl,-soname,$(LIBRARY_NAME).so.$(LIBRARY_VERSION_MAJOR)

OUTPUT=$(LIB)$(LIBRARY_NAME).so.$(LIBRARY_VERSION_MINOR)

all: $(TARGETS) link

clean:
	rm -f *.o
	rm -f $(OUTPUT)

include $(BUILDCHAIN)build.mk
