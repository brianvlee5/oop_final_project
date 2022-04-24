#pragma once
#include <SDL.h>
#include "Map.h"
#include "AnimeObject.h"

class Coordinate
{
public:
	Coordinate();
	void calMapCamera(Map, AnimeObject);
	int getpCX();
	int getpCY();
private:
	int printCamX;
	int printCamY;
};