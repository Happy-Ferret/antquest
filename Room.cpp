#include "AntQuest.h"

std::vector<HotSpot*> localSpots;
std::vector<Object*> localObjects;

Room::Room() {
}

int Room::newRoom(const char *roomStr) {
	for (unsigned int i=0; i<objects.size(); i++) {
		objects.at(i);
	}
	fileName=(char *)malloc(sizeof(roomStr));
	strcpy(fileName,roomStr);
	return 0;
}

const char* Room::getBackground() {
	return backGround;
}

const char* Room::getFile() {
	return fileName;
}

Object* Room::intersectsObject(int x, int y) {
	for( unsigned int i = 0; i < objects.size(); i++ ) {
		if (objects.at(i)->intersects(x, y)) return objects.at(i);
	}
	return NULL;
}

HotSpot* Room::intersectsHotSpot(int x, int y) {
	for( unsigned int i = 0; i < hotSpots.size(); i++ ) {
		if (hotSpots.at(i)->intersects(x, y)) return hotSpots.at(i);
	}
	return NULL;
}

unsigned Room::getNumberofObjects() {
	return objects.size();
}

Object *Room::getObject(int index) {
	return objects.at(index);
}

void Room::setBackground(const char* bg) {
	backGround=(char *)malloc(sizeof(bg));
	strcpy(backGround,bg);
}

void Room::addObject(Object *obj) {
	objects.push_back(obj);
}

void Room::addHotSpot(HotSpot *hs) {
	hotSpots.push_back(hs);
}