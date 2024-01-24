# DSA - Assignment 1
Name: Gautam Bhetanabhotla<br>
Roll number: 2023101032

<br><br>

## Files

### Header files
The assignment allows us to have some extra helper files, so this assignment features an extra `types.h` file where all the structs and their members are declared and typedef'ed. This is for convenience in the other `.h` files, where the functions involve more than one data type. Any editor errors may be omitted by including `types.h` in those headers.<br>
Additionally, `types.h` also includes the system headers `stdio.h`, `stdlib.h`, `string.h` and `stdbool.h`.<br>
Since headers are included in other headers and multiple other headers may be included in one header, multiple declaration/definition errors are prone to occur. Hence, each header file features `#ifndef` directives to avoid getting included more than once in any file.

<br>

### Source files
The source files, or the `.c` files, contain the definitions of all the functions that were required to be implemented. `platform.c`, apart from the required functions, also features a couple of helper functions to make things easier in other base functions. Those functions are marked by comments in the file.<br>`main.c` contains the `main()` function and also provides an interface with the base functions and the user by providing a command-line interface.

Here's a table showing the source files (and other header files) that a particular header file is included in.<br>

| types.h | post.h | comment.h | reply.h | platform.h |
| ----- | ----- | ----- | ----- | ----- |
| post.h |  |  |  |  |
| comment.h |  |  |  |  |
| reply.h |  |  |  |  |
| platform.h |  |  |  |  |
|  | post.c |  |  |  |
|  |  | comment.c |  |  |
|  |  |  | reply.c |  |
|  | platform.c | platform.c | platform.c | platform.c |
|  | main.c | main.c | main.c | main.c |

<br>

### Makefile
The makefile compiles all files ending in `.c` in the `code/` directory into an executable called `main`.<br>
Equivalent to running `gcc code/post.c code/comment.c code/reply.c code/platform.c code/main.c -o main` in the project's root directory.

<br><br>

## The command-line interface
The I/O format matches the format specified in the assignment document.<br>
Posts, comments and replies all have 2 elements: a username and some content (caption in the case of a post). The username must not contain spaces and can be 100 characters long, at max. The content may contain spaces but still must be, at most, 100 characters long, including the spaces AND the newline at the end. Therefore, 99 characters long with spaces.