CPP=clang++
CPPFLAGS=--std=c++20 `pkg-config gtkmm-3.0 --cflags` -lparis -I../paris/include/ -L../paris/bin/ -fPIE -fPIC -g3

all: bin bin/medusa_frontend

bin:
	mkdir -p bin

clean:
	rm -rf bin

install: bin/medusa_frontend
	cp bin/medusa_frontend /usr/bin
	cp ../../res/Medusa.desktop /usr/share/applications
	cp ../../res/img/icon.png /usr/share/icons/medusa.png

bin/medusa_frontend: bin/main.o bin/logging.o bin/medusa_window.o bin/lib.o bin/medusa_application.o
	${CPP} ${CPPFLAGS} `pkg-config gtkmm-3.0 --libs` -lcapstone -lunicorn $^ -o $@

bin/%.o: src/%.cpp
	${CPP} ${CPPFLAGS} $< -c -o $@
