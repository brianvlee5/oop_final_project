#pragma once
#include <SDL.h>
#include "Map.h"
#include "AnimeObject.h"
#include "Attack.h"

class Coordinate
{
public:
	Coordinate();
	void calMapCamera(Map, AnimeObject&);
	void calMap(Map, Attack&);
	int getpCX();
	int getpCY();
private:
	int printCamX;
	int printCamY;
};