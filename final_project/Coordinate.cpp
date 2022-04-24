#include "Coordinate.h"


Coordinate::Coordinate()
{
	printCamX = 0;
	printCamY = 0;
}

void Coordinate::calMapCamera(Map m, AnimeObject mainch)
{
	SDL_Rect temp = m.getcamera(mainch);
	printCamX = mainch.getX() - temp.x;
	printCamY = mainch.getY() - temp.y;
}

int Coordinate::getpCX()
{
	return printCamX;
}

int Coordinate::getpCY()
{
	return printCamY;
}
