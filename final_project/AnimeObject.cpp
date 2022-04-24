#include "AnimeObject.h"
#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include <stdio.h>
#include "constants.h"
#include "SDL_image.h"
#include "tile.h"


AnimeObject::AnimeObject(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b)
{
	renderer = ren;
	num = n;
	texture = new SDL_Texture * [num];

	for (int i = 0; i < num; i++)
	{

		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);

		SDL_Surface* imgSurface = IMG_Load(file);
		if (imgSurface == NULL)
		{
			printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
			exit(0);
		}
		else
		{
			SDL_SetColorKey(imgSurface, true, SDL_MapRGB(imgSurface->format, r, g, b));
			// Create texture from surface pixels	
			texture[i] = SDL_CreateTextureFromSurface(renderer, imgSurface);
			// Also, you can use IMG_LoadTexture() to replace IMG_Load and SDL_CreateTextureFromSurface
			// texture = IMG_LoadTexture(renderer, path);
			if (texture[i] == NULL)
			{
				printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
			}
			width = imgSurface->w;
			height = imgSurface->h;

			// Get rid of old loaded surface
			SDL_FreeSurface(imgSurface);
		}
	}

}
AnimeObject::AnimeObject(const char* path, int n, SDL_Renderer* ren)
{
	renderer = ren;
	num = n;
	texture = new SDL_Texture * [num];
	
	
	for (int i = 0; i < num; i++) 
	{

		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);

		SDL_Surface * imgSurface = IMG_Load(file);
		if (imgSurface == NULL)
		{
			printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
			exit(0);
		}
		else
		{
			// Create texture from surface pixels	
			texture[i] = SDL_CreateTextureFromSurface(renderer, imgSurface);
			// Also, you can use IMG_LoadTexture() to replace IMG_Load and SDL_CreateTextureFromSurface
			// texture = IMG_LoadTexture(renderer, path);
			if (texture[i] == NULL)
			{
				printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
			}
			width = imgSurface->w;
			height = imgSurface->h;

			// Get rid of old loaded surface
			SDL_FreeSurface(imgSurface);
		}
	}

}


Uint32 AnimeObject::changeData(Uint32 interval, void* param)
{
	AnimeObject* p = (AnimeObject*)param;
	if (p->time != 0)
	{
		p->frame = (p->frame + 1) % p->num;
		return interval;
	}
	else
	{
		return 0;
	}
}

void AnimeObject::startTimer(Uint32 t)
{
	time = t;
	timerID = SDL_AddTimer(time, changeData, this); // Set Timer callback
}

void AnimeObject::stopTimer()
{
	time = 0;
}

void AnimeObject::close()
{
	for (int i = 0; i < num; i++) {
		SDL_DestroyTexture(texture[i]);
	}
}

void AnimeObject::draw(SDL_Rect dst, SDL_Rect src) {
	SDL_Rect* d = &dst, * s = &src;
	//
//	if (dst.x == NULL)
//	{
//		d = NULL;
//	}
	if (src.x == NULL)
	{
		s = NULL;
	}

	SDL_RenderCopy(renderer, texture[frame], s, d);
}
/*
void AnimeObject::draw()
{
	SDL_Rect dst, src;
	dst.x = x;
	dst.y = y;
	dst.w = width;
	dst.h = height;

	//(texture)[frame].draw(renderer, dst, { NULL });
	
	SDL_Rect* d = &dst, * s = &src;
	//if (dst.x == NULL)
	//{
	//	d = NULL;
	//}
	if (src.x == NULL)
	{
		s = NULL;
	}

	SDL_RenderCopy(renderer, texture[frame], s, d);
}
*/

void AnimeObject::setPosition(int xx, int yy)
{
	x = xx;
	y = yy;
}

int AnimeObject::getWidth()
{
	return width;
}

int AnimeObject::getHeight() 
{
	return height;
}

int AnimeObject::getX() 
{
	return x;
}

int AnimeObject::getY() 
{
	return y;
}



void AnimeObject::setdetectCorner(SDL_Rect mc)
{
	
	if (velX >= 0)
	{
		detectCornerX[0][0] = (mc.x + (x - mc.x) * CAMERAW / WIDTH) * MAPTILEX / WIDTH;//up leftx
		detectCornerX[0][1] = (mc.y + (y - mc.y) * CAMERAH / HEIGHT) * MAPTILEY / HEIGHT;//      y
		detectCornerX[1][0] = (mc.x + ( width / SHRINK + x - mc.x + 2 * velX) * CAMERAW / WIDTH) * MAPTILEX / WIDTH;//up right
		detectCornerX[1][1] = (mc.y + (y - mc.y) * CAMERAH / HEIGHT) * MAPTILEY / HEIGHT;
		detectCornerX[2][0] = (mc.x + (x - mc.x) * CAMERAW / WIDTH) * MAPTILEX / WIDTH;//bottom left
		detectCornerX[2][1] = (mc.y + (height / SHRINK + y - mc.y) * CAMERAH / HEIGHT) * MAPTILEY / HEIGHT;
		detectCornerX[3][0] = (mc.x + ( width / SHRINK + x - mc.x + 2 * velX) * CAMERAW / WIDTH) * MAPTILEX / WIDTH;//bottom right 
		detectCornerX[3][1] = (mc.y + (height / SHRINK + y - mc.y) * CAMERAH / HEIGHT) * MAPTILEY / HEIGHT;
	}
	else if (velX < 0)
	{
		detectCornerX[0][0] = (mc.x + (x - mc.x + 2 * velX) * CAMERAW / WIDTH) * MAPTILEX / WIDTH;//up leftx
		detectCornerX[0][1] = (mc.y + (y - mc.y) * CAMERAH / HEIGHT) * MAPTILEY / HEIGHT;//      y
		detectCornerX[1][0] = (mc.x + ( width / SHRINK + x - mc.x) * CAMERAW / WIDTH) * MAPTILEX / WIDTH;//up right
		detectCornerX[1][1] = (mc.y + (y - mc.y) * CAMERAH / HEIGHT) * MAPTILEY / HEIGHT;
		detectCornerX[2][0] = (mc.x + (x - mc.x + 2 * velX) * CAMERAW / WIDTH) * MAPTILEX / WIDTH;//bottom left
		detectCornerX[2][1] = (mc.y + (height / SHRINK + y - mc.y) * CAMERAH / HEIGHT) * MAPTILEY / HEIGHT;
		detectCornerX[3][0] = (mc.x + ( width / SHRINK + x - mc.x) * CAMERAW / WIDTH) * MAPTILEX / WIDTH;//bottom right 
		detectCornerX[3][1] = (mc.y + (height / SHRINK + y - mc.y) * CAMERAH / HEIGHT) * MAPTILEY / HEIGHT;
	}

	if (velY <= 0)
	{
		detectCornerY[0][0] = (mc.x + (x - mc.x) * CAMERAW / WIDTH) * MAPTILEX / WIDTH;//up leftx
		detectCornerY[0][1] = (mc.y + (y - mc.y + 2 * velY) * CAMERAH / HEIGHT) * MAPTILEY / HEIGHT;//      y
		detectCornerY[1][0] = (mc.x + ( width / SHRINK + x - mc.x) * CAMERAW / WIDTH) * MAPTILEX / WIDTH;//up right
		detectCornerY[1][1] = (mc.y + (y - mc.y + 2 * velY) * CAMERAH / HEIGHT) * MAPTILEY / HEIGHT;
		detectCornerY[2][0] = (mc.x + (x - mc.x) * CAMERAW / WIDTH) * MAPTILEX / WIDTH;//bottom left
		detectCornerY[2][1] = (mc.y + (height / SHRINK + y - mc.y) * CAMERAH / HEIGHT) * MAPTILEY / HEIGHT;
		detectCornerY[3][0] = (mc.x + ( width / SHRINK + x - mc.x) * CAMERAW / WIDTH) * MAPTILEX / WIDTH;//bottom right 
		detectCornerY[3][1] = (mc.y + (height / SHRINK + y - mc.y) * CAMERAH / HEIGHT) * MAPTILEY / HEIGHT;
	}
	else if (velY > 0)
	{
		detectCornerY[0][0] = (mc.x + (x - mc.x) * CAMERAW / WIDTH) * MAPTILEX / WIDTH;//up leftx
		detectCornerY[0][1] = (mc.y + (y - mc.y) * CAMERAH / HEIGHT) * MAPTILEY / HEIGHT;//      y
		detectCornerY[1][0] = (mc.x + ( width / SHRINK + x - mc.x) * CAMERAW / WIDTH) * MAPTILEX / WIDTH;//up right
		detectCornerY[1][1] = (mc.y + (y - mc.y) * CAMERAH / HEIGHT) * MAPTILEY / HEIGHT;
		detectCornerY[2][0] = (mc.x + (x - mc.x) * CAMERAW / WIDTH) * MAPTILEX / WIDTH;//bottom left
		detectCornerY[2][1] = (mc.y + (height / SHRINK + y - mc.y + 2 * velY) * CAMERAH / HEIGHT) * MAPTILEY / HEIGHT;
		detectCornerY[3][0] = (mc.x + ( width / SHRINK + x - mc.x) * CAMERAW / WIDTH) * MAPTILEX / WIDTH;//bottom right 
		detectCornerY[3][1] = (mc.y + (height / SHRINK + y - mc.y + 2 * velY) * CAMERAH / HEIGHT) * MAPTILEY / HEIGHT;
	}
	
}

void AnimeObject::move(SDL_Rect mc) {
	printf("yDown: %d\n", yDown());

	if (jumpFlag)
	{
		velY = -10;
	}
	else if (yDown())
	{
		velY += 1;
	}
	else
	{
		velY = 0;
	}
	jumpFlag = 0;
	setdetectCorner(mc);
	moveOrNot();
//	setdetectP(mc);
//	printf("VX: %d\n", velX);
	printf("VY: %d\n", velY);
	if (x +  width / SHRINK >= 2 * WIDTH - CAMERAW)
		x = WIDTH + width / SHRINK;
	if (y + height / SHRINK >= 2 * HEIGHT + CAMERAH)
		y = HEIGHT + height / SHRINK;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
}

bool AnimeObject::xRight()
{
	
	if (tile[detectCornerX[1][1]][detectCornerX[1][0]] == 0 && tile[detectCornerX[3][1]][detectCornerX[3][0]] == 0)
		return true;
	return false;
}

bool AnimeObject::xLeft()
{
	if (tile[detectCornerX[2][1]][detectCornerX[2][0]] == 0 && tile[detectCornerX[0][1]][detectCornerX[0][0]]==0)
		return true;
	return false;
}

bool AnimeObject::yUp()
{
	if (tile[detectCornerY[1][1]][detectCornerY[1][0]] == 0 && tile[detectCornerY[0][1]][detectCornerY[0][0]] == 0)
		return true;
	return false;
}

bool AnimeObject::yDown()
{
	if (tile[detectCornerY[2][1]][detectCornerY[2][0]] == 0 && tile[detectCornerY[3][1]][detectCornerY[3][0]] == 0)
		return true;
	return false;
}

void AnimeObject::moveOrNot()
{

	if (velX > 0)
	{
		if (xRight())
		{
			x+=velX;			
		}
	}
	else if (velX < 0)
	{
		if (xLeft())
		{	
			x += velX;
		}
	}

	if (velY < 0)
	{
		if (yUp())
		{	
			y += velY;	
		}
	}
	else if (velY > 0)
	{
		if (yDown())
		{
			y += velY;
		}
	}
/*
	
	if (tile[detectP[1][1]][detectP[1][0]] == 0 )
	{
		if (velX > 0)
			x += velX;
	}
	if (tile[detectP[2][1]][detectP[2][0]] == 0 )
	{
		if (velX < 0)
			x += velX;
	}
	if (tile[detectP[0][1]][detectP[0][0]] == 0 )
	{
		if (velY < 0)
			y += velY;
	}
	if (tile[detectP[3][1]][detectP[3][0]] == 0)
	{
		if (velY > 0)
			y += velY;
	}
*/
}

int AnimeObject::getVY() {
	return velY;
}
void AnimeObject::setVY(int yy) {
	velY = yy;
}
int AnimeObject::getVX() {
	return velX;
}
void AnimeObject::setVX(int xx) {
	velX = xx;
}
void AnimeObject::setJumpFlag(bool f)
{
	jumpFlag = f;
}