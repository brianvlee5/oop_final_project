#include <stdio.h>
#include <SDL.h>

#include "Collision.h"
#include "constants.h"
#include "tile.h"

Collision::Collision()
{
	mapnow = chx = chy = 0;

}


void Collision::changemap(int n)
{
	mapnow = n;
}

void Collision::setcamera(SDL_Rect c)
{
	mapcamera = c;
}

bool Collision::right(int charx, int chary)
{
	chx = mapcamera.x + (charx - mapcamera.x) * CAMERAW / WIDTH;
	chy = mapcamera.y + (chary - mapcamera.y) * CAMERAH / HEIGHT;
	int tilex, tiley;
	tilex = chx / (WIDTH / 30);
	tiley = chy / (HEIGHT / 20);
	printf("chx: %d\nchy: %d\n", chx, chy);
	printf("tilex: %d\ntiley: %d\n", tilex, tiley);
	
	if (tile[tiley][tilex] == 1)
	{
		printf("false\n");
		return false;
	}
	printf("true\n");
	return true;
		
}