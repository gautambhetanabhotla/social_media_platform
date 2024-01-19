default: main

main: build/main.o build/comment.o build/platform.o build/post.o build/reply.o
	@gcc -o main build/main.o build/comment.o build/platform.o build/post.o build/reply.o

build/main.o: code/main.c
	@gcc -c code/main.c -o build/main.o

build/comment.o: code/comment.c
	@gcc -c code/comment.c -o build/comment.o

build/platform.o: code/platform.c
	@gcc -c code/platform.c -o build/platform.o

build/post.o: code/post.c
	@gcc -c code/post.c -o build/post.o

build/reply.o: code/reply.c
	@gcc -c code/reply.c -o build/reply.o

.PHONY: clean
clean:
	@rm -rf build/* > /dev/null 2>&1
	@rm main > /dev/null 2>&1
