class Speech {
public:
	Speech();
	int newSpeech(NPC *snpc);
	void loadSpeech();
	static int enableOption(lua_State* S);
	static int disableOption(lua_State* S);
	static int addOption(lua_State* S);
	static int closeSpeech(lua_State* S);
	static int say(lua_State* S);
private:
	lua_State* mLuaVM;
};
