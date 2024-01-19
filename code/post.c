#include "post.h"

struct Post {
	char* Username;
	char* Caption;
	Comment* Comments;
};

Post* createPost(char* username, char* caption) {
	Post* p = (Post*) malloc(sizeof(Post));
	p->Username = (char*) malloc((strlen(username) + 1) * sizeof(char));
	p->Caption = (char*) malloc((strlen(caption) + 1) * sizeof(char));
	p->Comments = NULL;
	strcpy(p->Username, username);
	strcpy(p->Caption, caption);
	return p;
}
