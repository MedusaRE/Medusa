CPP=clang++
CPPFLAGS=

all: bin bin/main

bin:
	sh -c "mkdir bin"

clean:
	rm -rf bin

bin/main: bin/main.o
	${CPP} ${CPPFLAGS} $^ -o $@

bin/%.o: src/%.cpp
	${CPP} ${CPPFLAGS} $< -c -o $@
