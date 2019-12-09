prog1: code1.cpp shared_classes.cpp Makefile
	@g++ -Wall -o $@ $<

prog2: code2.cpp shared_classes.cpp Makefile
	@g++ -Wall -o $@ $<

clean:
	@bash -c 'rm -v prog* ; exit 0'

.PHONY: clean
