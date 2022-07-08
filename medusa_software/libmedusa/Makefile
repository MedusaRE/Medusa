CPP=clang++
CPPFLAGS=--std=c++17

all: bin bin/main doxygen_out

bin:
	sh -c "mkdir bin"

doxygen_out: src/*.cpp src/*.hpp
	doxygen

clean:
	rm -rf bin doxygen_out

bin/main: bin/main.o bin/ARMv7Machine.o bin/ARM64Machine.o
	${CPP} ${CPPFLAGS} -lLIEF -lkeystone -lunicorn -lcapstone $^ -o $@

bin/%.o: src/%.cpp
	${CPP} ${CPPFLAGS} $< -c -o $@
