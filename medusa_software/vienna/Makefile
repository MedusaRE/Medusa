CPP=clang++
CPPFLAGS=--std=c++17 -Iinclude -lcapstone -lkeystone -lmedusa -lunicorn -lLIEF -fPIC -DLIB_H_NO_BUILD_GUI -O3 -lpcre2-8

all: res/bin bin bin/libvienna.so bin/main res/bin/x86_test_shellcode.bin res/bin/armv7_test_shellcode.bin res/bin/armv7_ls.bin doxygen_out

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

bin/libvienna.so: bin/ARMv7Decompiler.o bin/lib.o
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
	clang -target arm -ffreestanding -g0 $< -c -o $@

res/bin/armv7_test_shellcode.bin: res/bin/armv7_test_shellcode.o res/bin
#	ld.lld -o $@ $< --oformat binary
	llvm-objcopy -O binary --only-section=.text $< $@
#	cat $@ | tail -c +17 > $@.tmp
#	mv $@.tmp $@

res/bin/armv7_ls.bin: ../submodules/binary-samples/elf-Linux-ARMv7-ls res/bin
#	ld.lld -o $@ $< --oformat binary
	llvm-objcopy -O binary --only-section=.text $< $@
#	cat $@ | tail -c +17 > $@.tmp
#	mv $@.tmp $@

#.PHONY: doxygen_out
doxygen_out:
	doxygen

doxygen_web: doxygen_out
	mkdir -p /var/www/docs.medusa-re.org/vienna
	cp -R doxygen_out/html/* /var/www/docs.medusa-re.org/vienna/
