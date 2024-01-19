#include "reply.h"

Reply* createReply(char* username, char* content) {
	Reply* r = (Reply*) malloc(sizeof(Reply));
	r->Username = (char*) malloc((strlen(username) + 1) * sizeof(char));
	r->Content = (char*) malloc((strlen(content) + 1) * sizeof(char));
	strcpy(r->Username, username);
	strcpy(r->Content, content);
	return r;
}
