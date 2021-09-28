prog1: code1.cpp tree.hpp
	g++ -Wall -o $@ $<

prog2: code2.cpp tree.cpp
	@g++ -Wall -o $@ $<

clean:
	@bash -c 'rm -v prog* ; exit 0' 2>/dev/null

.PHONY: clean
