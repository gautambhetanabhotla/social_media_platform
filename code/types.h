#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#ifndef TYPES_H
#define TYPES_H

struct Post;
struct Platform;
struct Comment;
struct Reply;

struct Post {
	char* Username;
	char* Caption;
	struct Comment* Comments;
};

struct Comment {
	char* Username;
	char* Content;
	struct Reply* Replies;
};

struct Platform {
	struct Post* Posts;
	struct Post* lastViewedPost;
};

struct Reply {
	char* Username;
	char* Content;
};

typedef struct Platform Platform;
typedef struct Post Post;
typedef struct Comment Comment;
typedef struct Reply Reply;

extern Platform PLATFORM;

#endif
