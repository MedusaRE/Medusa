CPP=clang++
CPPFLAGS=--std=c++17 `pkg-config gtkmm-3.0 --cflags` -L../../libmedusa/bin -I../../libmedusa/include

all: bin bin/main

bin:
	mkdir -p bin

clean:
	rm -rf bin

bin/main: bin/main.o
	${CPP} ${CPPFLAGS} `pkg-config gtkmm-3.0 --libs` -lmedusa -lunicorn -lkeystone -lcapstone $^ -o $@

bin/%.o: src/%.cpp
	${CPP} ${CPPFLAGS} $< -c -o $@
