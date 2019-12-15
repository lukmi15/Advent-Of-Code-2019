prog1: code1.cpp shared.cpp Makefile
	@g++ -Wall -o $@ $<

prog2: code2.cpp shared.cpp Makefile
	@g++ -Wall -o $@ $<

clean:
	@bash -c 'rm -v prog*' 2>/dev/null ; exit 0

.PHONY: clean
