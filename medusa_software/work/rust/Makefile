RUSTC=rustc

all: bin bin/main

bin/main: src/main.rs
	rustc -o $@ $<

clean:
	rm -rf bin

bin:
	sh -c "mkdir bin"