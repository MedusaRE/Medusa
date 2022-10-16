CPP=clang++
CPPFLAGS=--std=c++17 -fPIC -Iinclude -O0 -g

.PHONY: all
all: bin bin/libmedusa.so bin/main doxygen_out

bin:
	sh -c "mkdir bin"

doxygen_out: src/*.cpp include/*/*.hpp
	doxygen

.PHONY: clean
clean:
	rm -rf bin doxygen_out

.PHONY: tools
tools: bin/main

bin/main: bin/main.o
	${CPP} ${CPPFLAGS} -Lbin -lLIEF -lmedusa -lkeystone -lunicorn -lcapstone $^ -o $@

bin/libmedusa.so: bin/ARMv7Machine.o bin/ARM64Machine.o bin/ExampleComponent.o bin/ExampleComponent2.o bin/ExampleDisplayComponent.o bin/libmedusa.o
	${CPP} -shared -o $@ $^

.PHONY: install
install: bin/libmedusa.so
	cp bin/libmedusa.so /usr/lib/
	rm -rf /usr/include/libmedusa
	cp -R include/* /usr/include

bin/%.o: src/%.cpp
	${CPP} ${CPPFLAGS} $< -c -o $@

.PHONY: run
run: bin/main
	bin/main

.PHONY: doxygen_web
doxygen_web: doxygen_out
	mkdir -p /var/www/docs.medusa-re.org/libmedusa
	cp -R doxygen_out/html/* /var/www/docs.medusa-re.org/libmedusa/