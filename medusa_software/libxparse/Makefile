CPP=clang++
CPPFLAGS=--std=c++17 -DLIB_H_NO_BUILD_GUI

all: bin bin/main

bin:
	mkdir -p bin

clean:
	rm -rf bin

bin/main: bin/main.o bin/XParse.o bin/ELF.o bin/lib.o
	${CPP} ${CPPFLAGS} $^ -o $@

bin/%.o: src/%.cpp
	${CPP} ${CPPFLAGS} $< -c -o $@
