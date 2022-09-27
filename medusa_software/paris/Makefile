CPP=clang++
CPPFLAGS=--std=c++17

all: bin bin/main doxygen_out

bin:
	sh -c "mkdir bin"

clean:
	rm -rf bin

bin/main: bin/main.o
	${CPP} ${CPPFLAGS} $^ -o $@

bin/%.o: src/%.cpp
	mkdir -p $(@D)
	${CPP} ${CPPFLAGS} $< -c -o $@

.PHONY doxygen_out:
	doxygen