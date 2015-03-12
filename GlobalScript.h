class GameEngine;
class GlobalScript {
public:
	GlobalScript(GameEngine *engine, Player *player, Room *room, Speech *speech);
	int open(const char *file);
	int close();
	bool intersects(int x, int y);
	static int say(lua_State *S);
	static int hasItem(lua_State *S);
	static int loadRoom(lua_State *S);
	static int addItem(lua_State *S);
	static int addFrame(lua_State *S);
	static int enterScene(lua_State *S);
	static int walkTo(lua_State *S);
	static int addHotSpot(lua_State *S);
	static int addObject(lua_State *S);
	static int wait(lua_State *S);
	static int fadeIn(lua_State *S);
	static int fadeOut(lua_State *S);
	static int set(lua_State *S);
	static int get(lua_State *S);
	static int pickUp(lua_State *S);
	static int drop(lua_State *S);
	void loadGlobals();
	void loadRoomGlobals();
	void lookItem(int index);
	void talk(int x, int y);
	void run(const char *function,const char *file);
	GameEngine* engine;
	Player *player;
	Room *room;
	Speech *speech;
	std::vector<Item*> items;
	std::vector<NPC*> npcs;
	static int scriptPause();
	void action(Action act);
	bool intersectCheck(int x, int y, Rect rect);
private:
	lua_State* mLuaVM;
};