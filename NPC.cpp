#include "AntQuest.h"
NPC::NPC(){}
void NPC::walkTo(int x, int y){}
	void NPC::setPosition(int x, int y){}
	bool NPC::isWalking(){return false;}
	bool NPC::isTalking(){return false;}
	//Pos NPC::position(){return}
	void NPC::say(std::string text){}
	void NPC::setIcon(const char *icon){}
	//const char* NPC::getIcon(){}
	void NPC::walk(int diff){}
	const char *NPC::getSpeech(){return "";}
	Rect NPC::getRect(){
		Rect r;
		r.x=p.x;
		r.y=p.y;
		r.x2=p.x+10;
		r.y2=p.y+10;
		return r;
	}