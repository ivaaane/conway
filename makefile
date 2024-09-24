PREFIX = /usr/local

conway: conway.c
	$(CC) conway.c -o conway

.PHONY: clean
clean:
	$(RM) lavat

.PHONY: install
install: conway
	install		-D conway	$(DESTDIR)$(PREFIX)/bin/conway

.PHONY: uninstall
unistall:
	$(RM) $(DESTDIR)$(PREFIX)/bin/conway
