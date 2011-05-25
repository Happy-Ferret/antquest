#include "AntQuest.h"
GameEngine::GameEngine() {
	currentAction=1;
	rcSpeechSprite.x=0;
	rcSpeechSprite.y=353;
	rcInventorySprite.x=32;
	rcInventorySprite.y=389;
	inventoryPos.x=32;
	inventoryPos.x2=107;
	inventoryPos.y=389;
	inventoryPos.y2=453;
	for (int i=0; i<4; i++) {
		speechChoice[i].x=0;
		speechChoice[i].y=400+(i*12);
		speechChoice[i].x2=640;
		speechChoice[i].y2=412+(i*12);
	}
	time=0;
	diff=0;
	lastTime=0;
	cursors = new Cursors();
	quit=false;
	fading=false;
	fadingIn=false;
	inventoryOpen=false;
	alpha = 255;
	loadSDL();
}

void GameEngine::setScript(GlobalScript *gscript) {
	script=gscript;
	SDL_WM_SetCaption(gameName, gameName);
	SDL_Surface* temp = SDL_LoadBMP(defaultBg);
	bg = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	temp = SDL_LoadBMP(speechBackground);
	speechSurface = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	temp   = SDL_LoadBMP(script->player->getIcon());
	playerSprite = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	temp   = SDL_LoadBMP(inventory);
	inventorySurface = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	temp   = SDL_LoadBMP(inventoryBg);
	inventoryBgSurface = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
}

int GameEngine::loadSDL() {
		/// SDL LOAD UP GUBBINS

	//initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		return -1;
	}

	//create a surface for the game window

	screen = SDL_SetVideoMode(640, 480, 0, 0);
	SDL_Surface* temp = SDL_CreateRGBSurface( SDL_SWSURFACE | SDL_SRCALPHA, 640, 480, 32, 0xff000000,0x00ff0000,0x0000ff00,0x000000ff);
	alphaScreen = SDL_DisplayFormat( temp );
	SDL_FreeSurface( temp );

	return 0;
}

int GameEngine::cleanSDL() {
	SDL_FreeSurface(bg);
	SDL_FreeSurface(playerSprite);
	SDL_FreeSurface(speechSurface);
	SDL_FreeSurface(screen);
	SDL_Quit();
	return 0;
}

bool GameEngine::renderLoop() {
	if(quit || script==NULL) return false;
	SDL_BlitSurface(bg, NULL, screen, NULL);

	SDL_BlitSurface(playerSprite, &rcAnimation, screen, &rcPlayerSprite);
	for (unsigned int i=0; i< script->room->getNumberofObjects(); i++) {
		SDL_BlitSurface(script->room->getObject(i)->getSurface(), NULL, screen, &script->room->getObject(i)->getRect());
	}
	if(script->player->isTalking()) {
		SDL_BlitSurface(speechSurface, NULL, screen, &rcSpeechSprite);
	} else if (inventoryOpen) {
		SDL_BlitSurface(inventoryBgSurface, NULL, screen, NULL);
	}

	if (!inventoryOpen) {
		SDL_BlitSurface(inventorySurface, NULL, screen, &rcInventorySprite);
	}
	if(fading) {
		SDL_SetAlpha( alphaScreen, SDL_SRCALPHA, alpha);
		SDL_BlitSurface(alphaScreen, NULL, screen, NULL);
	}
	SDL_UpdateRect(screen,0, 0, 0, 0);
	return true;
}

bool GameEngine::gameLoop() {
	if(quit || script==NULL) return false;
		time = SDL_GetTicks();
		diff = time - lastTime;
		lastTime = time;

		script->player->walk(diff);
		
		if (!(script->player->isWalking()) && script->player -> getAction().x!=NULL) {
			script->action(script->player->getAction());
		}
		if (fading) {
			if (SDL_GetTicks() - fadeTime > fadeRate) {
				fadeTime=SDL_GetTicks();
				if (fadingIn) {
					if (alpha<=0) {
						alpha = 255;
						fading=false;
					} else {
						alpha--;
					}
				} else {
					if (alpha >=255) {
						alpha = 255;
					} else {
						alpha++;
					}
				}
			}
		}

		if(SDL_PollEvent(&event))
		{

			switch(event.type)
			{
			case SDL_QUIT: { quit=true; return false; break; }

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				case SDLK_ESCAPE: {	quit=true; return false; break; }
				}
			break;
			case SDL_MOUSEBUTTONDOWN:
				switch(event.button.button)
				{
				case SDL_BUTTON_LEFT:
					if (fading) break;
					if (script->player->isTalking()) {
						for (int i=0; i<4; i++) {
							if (intersectCheck(event.button.x, event.button.y, speechChoice[i])) printf("%i \n", i);
						}
					} else {
						if (intersectCheck(event.button.x, event.button.y, inventoryPos)) {inventoryOpen=true; break;}
						Action act;
						act.x=event.button.x;
						act.y=event.button.y;
						act.action=currentAction;
						switch (currentAction) {
								case 0:
									script->player->walkTo(event.button.x, event.button.y);
									script->player->setAction(act);
								break;
								case 1:
									script->player->walkTo(event.button.x, event.button.y);
									script->player->setAction(act);
								break;
								case 2:
									script->player->walkTo(event.button.x, event.button.y);
								break;
								case 3:
									script->player->walkTo(event.button.x, event.button.y);
									script->talk(event.button.x, event.button.y);
								break;
						}
					}
				break;
				case SDL_BUTTON_RIGHT:
					if (fading) break;
					if(inventoryOpen) { inventoryOpen=false; break; }
					switch (currentAction) {
							case 0:
								currentAction=1; SDL_SetCursor(cursors->getCursor(1)); 
							break;
							case 1:
								currentAction=2; SDL_SetCursor(cursors->getCursor(2)); 
							break;
							case 2:
								currentAction=3; SDL_SetCursor(cursors->getCursor(3));
							break;
							case 3:
								currentAction=0; SDL_SetCursor(cursors->getCursor(0));
							break;
					}
				break;
				}
			break;
			case SDL_MOUSEMOTION:
				bool mouseOver=false;
				bool is = script->intersects(event.motion.x, event.motion.y);
				if (is != NULL) mouseOver=true;
				switch (currentAction) {
							case 0:
								if (mouseOver) {
									SDL_SetCursor(cursors->getCursor(4)); 
								} else {
									SDL_SetCursor(cursors->getCursor(0)); 
								}
							break;
							case 1:
								if (mouseOver) {
									SDL_SetCursor(cursors->getCursor(5)); 
								} else {
									SDL_SetCursor(cursors->getCursor(1)); 
								}
							break;
							case 2:
							break;
							case 3:
							break;
				}
			break;
			}
		}
		rcAnimation=script->player->getCurrentFrame(0);
		rcPlayerSprite.x=(int)script->player->position().x-(rcAnimation.w/2);
		rcPlayerSprite.y=(int)script->player->position().y-(rcAnimation.h);
		return true;
}

void GameEngine::setBg(const char *bgFile) {
	SDL_Surface* temp =SDL_LoadBMP(bgFile);
	bg = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
}

bool GameEngine::intersectCheck(int x, int y, Rect rect) {
	if (x>=rect.x && x<=rect.x2 && y>=rect.y && y<=rect.y2) return true;
	return false;
}

void GameEngine::setGameName(const char *cgameName) {
	gameName=(char *)malloc(sizeof(cgameName));
	strcpy(gameName,cgameName);
}
void GameEngine::setDefaultBg(const char *cdefaultBg) {
	defaultBg=(char *)malloc(sizeof(cdefaultBg));
	strcpy(defaultBg,cdefaultBg);
}
void GameEngine::setspeechBackground(const char *cspeechBackground) {
	speechBackground=(char *)malloc(sizeof(cspeechBackground));
	strcpy(speechBackground,cspeechBackground);
}
void GameEngine::setInventory(const char *ci) {
	inventory=(char *)malloc(sizeof(ci));
	strcpy(inventory,ci);
}
void GameEngine::setInventoryBg(const char *ciBg) {
	inventoryBg=(char *)malloc(sizeof(ciBg));
	strcpy(inventoryBg,ciBg);
}

int GameEngine::getTimePassed() {
	return diff;
}

void GameEngine::fadeIn(int time) {
	fading=true;
	fadingIn=true;
	alpha=255;
	fadeRate=time;
	fadeTime=SDL_GetTicks();
}

void GameEngine::fadeOut(int time) {
	fading=true;
	fadingIn=false;
	alpha=0;
	fadeRate=time;
	fadeTime=SDL_GetTicks();
}