#include "types.h"
#include "post.h"
#include "comment.h"
#include "reply.h"
#include "platform.h"

int main() {
	PLATFORM = createPlatform();
	addPost("gautambhetanabhotla", "post1");
	addPost("gautambhetanabhotla", "post2");
	if(deletePost(2)) printf("SUCCESSFULLY DELETED\n");
	return 0;
}
