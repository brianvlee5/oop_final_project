#include "Coordinate.h"



Coordinate::Coordinate()
{
	initialize();
}

Coordinate::Coordinate(int cx, int cy)
{
	printCamX = cx;
	printCamY = cy;
}

void Coordinate::initialize()
{
	printCamX = 0;
	printCamY = 0;
}

void Coordinate::calMapCamera(Map m, AnimeObject2& mainch)
{
	SDL_Rect temp = m.getcamera();
	printCamX = (mainch.getX() - temp.x);
	printCamY = (mainch.getY() - temp.y);

}

void Coordinate::calMapCamera(Map m, Monster& mainch)
{
	SDL_Rect temp = m.getcamera();
	printCamX = (mainch.getX() - temp.x);
	printCamY = (mainch.getY() - temp.y);

}

void Coordinate::calMapCamera(Map m, MAttack& matk)
{
	SDL_Rect temp = m.getcamera();
	printCamX = (matk.getX() - temp.x);
	printCamY = (matk.getY() - temp.y);

}

void Coordinate::calMapCamera(Map m, Attack& mainch)
{
	SDL_Rect temp = m.getcamera();
	printCamX = (mainch.getX() - temp.x);
	printCamY = (mainch.getY() - temp.y);
}

void Coordinate::calMapCamera(Map m, MonsterC& mainch)
{
	SDL_Rect temp = m.getcamera();
	printCamX = (mainch.getX() - temp.x);
	printCamY = (mainch.getY() - temp.y);

}
void Coordinate::calMapCamera(Map m, MonsterD& mainch)
{
	SDL_Rect temp = m.getcamera();
	printCamX = (mainch.getX() - temp.x);
	printCamY = (mainch.getY() - temp.y);

}

int Coordinate::getpCX()
{
	return printCamX;
}

int Coordinate::getpCY()
{
	return printCamY;
}
