CPP=clang++
CPPFLAGS=--std=c++17 `pkg-config gtkmm-3.0 --cflags`

all: bin bin/main

bin:
	mkdir -p bin

clean:
	rm -rf bin

bin/main: bin/main.o bin/logging.o bin/medusa_window.o
	${CPP} ${CPPFLAGS} `pkg-config gtkmm-3.0 --libs` $^ -o $@

bin/%.o: src/%.cpp
	${CPP} ${CPPFLAGS} $< -c -o $@
