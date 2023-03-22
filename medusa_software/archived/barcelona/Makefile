CPP=clang++
CPPFLAGS=--std=c++17 -lcurses

all: bin bin/main

bin:
	mkdir -p bin

clean:
	rm -rf bin

bin/main: bin/main.o
	${CPP} ${CPPFLAGS} $^ -o $@

bin/%.o: src/%.cpp
	mkdir -p $(@D)
	${CPP} ${CPPFLAGS} $< -c -o $@
