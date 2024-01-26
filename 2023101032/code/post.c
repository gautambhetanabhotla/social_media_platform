#include "post.h"


Post* createPost(char* username, char* caption) {
	Post* p = (Post*) malloc(sizeof(Post));
	p->Username = (char*) malloc((strlen(username) + 1) * sizeof(char));
	p->Caption = (char*) malloc((strlen(caption) + 1) * sizeof(char));
	p->Comments = NULL;
	p->nextpost = NULL;
	p->previouspost = NULL;
	strcpy(p->Username, username);
	strcpy(p->Caption, caption);
	return p;
}