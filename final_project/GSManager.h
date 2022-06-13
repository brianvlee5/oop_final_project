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
#include "AnimeObject2.h"
#include "Coordinate.h"
#include "Attack.h"
#include "Image.h"
#include "Monster.h"
#include "MonsterA.h"
#include "MonsterB.h"
#include "MonsterC.h"
#include "MonsterD.h"
#include "MonsterP.h"
#include "MonsterI.h"
#include "MAttack.h"
#include "NPC.h"

class GSManager
{
public:
	GSManager();
	void initialize();
	void startGame(RenderWindow& window);
	void GamePlay(RenderWindow & window);
	void MainMenu(RenderWindow& window);
	void LoadGamePlay(RenderWindow& window);
	void GameClear(RenderWindow& window);
	void setGameState(int gs);
	int getGameState();
	void InitMonsters(std::vector<Monster*>& mv);
	void drawCoinNum(std::vector<Object>& cv, RenderWindow& window, int coinn, Object& Coin);
private:
	
	SDL_Event ev;
	bool quit;
	int GameState;
};

