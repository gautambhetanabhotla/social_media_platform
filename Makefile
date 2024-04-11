objects := $(patsubst src/%.c,build/%.o,$(wildcard src/*.c))

default: build main

build:
	@mkdir build

main: $(objects)
	@gcc -o main -g $^

build/%.o: src/%.c
	@gcc -c -g -o $@ $<

clean:
	@rm -rf build main
