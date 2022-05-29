#pragma once
//original
#include <stdio.h>
#include <stdlib.h>
#include <vector>

//sdl related
#include <SDL.h>
#include <SDL_ttf.h>
#include "SDL2_gfxPrimitives.h"
#include "SDL_image.h"
#include "event.h"
#include "Mixer.h"
#include "Text.h"

//self added
#include "constants.h"
#include "System.h"
#include "RenderWindow.h"
#include "Map.h"
#include "StaticObject.h"
#include "AnimeObject.h"
#include "AnimeObject2.h"
#include "Coordinate.h"
#include "Attack.h"
#include "Image.h"
#include "Monster.h"
#include "MonsterA.h"
#include "MonsterP.h"

class GSManager
{
public:
	GSManager();
	void startGame(RenderWindow& win);
	void GamePlay(RenderWindow &window);
	void setGameState(int gs);
	int getGameState();
private:
	
	SDL_Event ev;
	bool quit;
	int GameState;
};

