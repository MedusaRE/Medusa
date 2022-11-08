CPP=clang++
CPPFLAGS=--std=c++20 `pkg-config gtkmm-3.0 --cflags` -lparis -I../paris/include/ -L../paris/bin/

all: bin bin/main

bin:
	mkdir -p bin

clean:
	rm -rf bin

bin/main: bin/main.o bin/logging.o bin/medusa_window.o bin/lib.o bin/medusa_application.o
	${CPP} ${CPPFLAGS} `pkg-config gtkmm-3.0 --libs` -lcapstone -lunicorn $^ -o $@

bin/%.o: src/%.cpp
	${CPP} ${CPPFLAGS} $< -c -o $@
