main: build/*.o
	@gcc -g -o main build/*.o

build/*.o:
	@gcc -g -c src/*.c -o build/*.o