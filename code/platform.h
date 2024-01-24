#include "types.h"

#ifndef PLATFORM_H
#define PLATFORM_H

//helpers

void DESTROYEVERYTHING();
void freeReply(Reply* r);
void freeComment(Comment* c);
void deleteComments(Post* p);
void deleteReplies(Comment* c);
void freePost(Post* p);

//helpers end here

Platform* createPlatform();
bool addPost(char* username, char* caption);
bool deletePost(int n);
Post* viewPost(int n);
Post* currPost();
Post* nextPost();
Post* previousPost();
bool addComment(char* username, char* content);
bool deleteComment(int n);
Comment* viewComments();
bool addReply(char* username, char* content, int n);
bool deleteReply(int n, int m);

#endif
