#pragma once
#include <SDL.h>
#define WIDTH 1920
#define HEIGHT 1280
#define ALLREGION -1
#define WINDOWW 960
#define WINDOWH 640
#define CAMERAW   WINDOWW
#define CAMERAH   WINDOWH
#define VELOCITY 4
#define SHRINK 1
#define MAPTILEX 60
#define MAPTILEY 40
#define NO_TRANSPARENT_BG {0, 0, 0, 0}
#define MAXHP 8
#define SOLID 100
#define SHADED 101
#define BLENDED 102
#define PROPNUM 6

//AImode
#define WANDER 0
#define TRACE 1
#define WAIT 2
#define TELEPORT 3
#define FLY 4
#define FLYBACK 5
#define STOP 6
#define THROW 7

//wander mode
#define LEFT 0
#define RIGHT 1
#define WALLL 0
#define WALLR 1
#define PLATFORMLB 2
#define PLATFORMRB 3
#define FLOOR 4

//for character
#define RUSHCD 1500  //milisecond
#define RUSHTIMER 50

//for attack
#define ATTACKNUM 10

//for music
#define MUSIC 10
#define EFFECT 11
#define FOREVER -1
#define ONE 0
#define ALLCHANNEL -1

//for GSM
#define MAINMENU 0
#define GAMEPLAY 1
#define LOADGAMEPLAY 2
#define GAMECLEAR 3


//for gameplay state
#define PLAY 0
#define PAUSE 1
#define SAVE 2
#define OVER 3

//for menu states
#define MENU 0
#define LOAD 1

//for saves
struct MapSave {
	int mapnum;
};

struct MainchSave {
	int mapnum;
	int health;
	int x, y;
	int c;
};


//monster start points
const SDL_Point MDStartP = { 57 * WIDTH / MAPTILEX, 25 * HEIGHT / MAPTILEY };
