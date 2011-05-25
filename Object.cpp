#include "AntQuest.h"
Object::Object(int x, int y, int x2, int y2, const char *name, const char *icon){
	rect.x=x;
	rect.y=y;
	rect.x2=x2;
	rect.y2=y2;
	objectName=name;
	objectIcon=icon;
}

bool Object::intersects(int x, int y) {
	if (x>=rect.x && x<=rect.x2 && y>=rect.y && y<=rect.y2) return true;
	return false;
}

const char *Object::getName() {
	return objectName;
}

const char *Object::getIcon() {
	return objectIcon;
}

SDL_Rect Object::getRect() {
	return srect;
}

SDL_Surface* Object::getSurface() {
	return surface;
}