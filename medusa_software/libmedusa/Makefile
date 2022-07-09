CPP=clang++
CPPFLAGS=--std=c++17 -fPIC

all: bin bin/libmedusa.so doxygen_out

bin:
	sh -c "mkdir bin"

doxygen_out: src/*.cpp include/*.hpp
	doxygen

clean:
	rm -rf bin doxygen_out

tools: bin/main

bin/main: bin/main.o
	${CPP} ${CPPFLAGS} -lLIEF -lmedusa -lkeystone -lunicorn -lcapstone $^ -o $@

bin/libmedusa.so: bin/ARMv7Machine.o bin/ARM64Machine.o
	${CPP} -shared -o $@ $^

install: bin/libmedusa.so
	cp bin/libmedusa.so /usr/lib/
	rm -rf /usr/include/libmedusa
	cp -R include /usr/include/libmedusa

bin/%.o: src/%.cpp
	${CPP} ${CPPFLAGS} $< -c -o $@
