#include "platform.h"
#include "post.h"

Platform* PLATFORM;
bool postViewedYet = false;

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
		if(!postViewedYet) PLATFORM->lastViewedPost = pp->nextpost;
	}
	else {
		pp = createPost(username, caption);
		PLATFORM->Posts = pp;
		if(!postViewedYet) PLATFORM->lastViewedPost = pp;
	}
	return true;
}

bool deletePost(int n) {
	Post* pp = PLATFORM->Posts;
	int size = 1;
	if(!pp) {
		// printf("PLATFORM->Posts is NULL\n");
		return false;
	}
	while(pp->nextpost) {
		pp = pp->nextpost;
		size++;
	}
	// printf("Reached the end of posts, number of posts is %d\n", size);
	if(n == 1) {
		Post* temp = pp;
		pp = pp->previouspost;
		pp->nextpost = NULL;
		free(temp);
		return true;
	}
	if(size < n) {
		// printf("Size is less than n\n");
		return false;
	}
	else if(size == n) {
		// printf("Size = n\n");
		while(--n) pp = pp->previouspost;
		(pp->nextpost)->previouspost = NULL;
		Post* temp = pp->nextpost;
		free(pp);
		PLATFORM->Posts = temp;
		return true;
	}
	else if(size > n) {
		// printf("Size is more than n\n");
		while(--n) pp = pp->previouspost;
		(pp->nextpost)->previouspost = pp->previouspost;
		(pp->previouspost)->nextpost = pp->nextpost;
		free(pp);
		return true;
	}
}

Post* viewPost(int n) {
	Post* pp = PLATFORM->Posts;
	int size = 1;
	if(!pp) return NULL;
	while(pp->nextpost) {
		pp = pp->nextpost;
		size++;
	}
	if(size < n) return NULL;
	while(--n) pp = pp->previouspost;
	postViewedYet = true;
	PLATFORM->lastViewedPost = pp;
	return pp;
}

Post* currPost() {
	return PLATFORM->lastViewedPost;
}

Post* nextPost() {
	if(!(PLATFORM->lastViewedPost)) return NULL;
	if(PLATFORM->lastViewedPost->previouspost) {
		PLATFORM->lastViewedPost = PLATFORM->lastViewedPost->previouspost;
		return PLATFORM->lastViewedPost;
	}
	else return PLATFORM->lastViewedPost;
}

Post* previousPost() {
	if(!(PLATFORM->lastViewedPost)) return NULL;
	if(PLATFORM->lastViewedPost->nextpost) {
		PLATFORM->lastViewedPost = PLATFORM->lastViewedPost->nextpost;
		return PLATFORM->lastViewedPost;
	}
	else return PLATFORM->lastViewedPost;
}


