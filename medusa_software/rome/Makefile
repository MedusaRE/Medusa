CPP=clang++
CPPFLAGS=--std=c++17 -lncurses -Iinclude

all: bin bin/rome.so bin/main

bin:
	sh -c "mkdir bin"

clean:
	rm -rf bin

bin/main: bin/main.o bin/rome.so
	${CPP} ${CPPFLAGS} $^ -o $@

bin/rome.so: src/rome.cpp
	${CPP} ${CPPFLAGS} $^ -shared -o $@

bin/%.o: src/%.cpp
	mkdir -p $(@D)
	${CPP} ${CPPFLAGS} $< -c -o $@
