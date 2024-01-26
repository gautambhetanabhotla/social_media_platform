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
	struct Post* nextpost;
	struct Post* previouspost;
};

struct Comment {
	char* Username;
	char* Content;
	struct Reply* Replies;
	struct Comment* nextcomment;
	struct Comment* previouscomment;
};

struct Platform {
	struct Post* Posts;
	struct Post* lastViewedPost;
};

struct Reply {
	char* Username;
	char* Content;
	struct Reply* nextreply;
	struct Reply* previousreply;
};

typedef struct Platform Platform;
typedef struct Post Post;
typedef struct Comment Comment;
typedef struct Reply Reply;

#endif
