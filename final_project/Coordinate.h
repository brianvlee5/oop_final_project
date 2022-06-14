#pragma once
#include <SDL.h>
#include "Map.h"
#include "Object.h"
#include "AnimeObject2.h"
#include "Attack.h"
#include "Monster.h"
#include "MonsterC.h"
#include "MonsterD.h"
#include "constants.h"
#include <stdio.h>
#include "MAttack.h"

class Coordinate
{
public:
	Coordinate();
	Coordinate(int cx, int cy);
	void initialize();
	void calMapCamera(Map, AnimeObject2&);
	void calMapCamera(Map, Object&);
	void calMapCamera(Map, Monster&);
	void calMapCamera(Map, Attack&);
	void calMapCamera(Map, MonsterC&);
	void calMapCamera(Map, MonsterD&);
	void calMapCamera(Map, MAttack&);
	int getpCX();
	int getpCY();
private:
	int printCamX;
	int printCamY;
};