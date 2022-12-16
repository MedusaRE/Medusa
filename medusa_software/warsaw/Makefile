CPP=clang++
CPPFLAGS=--std=c++17 -lparis -Iinclude -lmedusa -lunicorn -lkeystone -lcapstone -I../libmedusa/include

all: bin bin/warsaw

bin:
	mkdir -p bin

clean:
	rm -rf bin

bin/warsaw: bin/main.o bin/ARMv7Machine.o bin/Machine.o
	${CPP} ${CPPFLAGS} $^ -o $@

bin/%.o: src/%.cpp
	mkdir -p $(@D)
	${CPP} ${CPPFLAGS} $< -c -o $@

.PHONY: doxygen_out
doxygen_out:
	doxygen