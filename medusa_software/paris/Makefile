CPP=clang++
CPPFLAGS=--std=c++17 -g3 -DLIB_H_NO_BUILD_GUI

all: bin bin/main doxygen_out

bin:
	sh -c "mkdir bin"

clean:
	rm -rf bin

bin/main: bin/main.o bin/paris.o bin/lib.o
	${CPP} ${CPPFLAGS} $^ -o $@

bin/%.o: src/%.cpp
	mkdir -p $(@D)
	${CPP} ${CPPFLAGS} $< -c -o $@

.PHONY: doxygen_out
doxygen_out:
	doxygen

doxygen_web: doxygen_out
	mkdir -p /var/www/docs.medusa-re.org/paris
	cp -R doxygen_out/html/* /var/www/docs.medusa-re.org/paris/