#include "post.h"
#include "comment.h"
#include "reply.h"
#include "platform.h"

extern Platform* PLATFORM;
extern bool postViewedYet;

//some more helpers


void prompt() {
	printf("\033[0;34mCommand: \033[0m");
}

void createPlatformHelper() {
	if(!PLATFORM) PLATFORM = createPlatform();
}

void addPostHelper() {
	char username[101], caption[101];
	scanf("%s\n", username);
	fgets(caption, 101, stdin);
	if(!addPost(username, caption)) printf("ERROR: Post not added\n");
	fflush(stdin);
}

void deletePostHelper() {
	int n;
	scanf("%d", &n);
	if(!deletePost(n)) printf("ERROR: Post not deleted\n");
	fflush(stdin);
}

void viewPostHelper() {
	int n;
	scanf("%d", &n);
	Post* p = viewPost(n);
	if(!p) printf("ERROR: Post not found\n");
	else printf("%s %s", p->Username, p->Caption);
	fflush(stdin);
}

void currentPostHelper() {
	Post* p = currPost();
	if(!p) printf("ERROR: Post not found\n");
	else printf("%s %s", p->Username, p->Caption);
	fflush(stdin);
}

void previousPostHelper() {
	Post* p = previousPost();
	if(!p) printf("ERROR: Previous post does not exist\n");
	else printf("%s %s", p->Username, p->Caption);
	fflush(stdin);
}

void nextPostHelper() {
	Post* p = nextPost();
	if(!p) printf("ERROR: Next post does not exist\n");
	else printf("%s %s", p->Username, p->Caption);
	fflush(stdin);
}

void addCommentHelper() {
	char username[101], content[101];
	scanf("%s\n", username);
	fgets(content, 101, stdin);
	if(!addComment(username, content)) printf("ERROR: Comment not added\n");
	fflush(stdin);
}

void viewAllCommentsHelper() {
	Comment* c = viewComments();
	if(!c) printf("ERROR: Comments not available\n");
	else {
		while(c) {
			printf("%s %s", c->Username, c->Content);
			Reply* r = c->Replies;
			while(r) {
				printf("\t%s %s", r->Username, r->Content);
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
	char username[101], content[101];
	int n;
	for(int i = 0; i < 101; i++) content[i] = '\0';
	scanf("%s\n", username);
	fgets(content, 101, stdin);
	scanf("%d", &n);
	if(!addReply(username, content, n)) printf("ERROR: Reply not added\n");
	fflush(stdin);
}

void deleteReplyHelper() {
	int n, m; scanf("%d", &n); scanf("%d", &m);
	if(!deleteReply(n, m)) printf("ERROR: Reply not deleted\n");
	fflush(stdin);
}

//helpers end here

char* commandlist[] = {"create_platform", "add_post", "delete_post", "view_post", "current_post", "previous_post", "next_post", "add_comment", "view_comments", "delete_comment", "add_reply", "delete_reply", "exit"};

void processQuery() {
	prompt();
	char command[100];
	scanf("%s", command);
	int commandmatch = -1;
	for(int i = 0; i < 13; i++) if(strcmp(command, commandlist[i]) == 0) commandmatch = i;
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
		case 12:
			DESTROYEVERYTHING();
			exit(0);
	}
}

int main() {
	while(true) processQuery();
	return 0;
}
