main: wordle_game

# wordle.o: wordle.cpp wordle.H
#	g++ -c wordle.cpp

SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard *.H)


OBJECTS := $(SOURCES:.cpp=.o)

%.o : %.cpp ${HEADERS}
	g++ -c $<

wordle: ${OBJECTS}
	g++ -o $@ ${OBJECTS}

clean:
	-rm -f *.o main

debug:
	g++ -g -o debug wordle.cpp wordle.H

run-debug: debug
	ddd debug

.PHONY: run-debug