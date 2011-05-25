#include "AntQuest.h"
HotSpot::HotSpot(int x, int y, int x2, int y2, const char *name){
	rect.x=x;
	rect.y=y;
	rect.x2=x2;
	rect.y2=y2;
	spotName=name;
}

bool HotSpot::intersects(int x, int y) {
	if (x>=rect.x && x<=rect.x2 && y>=rect.y && y<=rect.y2) return true;
	return false;
}

const char *HotSpot::getName() {
	return spotName;
}