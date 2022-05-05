#pragma once
#include <SDL.h>
#include "Map.h"
#include "AnimeObject.h"
#include "Attack.h"
#include "Monster.h"
#include "constants.h"
#include <stdio.h>

class Coordinate
{
public:
	Coordinate();
	void calMapCamera(Map, AnimeObject&);
	void calMapCamera(Map, Monster);
	void calMap(Map, Attack&);
	int getpCX();
	int getpCY();
private:
	int printCamX;
	int printCamY;
};