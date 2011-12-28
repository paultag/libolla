.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<
link:
	$(CC) $(LDFLAGS) $(TARGETS) -o $(OUTPUT)
