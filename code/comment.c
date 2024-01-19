#include "comment.h"

struct Comment {
	char* Username;
	char* Content;
	struct Reply* Replies;
};


