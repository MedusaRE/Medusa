CPP=clang++
CPPFLAGS=--std=c++17

all: bin bin/main

bin:
	sh -c "mkdir bin"

clean:
	rm -rf bin

bin/main: bin/main.o
	${CPP} ${CPPFLAGS} $^ -o $@

bin/%.o: src/%.cpp
	mkdir -p $(@D)
	${CPP} ${CPPFLAGS} $< -c -o $@