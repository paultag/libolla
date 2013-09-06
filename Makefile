SUBDIRS=src lib
.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

lib: src
tests: lib

install: $(SUBDIRS)
	mkdir -p $(DESTDIR)/usr/include $(DESTDIR)/usr/lib
	cp -r lib/*     $(DESTDIR)/usr/lib/

clean:
	rm -vf lib/*.so*
	rm -vf src/*.o

all: subdirs
