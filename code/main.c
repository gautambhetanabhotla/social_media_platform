#include "post.h"
#include "comment.h"
#include "reply.h"
#include "platform.h"

extern Platform* PLATFORM;
extern bool postViewedYet;

char* commandlist[] = {"create_platform", "add_post", "delete_post", "view_post", "current_post", "previous_post", "next_post", "add_comment", "view_all_comments", "delete_comment", "add_reply", "delete_reply"};
char* functionlist[];

int main() {
	PLATFORM = createPlatform();
	addPost("gautambhetanabhotla", "post1");
	addPost("gautambhetanabhotla", "post2");
	addPost("krishivgupta", "post3");
	addPost("sriyanshsuryadevara", "post4");
	addPost("ravichandra", "post5");
	if(deletePost(1)) printf("DELETED BRUH\n");
	Post* pp = PLATFORM->Posts;
	while(pp != NULL) {
		printf("%s %s\n", pp->Username, pp->Caption);
		pp = pp->nextpost;
	}
	printf("Hello there\n");
	printf("%s %s\n", currPost()->Username, currPost()->Caption);
	printf("%s %s\n", viewPost(3)->Username, viewPost(3)->Caption);
	printf("%s %s\n", currPost()->Username, currPost()->Caption);
	if(addComment("gautambhetanabhotla", "sriyansh is so hot")) printf("COMMENT ADDED\n");
	printf("%s %s\n", currPost()->Comments->Username, currPost()->Comments->Content);
	if(deleteComment(1)) printf("COMMENT DELETED\n");
	if(addComment("gautambhetanabhotla", "sriyansh is so hot")) printf("COMMENT ADDED\n");
	printf("%s %s\n", currPost()->Comments->Username, currPost()->Comments->Content);
	return 0;
}
