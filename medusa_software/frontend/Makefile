CPP=clang++
CPPFLAGS=--std=c++17 `pkg-config gtkmm-3.0 --cflags` -lparis

all: bin bin/main

bin:
	sh -c "mkdir bin"

clean:
	rm -rf bin

bin/main: bin/main.o bin/logging.o bin/medusa_window.o bin/lib.o
	${CPP} ${CPPFLAGS} `pkg-config gtkmm-3.0 --libs` -lcapstone -lunicorn $^ -o $@

bin/%.o: src/%.cpp
	${CPP} ${CPPFLAGS} $< -c -o $@
