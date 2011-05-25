#include "AntQuest.h"
Item::Item(const char *cname, const char *ciconPicture) {
	name=(char *)malloc(sizeof(cname));
	strcpy(name,cname);
	iconPicture=(char *)malloc(sizeof(ciconPicture));
	strcpy(iconPicture,ciconPicture);
}

const char *Item::getName() {
	return name;
}

const char *Item::getIcon() {
	return iconPicture;
}