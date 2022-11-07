CPP=clang++
CPPFLAGS=--std=c++17 -g3 -DLIB_H_NO_BUILD_GUI -fPIC -Iinclude -Lbin

all: bin bin/libparis.so bin/main

bin:
	mkdir -p bin

clean:
	rm -rf bin

bin/main: bin/main.o
	${CPP} ${CPPFLAGS} -Lbin -lparis $^ -o $@

bin/%.o: src/%.cpp
	mkdir -p $(@D)
	${CPP} ${CPPFLAGS} $< -c -o $@

bin/libparis.so: bin/paris.o bin/lib.o
	${CPP} -shared -o $@ $^

.PHONY: doxygen_out
doxygen_out:
	doxygen

doxygen_web: doxygen_out
	mkdir -p /var/www/docs.medusa-re.org/paris
	cp -R doxygen_out/html/* /var/www/docs.medusa-re.org/paris/

.PHONY: install
install: bin/libparis.so
	cp bin/libparis.so /usr/lib/
	rm -rf /usr/include/paris
	cp -R include/* /usr/include