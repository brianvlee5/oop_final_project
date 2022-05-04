#include "Coordinate.h"
#include "constants.h"
#include <stdio.h>


Coordinate::Coordinate()
{
	printCamX = 0;
	printCamY = 0;
}

void Coordinate::calMapCamera(Map m, AnimeObject mainch)
{
	SDL_Rect temp = m.getcamera();
	printCamX = (mainch.getX() - temp.x);
	printCamY = (mainch.getY() - temp.y);
	printf("prtcx: %d  prtcy: %d\n", printCamX, printCamY);
}

int Coordinate::getpCX()
{
	return printCamX;
}

int Coordinate::getpCY()
{
	return printCamY;
}
