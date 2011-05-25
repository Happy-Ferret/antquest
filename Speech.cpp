#include "AntQuest.h"
	Option options[MAX_ARRAY];

	Speech::Speech(){
	}

int Speech::newSpeech(NPC *snpc) {
	mLuaVM = lua_open();

	if(mLuaVM == NULL) {
		return -1;
	}

	lua_baselibopen(mLuaVM);
	lua_iolibopen(mLuaVM);
	lua_strlibopen(mLuaVM);
	lua_mathlibopen(mLuaVM);
	lua_register(mLuaVM, "enableOption", enableOption);
	lua_register(mLuaVM, "disableOption", disableOption);
	lua_register(mLuaVM, "addOption", addOption);
	lua_register(mLuaVM, "closeSpeech", closeSpeech);
	lua_register(mLuaVM, "say", say);

	lua_dofile(mLuaVM,snpc->getSpeech());

	loadSpeech();
	return 0;
}

void Speech::loadSpeech() {
	lua_getglobal(mLuaVM, "loadSpeech");
	lua_call(mLuaVM, 0, 0);
}

int Speech::addOption(lua_State *S)
{
	int n=lua_gettop(S);
	
	if (n==2) {
		int index = lua_tonumber(S, lua_gettop(S)-1);
		if (index<MAX_ARRAY) {
			options[index].text=lua_tostring(S, lua_gettop(S));
			options[index].enabled=false;
		}
	}
	return 0;
}

int Speech::enableOption(lua_State *S)
{
	int n=lua_gettop(S);
	
	if (n==1) {
		int index = lua_tonumber(S, lua_gettop(S)-1);
		if (index<MAX_ARRAY) {
			options[index].enabled=true;
		}
	}
	return 0;
}

int Speech::disableOption(lua_State *S)
{
	int n=lua_gettop(S);
	
	if (n==1) {
		int index = lua_tonumber(S, lua_gettop(S)-1);
		if (index<MAX_ARRAY) {
			options[index].enabled=false;
		}
	}
	return 0;
}

int Speech::closeSpeech(lua_State *S)
{
	return 0;
}

int Speech::say(lua_State *S)
{
	const char *say = lua_tostring(S, lua_gettop(S));
	printf(say);
	printf("\n");
	return 0;
}