#include "platform.h"
#include "comment.h"
#include "post.h"
#include "reply.h"

Platform* PLATFORM = NULL;
bool postViewedYet = false;

//helpers start here

void DESTROYEVERYTHING() {
	Post* pp = PLATFORM->Posts;
	if(!pp) return;
	while(pp->nextpost) {
		pp = pp->nextpost;
		freePost(PLATFORM->Posts);
		PLATFORM->Posts = pp;
	}
	if(pp) {
		freePost(pp);
		PLATFORM->Posts = NULL;
	}
	free(PLATFORM);
}

void freeReply(Reply* r) {
	free(r->Username);
	free(r->Content);
	free(r);
}

void freeComment(Comment* c) {
	free(c->Username);
	free(c->Content);
	deleteReplies(c);
	free(c);
}

void deleteComments(Post* p) {
	Comment* c = p->Comments;
	if(!c) return;
	while(c->nextcomment) {
		c = c->nextcomment;
		freeComment(c->previouscomment);
	}
	freeComment(c);
	p->Comments = NULL;
}

void deleteReplies(Comment* c) {
	Reply* r = c->Replies;
	if(!r) return;
	while(r->nextreply) {
		r = r->nextreply;
		free(r->previousreply);
	}
	freeReply(r);
	c->Replies = NULL;
}

void freePost(Post* p) {
	if(!p) return;
	deleteComments(p);
	free(p->Username);
	free(p->Caption);
	free(p);
}

//helpers end here

Platform* createPlatform() {
	Platform* p = (Platform*) malloc(sizeof(Platform));
	p->Posts = NULL;
	p->lastViewedPost = NULL;
	return p;
}

bool addPost(char* username, char* caption) {
	if(!username || !caption) return false;
	if(!PLATFORM) return false;
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
	if(!PLATFORM) return false;
	Post* pp = PLATFORM->Posts;
	if(!pp) return false;
	int size = 1;
	while(pp->nextpost) {
		pp = pp->nextpost;
		size++;
	}
	if(n == 1 && size == 1) {
		PLATFORM->Posts = NULL;
		freePost(pp);
		PLATFORM->lastViewedPost = NULL;
		postViewedYet = false;
		return true;
	}
	if(n == 1 && size != 1) {
		pp->previouspost->nextpost = NULL;
		if(pp == PLATFORM->lastViewedPost) {
			PLATFORM->lastViewedPost = pp->previouspost;
		}
		freePost(pp);
		postViewedYet = false;
		return true;
	}
	if(size < n) return false;
	else if(size == n) {
		while(--n) pp = pp->previouspost;
		(pp->nextpost)->previouspost = NULL;
		Post* temp = pp->nextpost;
		if(pp == PLATFORM->lastViewedPost) {
			Post* temp2 = PLATFORM->Posts;
			while(temp2->nextpost) temp2 = temp2->nextpost;
			PLATFORM->lastViewedPost = temp2;
		}
		freePost(pp);
		PLATFORM->Posts = temp;
		postViewedYet = false;
		return true;
	}
	else if(size > n) {
		while(--n) pp = pp->previouspost;
		if(pp == PLATFORM->lastViewedPost) {
			Post* temp2 = PLATFORM->Posts;
			while(temp2->nextpost) temp2 = temp2->nextpost;
			PLATFORM->lastViewedPost = temp2;
		}
		(pp->nextpost)->previouspost = pp->previouspost;
		(pp->previouspost)->nextpost = pp->nextpost;
		freePost(pp);
		postViewedYet = false;
		return true;
	}
}

Post* viewPost(int n) {
	if(!PLATFORM) return NULL;
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
	if(!PLATFORM) return NULL;
	return PLATFORM->lastViewedPost;
}

Post* nextPost() {
	if(!PLATFORM) return NULL;
	if(!(PLATFORM->lastViewedPost)) return NULL;
	if(PLATFORM->lastViewedPost->previouspost) {
		PLATFORM->lastViewedPost = PLATFORM->lastViewedPost->previouspost;
		return PLATFORM->lastViewedPost;
	}
	else return PLATFORM->lastViewedPost;
}

Post* previousPost() {
	if(!PLATFORM) return NULL;
	if(!(PLATFORM->lastViewedPost)) return NULL;
	if(PLATFORM->lastViewedPost->nextpost) {
		PLATFORM->lastViewedPost = PLATFORM->lastViewedPost->nextpost;
		return PLATFORM->lastViewedPost;
	}
	else return PLATFORM->lastViewedPost;
}

bool addComment(char* username, char* content) {
	if(!PLATFORM) return false;
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
	if(!PLATFORM) return false;
	if(!(PLATFORM->lastViewedPost)) return false;
	Comment* LVPC = PLATFORM->lastViewedPost->Comments;
	if(!LVPC) return false;
	int size = 1;
	while(LVPC->nextcomment) {
		LVPC = LVPC->nextcomment;
		size++;
	}
	if(n == 1 && size == 1) {
		PLATFORM->lastViewedPost->Comments = NULL;
		deleteReplies(LVPC);
		free(LVPC);
		return true;
	}
	if(n == 1 && size != 1) {
		LVPC->previouscomment->nextcomment = NULL;
		deleteReplies(LVPC);
		free(LVPC);
		return true;
	}
	if(size < n) return false;
	else if(size == n) {
		while(--n) LVPC = LVPC->previouscomment;
		LVPC->nextcomment->previouscomment = NULL;
		PLATFORM->lastViewedPost->Comments = LVPC->nextcomment;
		deleteReplies(LVPC);
		free(LVPC);
		return true;
	}
	else if(size > n) {
		while(--n) LVPC = LVPC->previouscomment;
		LVPC->previouscomment->nextcomment = LVPC->nextcomment;
		LVPC->nextcomment->previouscomment = LVPC->previouscomment;
		deleteReplies(LVPC);
		free(LVPC);
		return true;
	}
}

Comment* viewComments() {
	if(!PLATFORM) return NULL;
	if(!(PLATFORM->lastViewedPost)) return NULL;
	return PLATFORM->lastViewedPost->Comments;
}

bool addReply(char* username, char* content, int n) {
	if(!PLATFORM) return false;
	if(!(PLATFORM->lastViewedPost)) return false;
	Comment* LVPC = PLATFORM->lastViewedPost->Comments;
	if(!LVPC) return false;
	int numcomments = 1;
	while(LVPC->nextcomment) {
		LVPC = LVPC->nextcomment;
		numcomments++;
	}
	if(numcomments < n) return false;
	while(--n) LVPC = LVPC->previouscomment;
	Reply* currentReply = LVPC->Replies;
	if(!currentReply) {
		currentReply = createReply(username, content);
		LVPC->Replies = currentReply;
		return true;
	}
	while(currentReply->nextreply) {
		currentReply = currentReply->nextreply;
	}
	currentReply->nextreply = createReply(username, content);
	currentReply->nextreply->previousreply = currentReply;
	while(LVPC->previouscomment) LVPC = LVPC->previouscomment;
	PLATFORM->lastViewedPost->Comments = LVPC;
	return true;
}

bool deleteReply(int n, int m) {
	if(!PLATFORM) return false;
	if(!(PLATFORM->lastViewedPost)) return false;
	Comment* LVPC = PLATFORM->lastViewedPost->Comments;
	if(!LVPC) return false;
	int numcomments = 1;
	while(LVPC->nextcomment) {
		LVPC = LVPC->nextcomment;
		numcomments++;
	}
	if(numcomments < n) return false;
	while(--n) LVPC = LVPC->previouscomment;
	Reply* LVR = LVPC->Replies;
	if(!LVR) return false;
	int numreplies = 1;
	while(LVR->nextreply) {
		LVR = LVR->nextreply;
		numreplies++;
	}
	if(numreplies < m) return false;
	else if(numreplies == m && m != 1) {
		while(--m) LVR = LVR->previousreply;
		LVR->nextreply->previousreply = NULL;
		LVPC->Replies = LVR->nextreply;
		freeReply(LVR);
		return true;
	}
	else if(numreplies == m && m == 1) {
		LVPC->Replies = NULL;
		freeReply(LVR);
		return true;
	}
	else if(numreplies > m) {
		if(m > 1) {
			while(--m) LVR = LVR->previousreply;
			LVR->previousreply->nextreply = LVR->nextreply;
			LVR->nextreply->previousreply = LVR->previousreply;
			freeReply(LVR);
			return true;
		}
		else if(m == 1) {
			LVR->previousreply->nextreply = NULL;
			freeReply(LVR);
			return true;
		}
	}
}
