#include "platform.h"

Platform* createPlatform() {
	Platform* p = (Platform*) malloc(sizeof(Platform));
	return p;
}
