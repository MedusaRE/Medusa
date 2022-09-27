CPP=clang++
CPPFLAGS=--std=c++17 -fPIC -Iinclude

all: bin bin/libmedusa.so bin/main doxygen_out

bin:
	sh -c "mkdir bin"

doxygen_out: src/*.cpp include/*/*.hpp
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
	cp -R include/* /usr/include

bin/%.o: src/%.cpp
	${CPP} ${CPPFLAGS} $< -c -o $@

run: bin/main
	bin/main

doxygen_web: doxygen_out
	mkdir -p /var/www/docs.medusa-re.org/libmedusa
	cp -R doxygen_out/html/* /var/www/docs.medusa-re.org/libmedusa/