#pragma once
//#include "AnimeObject.h"

class Collision 
{
public:
	Collision();
	void changemap(int);
	void setcamera(SDL_Rect);
	bool right(int, int);
	bool left(int, int);
	bool up(int, int);
	bool down(int, int);
	
private:
	int mapnow;
	SDL_Rect mapcamera;//used to calculate the position of the character on the map
	int chx, chy;//the real x y of character
};