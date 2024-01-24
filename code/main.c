#include "post.h"
#include "comment.h"
#include "reply.h"
#include "platform.h"

extern Platform* PLATFORM;
extern bool postViewedYet;

//some more helpers

void createPlatformHelper() {
	PLATFORM = createPlatform();
	// printf("Platform created\n");
}

void addPostHelper() {
	// printf("in add post\n");
	char username[101], caption[101];
	scanf("%s", username);
	fgets(caption, 101, stdin);
	if(!addPost(username, caption)) printf("ERROR: Post not added\n");
	fflush(stdin);
}

void deletePostHelper() {
	// printf("in delete post\n");
	int n;
	scanf("%d", &n);
	if(!deletePost(n)) printf("ERROR: Post not deleted\n");
	fflush(stdin);
}

void viewPostHelper() {
	// printf("in view post\n");
	int n;
	scanf("%d", &n);
	Post* p = viewPost(n);
	if(!p) printf("ERROR: Post not found\n");
	else printf("%s %s\n", p->Username, p->Caption);
	fflush(stdin);
}

void currentPostHelper() {
	Post* p = currPost();
	if(!p) printf("ERROR: Post not found\n");
	else printf("%s %s\n", p->Username, p->Caption);
	fflush(stdin);
}

void previousPostHelper() {
	Post* p = previousPost();
	if(!p) printf("ERROR: Previous post does not exist\n");
	else printf("%s %s\n", p->Username, p->Caption);
	fflush(stdin);
}

void nextPostHelper() {
	Post* p = nextPost();
	if(!p) printf("ERROR: Next post does not exist\n");
	else printf("%s %s\n", p->Username, p->Caption);
	fflush(stdin);
}

void addCommentHelper() {
	char username[101], content[101];
	scanf("%s", username);
	fgets(content, 101, stdin);
	if(!addComment(username, content)) printf("ERROR: Comment not added\n");
	fflush(stdin);
}

void viewAllCommentsHelper() {
	Comment* c = viewComments();
	if(!c) printf("ERROR: Comments not available\n");
	else {
		while(c->nextcomment) {
			printf("%s %s\n", c->Username, c->Content);
			Reply* r = c->Replies;
			while(r) {
				printf("\t%s %s\n", c->Replies->Username, c->Replies->Content);
				r = r->nextreply;
			}
			c = c->nextcomment;
		}
	}
}

void deleteCommentHelper() {
	int n; scanf("%d", &n);
	if(!deleteComment(n)) printf("ERROR: Couldn't delete comment\n");
	fflush(stdin);
}

void addReplyHelper() {

}

void deleteReplyHelper() {

}

//helpers end here

char* commandlist[] = {"create_platform", "add_post", "delete_post", "view_post", "current_post", "previous_post", "next_post", "add_comment", "view_all_comments", "delete_comment", "add_reply", "delete_reply"};

void processQuery() {
	char command[100];
	scanf("%s", command);
	int commandmatch = -1;
	for(int i = 0; i < 12; i++) if(strcmp(command, commandlist[i]) == 0) commandmatch = i;
	switch(commandmatch) {
		case -1:
			fflush(stdin);
			return;
		case 0:
			createPlatformHelper();
			break;
		case 1:
			addPostHelper();
			break;
		case 2:
			deletePostHelper();
			break;
		case 3:
			viewPostHelper();
			break;
		case 4:
			currentPostHelper();
			break;
		case 5:
			previousPostHelper();
			break;
		case 6:
			nextPostHelper();
			break;
		case 7:
			addCommentHelper();
			break;
		case 8:
			viewAllCommentsHelper();
			break;
		case 9:
			deleteCommentHelper();
			break;
		case 10:
			addReplyHelper();
			break;
		case 11:
			deleteReplyHelper();
			break;
	}
}

int main() {
	/* PLATFORM = createPlatform();
	addPost("gautambhetanabhotla", "post1");
	addPost("gautambhetanabhotla", "post2");
	addPost("krishivgupta", "post3");
	addPost("sriyanshsuryadevara", "post4");
	addPost("ravichandra", "post5");
	Post* PPPP = viewPost(3);
	printf("%s %s\n", PPPP->Username, PPPP->Caption);
	printf("%s %s\n", currPost()->Username, currPost()->Caption);
	if(addComment("gautambhetanabhotla", "sriyansh is so hot")) printf("COMMENT ADDED\n");
	if(addComment("krishiv", "sriyansh is so hoter")) printf("COMMENT ADDED\n");
	printf("%s %s\n", currPost()->Comments->Username, currPost()->Comments->Content);
	if(deleteComment(2)) printf("COMMENT DELETED\n");
	if(addComment("gautambhetanabhotla", "sriyansh is so hot")) printf("COMMENT ADDED\n");
	printf("%s %s\n", currPost()->Comments->Username, currPost()->Comments->Content);
	if(addReply("gautambhetanabhotla", "ikr", 1)) printf("REPLY ADDED\n");
	printf("\t%s %s\n", currPost()->Comments->Replies->Username, currPost()->Comments->Replies->Content);
	if(addReply("gautambhetanabhotla", "ikr", 1)) printf("REPLY ADDED\n");
	printf("\t%s %s\n", currPost()->Comments->Replies->nextreply->Username, currPost()->Comments->Replies->nextreply->Content); */
	while(true) processQuery();
	return 0;
}
