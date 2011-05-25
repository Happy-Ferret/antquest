#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <SDL.h>

extern "C"
{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

struct Rect
{
	int x;
	int y;
	int x2;
	int y2;
};

struct Pos {
	float x;
	float y;
};

struct Option {
	const char *text;
	bool enabled;
};

struct Action {
	int x;
	int y;
	int action;
};

struct WalkArea {
	Rect r;
	int scale;
};

struct GameVariable {
	char *name;
	char *value;
	int type;
};

#define ACT_USE 0
#define ACT_LOOK 1
#define MAX_ARRAY 20
#define MAX_FRAMES 20
#define MAX_ANIMS 20
#define GLOBAL_FILE "global.lua"

#include "Cursors.h"
#include "Item.h"
#include "Animation.h"
#include "Player.h"
#include "HotSpot.h"
#include "Object.h"
#include "NPC.h"
#include "Speech.h"
#include "Room.h"
#include "GlobalScript.h"
#include "GameEngine.h"
