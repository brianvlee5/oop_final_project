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
	GSManager(bool q, int gs);
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

	friend void pauseEvents(SDL_Event e, GSManager* gsm, int& state, AnimeObject2& mch, vector<Attack>& atk, vector<Monster*>& mv);
	friend void MenuEvents(SDL_Event e, GSManager* gsm, int& state);
	friend void ClearEvents(SDL_Event e, GSManager* gsm);
	friend void OverEvents(SDL_Event e, GSManager* gsm);
private:
	
	SDL_Event ev;
	bool quit;
	int GameState;
};

