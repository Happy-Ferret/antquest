#include "AntQuest.h"

//void Player::pickUp(Item i) { 
//	inventory->push_back(i);
//}

Player::Player() {
	p.x=0;
	p.y=0;
	direction=1;
	icon="default.bmp";
	walking=false;
	talking=false;
	action.x=NULL;
	action.y=NULL;
	action.action=NULL;
}

bool Player::isWalking() {
	return walking;
}

bool Player::isTalking() {
	return talking;
}

void Player::setPosition(int x, int y) {
	p.x=(float)x;
	p.y=(float)y;
}

void Player::walkTo(int x, int y) {
	walkP.x=(float)x;
	walkP.y=(float)y;
	walking=true;
	if (walkP.x>p.x) {
		direction=1;
	} else if (walkP.x <p.x) {
		direction=3;
	}
	updateAnim();
}

void Player::say(std::string text) {

}

void Player::setIcon(const char* cicon) {
	icon=(char *)malloc(sizeof(cicon));
	strcpy(icon,cicon);
}

const char* Player::getIcon() {
	return icon;
}

Pos Player::position() {
	return p;
}

void Player::walk(int diff) {
	if (walking) {
			if (walkP.x-p.x <=0.1 && walkP.x-p.x >= -0.1 && walkP.y-p.y <=0.1 && walkP.y-p.y >= - 0.1 ) {
				walking=false;
				updateAnim();
			}
			if (walkP.x>p.x) {p.x=p.x+0.1f; 
			} else if (walkP.x <p.x) { p.x=p.x-0.1f; }
			if (walkP.y>p.y) {p.y=p.y+0.1f; 
			} else if (walkP.y<p.y) { p.y=p.y-0.1f; }
	}
}

void Player::setAnimation(Animation *an) {
	a=an;
}

SDL_Rect Player::getCurrentFrame(int time) {
	return a->getFrame(0);
}

void Player::updateAnim() {
	if (walking) {
		if (direction==1) {
			a->setAnim("walkRight");
		} else if (direction==3) {
			a->setAnim("walkLeft");
		}
	} else if(talking) {
	} else {
			a->setAnim("stationaryDown");
	}
}

Action Player::getAction() {
	return action;
}

void Player::setAction(Action act) {
	action=act;
}

bool Player::hasItem(const char *itemname) {
	for (unsigned int i=0; i<inventory.size(); i++) {
		if(strcmp(inventory.at(i)->getName(),itemname)==0) return true;
	}
	return false;
}

void Player::pickUp(Item *i) {
	inventory.push_back(i);
}

void Player::drop(const char *itemname) {
	for (unsigned int i=0; i<inventory.size(); i++) {
		if(strcmp(inventory.at(i)->getName(),itemname)==0) inventory.erase(inventory.begin()+i); break;
	}
}