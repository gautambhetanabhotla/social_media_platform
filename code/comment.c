#include "comment.h"

Comment* createComment(char* username, char* content) {
	Comment* c = (Comment*) malloc(sizeof(Comment));
	c->Username = (char*) malloc((strlen(username) + 1) * sizeof(char));
	c->Content = (char*) malloc((strlen(content) + 1) * sizeof(char));
	c->Replies = NULL;
	strcpy(c->Username, username);
	strcpy(c->Content, content);
	return c;
}
