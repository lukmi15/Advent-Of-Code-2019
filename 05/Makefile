prog1: code1.cpp ici.hpp ici.cpp
	@g++ -Wall -o $@ $< ici.cpp

prog2: code2.cpp ici.hpp ici.cpp
	@g++ -Wall -o $@ $< ici.cpp

clean:
	@bash -c 'rm -v prog* ; exit 0'

.PHONY: clean
