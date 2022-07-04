.POSIX:

PREFIX = /usr/local

target/release/now-playing: src/lib.rs src/main.rs
	cargo build --release
clean:
	cargo clean
install: target/release/now-playing
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f target/release/now-playing $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/now-playing
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/now-playing

.PHONY: clean install uninstall
