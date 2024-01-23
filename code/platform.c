#include "platform.h"
#include "comment.h"
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
		return false;
	}
	while(pp->nextpost) {
		pp = pp->nextpost;
		size++;
	}
	if(n == 1) {
		Post* temp = pp;
		pp = pp->previouspost;
		pp->nextpost = NULL;
		free(temp);
		return true;
	}
	if(n == 1 && size == 1) {
		PLATFORM->Posts = NULL;
		free(pp);
		return true;
	}
	if(n == 1 && size != 1) {
		pp->previouspost->nextpost = NULL;
		free(pp);
		return true;
	}
	if(size < n) {
		return false;
	}
	else if(size == n) {
		while(--n) pp = pp->previouspost;
		(pp->nextpost)->previouspost = NULL;
		Post* temp = pp->nextpost;
		free(pp);
		PLATFORM->Posts = temp;
		return true;
	}
	else if(size > n) {
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

bool addComment(char* username, char* content) {
	if(!(PLATFORM->lastViewedPost)) return false;
	Comment* currentComment = PLATFORM->lastViewedPost->Comments;
	if(!(currentComment)) {
		currentComment = createComment(username, content);
		PLATFORM->lastViewedPost->Comments = currentComment;
		return true;
	}
	while((currentComment->nextcomment)) {
		currentComment = currentComment->nextcomment;
	}
	currentComment->nextcomment = createComment(username, content);
	currentComment->nextcomment->previouscomment = currentComment;
	return true;
}

bool deleteComment(int n) {
	Comment* LVPC = PLATFORM->lastViewedPost->Comments;
	if(!LVPC) return false;
	int size = 1;
	while(LVPC->nextcomment) {
		LVPC = LVPC->nextcomment;
		size++;
	}
	if(n == 1 && size == 1) {
		PLATFORM->lastViewedPost->Comments = NULL;
		free(LVPC);
		return true;
	}
	if(n == 1 && size != 1) {
		LVPC->previouscomment->nextcomment = NULL;
		free(LVPC);
		return true;
	}
	if(size < n) return false;
	else if(size == n) {
		while(--n) LVPC = LVPC->previouscomment;
		LVPC->nextcomment->previouscomment = NULL;
		PLATFORM->lastViewedPost->Comments = LVPC->nextcomment;
		free(LVPC);
		return true;
	}
	else if(size > n) {
		while(--n) LVPC = LVPC->previouscomment;
		LVPC->previouscomment->nextcomment = LVPC->nextcomment;
		LVPC->nextcomment->previouscomment = LVPC->previouscomment;
		free(LVPC);
		return true;
	}
}
