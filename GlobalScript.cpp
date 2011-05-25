#include "AntQuest.h"
GameEngine* sengine;
Player *splayer;
Room *sroom;
Speech *sspeech;
std::vector<Item*> *sitems;
std::vector<NPC*> *snpcs;
GlobalScript *script;
int timer;
int waitTime;
bool waiting;
std::vector<GameVariable> variables;

int GlobalScript::open(const char* file) {
	mLuaVM = lua_open();

	if(mLuaVM == NULL) {
		return -1;
	}

	lua_baselibopen(mLuaVM);
	lua_iolibopen(mLuaVM);
	lua_strlibopen(mLuaVM);
	lua_mathlibopen(mLuaVM);

	lua_register(mLuaVM, "say", say);
	lua_register(mLuaVM, "hasItem", hasItem);
	lua_register(mLuaVM, "addHotSpot", addHotSpot);
	lua_register(mLuaVM, "addObject", addObject);
	lua_register(mLuaVM, "addItem", addItem);
	lua_register(mLuaVM, "addFrame", addFrame);
	lua_register(mLuaVM, "loadRoom", loadRoom);
	lua_register(mLuaVM, "enterScene", enterScene);
	lua_register(mLuaVM, "walkTo", walkTo);
	lua_register(mLuaVM, "wait", wait);
	lua_register(mLuaVM, "fadeIn", fadeIn);
	lua_register(mLuaVM, "fadeOut", fadeOut);
	lua_register(mLuaVM, "set", set);
	lua_register(mLuaVM, "get", get);
	lua_register(mLuaVM, "pickUp", pickUp);
	lua_register(mLuaVM, "drop", drop);

	lua_dofile(mLuaVM, file);
	return 0;
}

int GlobalScript::close() {
	lua_close(mLuaVM);
	return 0;
}


void GlobalScript::loadGlobals() {
	open(GLOBAL_FILE);
	lua_getglobal(mLuaVM, "gameName");
	engine->setGameName(lua_tostring(mLuaVM, lua_gettop(mLuaVM)));
	lua_getglobal(mLuaVM, "defaultBg");
	engine->setDefaultBg(lua_tostring(mLuaVM, lua_gettop(mLuaVM)));
	lua_getglobal(mLuaVM, "speechBackground");
	engine->setspeechBackground(lua_tostring(mLuaVM, lua_gettop(mLuaVM)));
	lua_getglobal(mLuaVM, "inventory");
	engine->setInventory(lua_tostring(mLuaVM, lua_gettop(mLuaVM)));
	lua_getglobal(mLuaVM, "inventoryBg");
	engine->setInventoryBg(lua_tostring(mLuaVM, lua_gettop(mLuaVM)));
	lua_getglobal(mLuaVM, "playerIcon");
	player->setIcon(lua_tostring(mLuaVM, lua_gettop(mLuaVM)));
	close();
}


int GlobalScript::say(lua_State *S)
{
	const char *say = lua_tostring(S, lua_gettop(S));
	printf(say);
	printf("\n");
	return 0;
}

int GlobalScript::hasItem(lua_State *S) 
{
	bool item = splayer->hasItem(lua_tostring(S, lua_gettop(S)));
	lua_pushboolean(S, item);
	return 1;
}

int GlobalScript::wait(lua_State *S) 
{
	waiting=true;
	waitTime=lua_tonumber(S, lua_gettop(S));
	scriptPause();
	return 0;
}

int GlobalScript::fadeIn(lua_State *S) 
{
	sengine->fadeIn(lua_tonumber(S, lua_gettop(S)));
	return 0;
}

int GlobalScript::fadeOut(lua_State *S) 
{
	sengine->fadeOut(lua_tonumber(S, lua_gettop(S)));
	return 0;
}

int GlobalScript::loadRoom(lua_State *S) 
{
	const char *roomStr = lua_tostring(S, lua_gettop(S));

	sroom->newRoom(roomStr);
	script->loadRoomGlobals();
	script->run("startRoom",sroom->getFile());
	return 0;
}

void GlobalScript::loadRoomGlobals() {
	open(room->getFile());
	lua_getglobal(mLuaVM, "backGround");

	room->setBackground(lua_tostring(mLuaVM, lua_gettop(mLuaVM)));
	engine->setBg(room->getBackground());
}

void GlobalScript::run(const char *function, const char *file) {
	open(file);
	lua_getglobal(mLuaVM, function);
	lua_call(mLuaVM, 0, 0);
}

void GlobalScript::lookItem(int index)
{
	std::string functionName = "item";
	functionName.append(items.at(index)->getName());
	functionName.append("Look");
	run(functionName.c_str(),GLOBAL_FILE);
}

void GlobalScript::talk(int x, int y)
{
	bool found=false;
	for (unsigned int i=0; i<npcs.size() && !found; i++) {
		if(intersectCheck(x, y, npcs.at(i)->getRect())) {
			speech->newSpeech(npcs.at(i));
			found=true;
		}
	}
	if (!found) {
		lua_getglobal(mLuaVM, "defaultTalk");
		lua_call(mLuaVM, 0, 0);
	}
}

int GlobalScript::pickUp(lua_State *S)
{
	const char *name=lua_tostring(S, lua_gettop(S));
	for (unsigned int i=0; i<sitems->size(); i++) {
		if(strcmp(sitems->at(i)->getName(),name)==0) {
			splayer->pickUp(sitems->at(i));
			return 0;
		}
	}
	return 0;
}

int GlobalScript::drop(lua_State *S)
{
	const char *name=lua_tostring(S, lua_gettop(S));
	splayer->drop(name);
	return 0;
}

int GlobalScript::addFrame(lua_State *S)
{
	int n=lua_gettop(S);
	if (n==6)	splayer->a->addFrame(lua_tonumber(S, lua_gettop(S)-5),
		lua_tonumber(S, lua_gettop(S)-4),
		lua_tonumber(S, lua_gettop(S)-3),
		lua_tonumber(S, lua_gettop(S)-2),
		lua_tonumber(S, lua_gettop(S)-1),
		lua_tostring(S, lua_gettop(S))
		);

	return 0;
}

int GlobalScript::addItem(lua_State *S)
{
	int n=lua_gettop(S);
	if (n==2)	sitems->push_back(new Item(lua_tostring(S, lua_gettop(S)-1),lua_tostring(S, lua_gettop(S))));

	return 0;
}

int GlobalScript::scriptPause() {
	while (waiting) {
		timer=timer+sengine->getTimePassed();
		if (timer>=waitTime) {
			waiting=false;
			timer=0;
			return 0;
		}
		sengine->gameLoop();
		sengine->renderLoop();
	}
	return 0;
}


int GlobalScript::addHotSpot(lua_State *S)
{
	int n=lua_gettop(S);
	
	if (n==5)	sroom->addHotSpot(new HotSpot(lua_tonumber(S, lua_gettop(S)-4),
		lua_tonumber(S, lua_gettop(S)-3),
		lua_tonumber(S, lua_gettop(S)-2),
		lua_tonumber(S, lua_gettop(S)-1),
		lua_tostring(S, lua_gettop(S))
		));
	return 0;
}

int GlobalScript::addObject(lua_State *S)
{
	int n=lua_gettop(S);
	
	if (n==5)	sroom->addObject(new Object(lua_tonumber(S, lua_gettop(S)-5),
		lua_tonumber(S, lua_gettop(S)-4),
		lua_tonumber(S, lua_gettop(S)-3),
		lua_tonumber(S, lua_gettop(S)-2),
		lua_tostring(S, lua_gettop(S)-1),
		lua_tostring(S, lua_gettop(S))
		));
	return 0;
}

int GlobalScript::walkTo(lua_State *S) {
	splayer->walkTo(lua_tonumber(S, lua_gettop(S) - 1), lua_tonumber(S, lua_gettop(S)));
	return 0;
}

int GlobalScript::enterScene(lua_State *S) {
	splayer->setPosition(lua_tonumber(S, lua_gettop(S) - 1), lua_tonumber(S, lua_gettop(S)));
	return 0;
}

int GlobalScript::set(lua_State *S) {
	bool found=false;
	std::string valstring="";
	int n=lua_gettop(S);
	if (n!=2) return 0;
	const char *name=lua_tostring(S, lua_gettop(S)-1);
	switch(lua_type(S, lua_gettop(S))) {
	case LUA_TNUMBER:
		valstring=lua_tostring(S, lua_gettop(S));
		break;
	case LUA_TBOOLEAN:
		valstring=(lua_toboolean(S, lua_gettop(S))==1) ? "true" : "false";
		break;
	case LUA_TSTRING:
		valstring=lua_tostring(S, lua_gettop(S));
		break;
	default:
		break;
	}
	const char *value = valstring.c_str();
	for (unsigned int i=0; i<variables.size() && !found; i++) {
		if (strcmp(variables.at(i).name,name)==0) {
			variables.at(i).value=(char *)realloc(variables.at(i).value,sizeof(value));
			strcpy(variables.at(i).value,value);
			variables.at(i).type=(int)lua_type(S,lua_gettop(S));
			found=true;
		}
	}
	if (!found) {
		GameVariable gv;
		gv.name=(char *)malloc(sizeof(name));
		strcpy(gv.name,name);
		gv.value=(char *)malloc(sizeof(value));
		gv.type=(int)lua_type(S,lua_gettop(S));
		strcpy(gv.value,value);
		variables.push_back(gv);
	}
	return 0;
}

int GlobalScript::get(lua_State *S) {
	bool found=false;
	for (unsigned int i=0; i<variables.size()&&!found; i++) {
		const char *name=lua_tostring(S, lua_gettop(S));
		if (strcmp(variables.at(i).name,name)==0) {
			switch(variables.at(i).type) {
				case LUA_TNUMBER:
					lua_pushnumber(S,atoi(variables.at(i).value));
					break;
				case LUA_TBOOLEAN:
					lua_pushboolean(S,(strcmp(variables.at(i).value,"true")==0) ? true : false);
					break;
				case LUA_TSTRING:
					lua_pushstring(S,variables.at(i).value);
					break;
				default:
					lua_pushnil(S);
					break;
			}
			found=true;
		}
	}
	if (!found) {
		lua_pushnil(S);
	}
	return 1;
}
void GlobalScript::action(Action act) {
	bool found=false;

	//for( unsigned int i = 0; i < objects.size() && !found; i++ ) {
	//	if (objects.at(i)->intersects(x, y)) found=true; objects.at(i);
	//}

	std::string functionName = "";
	HotSpot *hs = room->intersectsHotSpot(act.x, act.y);
	if (hs!=NULL) {		
		functionName.append("hs");
		functionName.append(hs->getName());
	} else {
		functionName.append("default");
	}

	switch (act.action) {
		case ACT_USE:
			functionName.append("Use");
		break;
		case ACT_LOOK:
			functionName.append("Look");
		break;
	}

	run(functionName.c_str(),room->getFile());
	act.x=NULL;
	act.y=NULL;
	act.action=NULL;
	player->setAction(act);
}

GlobalScript::GlobalScript(GameEngine *engines, Player *players, Room *rooms, Speech *speechs) {
	waiting=false;
	timer=0;
	waitTime=0;
	engine=engines;
	player=players;
	room=rooms;
	speech=speechs;
	sengine=engine;
	splayer=player;
	sroom=room;
	sspeech=speech;
	sitems=&items;
	snpcs=&npcs;
	script=this;
}

bool GlobalScript::intersectCheck(int x, int y, Rect rect) {
	if (x>=rect.x && x<=rect.x2 && y>=rect.y && y<=rect.y2) return true;
	return false;
}

bool GlobalScript::intersects(int x, int y) {
	HotSpot *hs = room->intersectsHotSpot(x, y);
	if (hs==NULL) return false;
	return true;
}
