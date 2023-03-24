CPP=clang++
CPPFLAGS=--std=c++17 -lparis -Iinclude -lmedusa -lunicorn -lkeystone -lcapstone -I../../libmedusa/include -I../../mpi/include -L../../mpi/bin -L../../libmedusa/bin
CPPFLAGS_SO=-shared -undefined dynamic_lookup

.PHONY: all
all: bin bin/warsaw bin/libwarsaw.so

bin:
	mkdir -p bin

.PHONY: clean
clean:
	rm -rf bin

bin/warsaw: bin/main.o bin/ARMv7Machine.o bin/Machine.o
	${CPP} ${CPPFLAGS} $^ -o $@

bin/libwarsaw.so: bin/ARMv7Machine.o bin/Machine.o
	${CPP} ${CPPFLAGS} ${CPPFLAGS_SO} $^ -o $@

bin/%.o: src/%.cpp
	mkdir -p $(@D)
	${CPP} ${CPPFLAGS} $< -c -o $@

.PHONY: doxygen_out
doxygen_out:
	doxygen

.PHONY: install
install: bin/libwarsaw.so
	cp bin/libwarsaw.so /usr/lib/
	rm -rf /usr/include/warsaw
	cp -R include/* /usr/include
