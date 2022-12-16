CPP=clang++
CPPFLAGS=--std=c++17 -lparis

all: bin bin/warsaw

bin:
	mkdir -p bin

clean:
	rm -rf bin

bin/warsaw: bin/main.o
	${CPP} ${CPPFLAGS} $^ -o $@

bin/%.o: src/%.cpp
	mkdir -p $(@D)
	${CPP} ${CPPFLAGS} $< -c -o $@
