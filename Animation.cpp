#include "AntQuest.h"

Animation::Animation() {
	for (int i=0; i<MAX_ANIMS; i++) {
		anims[i].animationName=NULL;
	}
	nextFreeAnim=0;
	currentFrame=0;
	currentAnim=0;
}
void Animation::addAnim(const char *name) {
	anims[nextFreeAnim].animationName=name;
	for (int i=0; i<MAX_FRAMES; i++) {
		anims[nextFreeAnim].rects[i].x=NULL;
		anims[nextFreeAnim].rects[i].y=NULL;
		anims[nextFreeAnim].rects[i].w=NULL;
		anims[nextFreeAnim].rects[i].h=NULL;
	}
	nextFreeAnim++;
}

void Animation::addFrame(int index, int x, int y, int w, int h, const char *name){
	SDL_Rect rect;
	rect.x=x;
	rect.y=y;
	rect.w=w;
	rect.h=h;
	if (index>MAX_FRAMES) return;
	for (int i=0; i<MAX_ANIMS; i++) {
		if (anims[i].animationName!=NULL && strcmp(anims[i].animationName,name)==0) {
			anims[i].rects[index]=rect;
		}
	}
}

SDL_Rect Animation::getFrame(int time){
	int framerate =0;
	currentFrame++;
	if (currentFrame>5) currentFrame=0;
	return anims[currentAnim].rects[currentFrame];
}

void Animation::setAnim(const char *name) {
	for (int i=0; i<MAX_ANIMS; i++) {
		if (anims[i].animationName!=NULL && strcmp(anims[i].animationName,name)==0) { currentAnim=i; currentFrame=0; return; }
	}
}