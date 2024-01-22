#include "types.h"
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
	printf("%s %s\n", currPost()->Username, currPost()->Caption);
	printf("%s %s\n", viewPost(2)->Username, viewPost(2)->Caption);
	printf("%s %s\n", currPost()->Username, currPost()->Caption);
	return 0;
}
