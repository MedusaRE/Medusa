CPP=clang++
CPPFLAGS=--std=c++17 -Iinclude -lcapstone -lkeystone -lmedusa -lunicorn -lLIEF -fPIC

all: res/bin bin bin/libvienna.so bin/main doxygen_out

bin:
	sh -c "mkdir bin"

clean:
	rm -rf bin res/bin

bin/main: bin/main.o
	${CPP} ${CPPFLAGS} -Lbin -lvienna ../submodules/pugixml/src/pugixml.cpp $^ -o $@

bin/%.o: src/%.cpp
	mkdir -p $(@D)
	${CPP} ${CPPFLAGS} $< -c -o $@

res/bin:
	sh -c "mkdir res/bin"

bin/libvienna.so: bin/ARMv7Decompiler.o
	${CPP} ${CPPFLAGS} -shared -o $@ $^

.PHONY: install
install: bin/libvienna.so
	cp bin/libvienna.so /usr/lib/
	rm -rf /usr/include/vienna
	cp -R include/* /usr/include

res/bin/x86_test_shellcode.o: res/src/x86_test_shellcode.c res/bin
	clang -target x86_64 -ffreestanding $< -c -o $@

res/bin/x86_test_shellcode.bin: res/bin/x86_test_shellcode.o res/bin
	ld.lld -o $@ $< --oformat binary

res/bin/armv7_test_shellcode.o: res/src/armv7_test_shellcode.c res/bin
	clang -target arm -ffreestanding $< -c -o $@

res/bin/armv7_test_shellcode.bin: res/bin/armv7_test_shellcode.o res/bin
	ld.lld -o $@ $< --oformat binary

.PHONY: doxygen_out
doxygen_out:
	doxygen

doxygen_web: doxygen_out
	mkdir -p /var/www/docs.medusa-re.org/vienna
	cp -R doxygen_out/html/* /var/www/docs.medusa-re.org/vienna/