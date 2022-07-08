CPP=clang++
CPPFLAGS=--std=c++17 -fPIC

all: bin bin/libmedusa.so doxygen_out

bin:
	sh -c "mkdir bin"
	sh -c "mkdir bin/libmedusa"

doxygen_out: src/*.cpp src/*.hpp
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
	cp -R src/*.hpp bin/libmedusa/
	cp -R bin/libmedusa /usr/include

bin/%.o: src/%.cpp
	${CPP} ${CPPFLAGS} $< -c -o $@
