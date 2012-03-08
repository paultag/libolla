SUBDIRS=src lib
.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

lib: src
tests: lib

install: $(SUBDIRS)
	mkdir -p $(DESTDIR)/usr/include $(DESTDIR)/usr/lib
	cp -r include/* $(DESTDIR)/usr/include/
	cp -r lib/*     $(DESTDIR)/usr/lib/

all: subdirs
