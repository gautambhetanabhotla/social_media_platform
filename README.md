# Social media platform

This program was made as part of our first assignment on Data Structures and Agorithms.

<br>

## Commands

`create_platform` creates the social media platform. It is the first command that must be run in every session. Only one platform can be created.<br>
`add_post username caption` adds a post to the platform, by `username` and with the caption `caption`.<br>
`delete_post n` deletes the `n`th recent post on the platform.<br>
`view_post n` displays the `n`th recent post on the platform along with its comments and their replies.<br>
`current_post` displays the most recently viewed post. If no post has been viewed yet, it displays the most recent post added to the platform.<br>
`previous_post` displays the post added right after the current post. (It says "previous" because recent posts show up first and older ones next, for example, on Instagram.)<br>
`next_post` displays the post added before the current post.<br>
`add_comment username content` adds a comment on the current post by `username` with the content `content`.

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



### Makefile

The makefile compiles all files ending in `.c` in the `code/` directory into an executable called `main`.<br>
Equivalent to running `gcc code/post.c code/comment.c code/reply.c code/platform.c code/main.c -o main` in the project's root directory.

<br>

## The command-line interface

Posts, comments and replies all have 2 elements: a username and some content (caption in the case of a post). The username must not contain spaces and can be 100 characters long, at max. The content may contain spaces but still must be, at most, 100 characters long, including the spaces AND the newline at the end. Therefore, 99 characters long with spaces.

