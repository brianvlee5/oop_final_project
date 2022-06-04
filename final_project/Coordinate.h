#pragma once
#include <SDL.h>
#include "Map.h"
#include "AnimeObject2.h"
#include "Attack.h"
#include "Monster.h"
#include "MonsterC.h"
#include "constants.h"
#include <stdio.h>


class Coordinate
{
public:
	Coordinate();

	void calMapCamera(Map, AnimeObject2&);
	void calMapCamera(Map, Monster&);
	void calMapCamera(Map, Attack&);
	void calMapCamera(Map, MonsterC&);
	int getpCX();
	int getpCY();
private:
	int printCamX;
	int printCamY;
};