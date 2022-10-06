CPP=clang++
CPPFLAGS=--std=c++17

all: res/bin bin bin/main

bin:
	sh -c "mkdir bin"

clean:
	rm -rf bin

bin/main: bin/main.o
	${CPP} ${CPPFLAGS} $^ -o $@

bin/%.o: src/%.cpp
	mkdir -p $(@D)
	${CPP} ${CPPFLAGS} $< -c -o $@

res/bin:
	sh -c "mkdir res/bin"

res/bin/x86_test_shellcode.o: res/src/x86_test_shellcode.c
	clang -target x86_64 -ffreestanding $< -c -o $@

res/bin/x86_test_shellcode.bin: res/bin/x86_test_shellcode.o
	ld -o $@ $< --oformat binary
