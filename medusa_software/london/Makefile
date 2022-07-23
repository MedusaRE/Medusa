export PKG_CONFIG_PATH=/usr/lib/pkgconfig:/usr/local/lib/pkgconfig
CPP=clang++
CPPFLAGS=--std=c++17 `pkg-config gtkmm-3.0 --cflags` `pkg-config gtksourceviewmm-3.0 --cflags`

all: ~/.medusa/london.ini bin bin/main

~/.medusa/london.ini: ../../res/defaults/.medusa/london.ini
	mkdir -p ~/.medusa
	cp $^ $@

bin:
	sh -c "mkdir bin"

clean:
	rm -rf bin

bin/main: bin/main.o bin/lib.o bin/logging.o bin/medusa_window.o bin/london.o
	${CPP} ${CPPFLAGS} `pkg-config gtkmm-3.0 --libs` `pkg-config gtksourceviewmm-3.0 --libs` $^ -o $@

bin/%.o: src/%.cpp
	mkdir -p $(@D)
	${CPP} ${CPPFLAGS} $< -c -o $@
