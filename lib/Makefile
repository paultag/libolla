BUILDCHAIN=../meta/buildchain/
include $(BUILDCHAIN)/library-info.mk

all: clean
	ln -s $(LIBRARY_NAME).so.$(LIBRARY_VERSION_MINOR) \
		$(LIBRARY_NAME).so.$(LIBRARY_VERSION_MAJOR)
	ln -s $(LIBRARY_NAME).so.$(LIBRARY_VERSION_MINOR) $(LIBRARY_NAME).so

clean:
	rm -f $(LIBRARY_NAME).so.$(LIBRARY_VERSION_MAJOR)
	rm -f $(LIBRARY_NAME).so

include $(BUILDCHAIN)build.mk
