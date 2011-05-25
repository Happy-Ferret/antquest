#include "AntQuest.h"

int main(int argc, char* argcv[])
{
	Player *player = new Player();
	Room *room = new Room();
	Speech *speech = new Speech();
	GameEngine *engine = new GameEngine();
	GlobalScript *script = new GlobalScript(engine, player, room, speech);

	Animation *a=new Animation();
	a->addAnim("walkLeft");
	a->addAnim("walkRight");
	a->addAnim("stationaryDown");
	a->setAnim("stationaryDown");
	player->setAnimation(a);

	script->loadGlobals();
	engine->setScript(script);

	script->run("gameStart",GLOBAL_FILE);

	while(engine->gameLoop() && engine->renderLoop());

	return 0;
}
