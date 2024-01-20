#include "platform.h"
#include "post.h"

Platform* createPlatform() {
	Platform* p = (Platform*) malloc(sizeof(Platform));
	p->Posts = NULL;
	p->lastViewedPost = NULL;
	return p;
}

bool addPost(char* username, char* caption) {
	if(!username || !caption) return false;
	Post* pp = PLATFORM->Posts;
	if(pp) {
		while(pp->nextpost) pp = pp->nextpost;
		pp->nextpost = createPost(username, caption);
		(pp->nextpost)->previouspost = pp;
	}
	else {
		pp = createPost(username, caption);
	}
	return true;
}	

bool deletePost(int n) {
	Post* pp = PLATFORM->Posts;
	int size = 1;
	if(!pp) return false;
	while(pp->nextpost) {
		pp = pp->nextpost;
		size++;
	}
	if(size < n) return false;
	if(size == n) {
		while(--n) pp = pp->previouspost;
		(pp->nextpost)->previouspost = NULL;
		Post* temp = pp->nextpost;
		free(pp);
		PLATFORM->Posts = temp;
		return true;
	}
	if(size > n) {
		while(--n) pp = pp->previouspost;
		(pp->nextpost)->previouspost = pp->previouspost;
		(pp->previouspost)->nextpost = pp->nextpost;
		free(pp);
		return true;
	}
}