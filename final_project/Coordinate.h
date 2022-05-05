#pragma once
#include <SDL.h>
#include "Map.h"
#include "AnimeObject.h"
#include "Monster.h"

class Coordinate
{
public:
	Coordinate();
	void calMapCamera(Map, AnimeObject);
	void calMapCamera(Map, Monster);
	int getpCX();
	int getpCY();
private:
	int printCamX;
	int printCamY;
};