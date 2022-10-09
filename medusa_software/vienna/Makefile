CPP=clang++
CPPFLAGS=--std=c++17 -Iinclude -lcapstone -lkeystone -lmedusa -lunicorn -lLIEF

all: res/bin bin bin/libvienna.so bin/main

bin:
	sh -c "mkdir bin"

clean:
	rm -rf bin

bin/main: bin/main.o
	${CPP} ${CPPFLAGS} -Lbin -lvienna $^ -o $@

bin/%.o: src/%.cpp
	mkdir -p $(@D)
	${CPP} ${CPPFLAGS} $< -c -o $@

res/bin:
	sh -c "mkdir res/bin"

bin/libvienna.so: bin/vienna.o
	${CPP} ${CPPFLAGS} -shared -o $@ $^

.PHONY: install
install: bin/libvienna.so
	cp bin/libvienna.so /usr/lib/
	rm -rf /usr/include/vienna
	cp -R include/* /usr/include

res/bin/x86_test_shellcode.o: res/src/x86_test_shellcode.c
	clang -target x86_64 -ffreestanding $< -c -o $@

res/bin/x86_test_shellcode.bin: res/bin/x86_test_shellcode.o
	ld -o $@ $< --oformat binary
