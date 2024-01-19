#include "comment.h"

struct Comment {
	char* username;
	char* content;
	struct Reply* replies;
};


