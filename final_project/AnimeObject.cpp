#include "AnimeObject.h"
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
	timerID = SDL_AddTimer(time, changeData, this);
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

/*
void AnimeObject::setdetectCorner(SDL_Rect mc)
{
	if (velX >= 0)
	{
		detectCornerX[0][0] = (mc.x + (x - mc.x) * CAMERAW / WINDOWW) * MAPTILEX / WIDTH;//up leftx
		detectCornerX[0][1] = (mc.y + (y - mc.y) * CAMERAH / WINDOWH) * MAPTILEY / HEIGHT;//      y
		detectCornerX[1][0] = (mc.x + ( width / SHRINK + x - mc.x + 2 * velX) * CAMERAW / WINDOWW) * MAPTILEX / WIDTH;//up right
		detectCornerX[1][1] = (mc.y + (y - mc.y) * CAMERAH / WINDOWH) * MAPTILEY / HEIGHT;
		detectCornerX[2][0] = (mc.x + (x - mc.x) * CAMERAW / WINDOWW) * MAPTILEX / WIDTH;//bottom left
		detectCornerX[2][1] = (mc.y + (height / SHRINK + y - mc.y) * CAMERAH / WINDOWH) * MAPTILEY / HEIGHT;
		detectCornerX[3][0] = (mc.x + ( width / SHRINK + x - mc.x + 2 * velX) * CAMERAW / WINDOWW) * MAPTILEX / WIDTH;//bottom right 
		detectCornerX[3][1] = (mc.y + (height / SHRINK + y - mc.y) * CAMERAH / WINDOWH) * MAPTILEY / HEIGHT;
	}
	else if (velX < 0)
	{
		detectCornerX[0][0] = (mc.x + (x - mc.x + 2 * velX) * CAMERAW / WINDOWW) * MAPTILEX / WIDTH;//up leftx
		detectCornerX[0][1] = (mc.y + (y - mc.y) * CAMERAH / WINDOWH) * MAPTILEY / HEIGHT;//      y
		detectCornerX[1][0] = (mc.x + ( width / SHRINK + x - mc.x) * CAMERAW / WINDOWW) * MAPTILEX / WIDTH;//up right
		detectCornerX[1][1] = (mc.y + (y - mc.y) * CAMERAH / WINDOWH) * MAPTILEY / HEIGHT;
		detectCornerX[2][0] = (mc.x + (x - mc.x + 2 * velX) * CAMERAW / WINDOWW) * MAPTILEX / WIDTH;//bottom left
		detectCornerX[2][1] = (mc.y + (height / SHRINK + y - mc.y) * CAMERAH / WINDOWH) * MAPTILEY / HEIGHT;
		detectCornerX[3][0] = (mc.x + ( width / SHRINK + x - mc.x) * CAMERAW / WINDOWW) * MAPTILEX / WIDTH;//bottom right 
		detectCornerX[3][1] = (mc.y + (height / SHRINK + y - mc.y) * CAMERAH / WINDOWH) * MAPTILEY / HEIGHT;
	}

	if (velY <= 0)
	{
		detectCornerY[0][0] = (mc.x + (x - mc.x) * CAMERAW / WINDOWW) * MAPTILEX / WIDTH;//up leftx
		detectCornerY[0][1] = (mc.y + (y - mc.y + 2 * velY) * CAMERAH / WINDOWH) * MAPTILEY / HEIGHT;//      y
		detectCornerY[1][0] = (mc.x + ( width / SHRINK + x - mc.x) * CAMERAW / WINDOWW) * MAPTILEX / WIDTH;//up right
		detectCornerY[1][1] = (mc.y + (y - mc.y + 2 * velY) * CAMERAH / WINDOWH) * MAPTILEY / HEIGHT;
		detectCornerY[2][0] = (mc.x + (x - mc.x) * CAMERAW / WINDOWW) * MAPTILEX / WIDTH;//bottom left
		detectCornerY[2][1] = (mc.y + (height / SHRINK + y - mc.y) * CAMERAH / WINDOWH) * MAPTILEY / HEIGHT;
		detectCornerY[3][0] = (mc.x + ( width / SHRINK + x - mc.x) * CAMERAW / WINDOWW) * MAPTILEX / WIDTH;//bottom right 
		detectCornerY[3][1] = (mc.y + (height / SHRINK + y - mc.y) * CAMERAH / WINDOWH) * MAPTILEY / HEIGHT;
	}
	else if (velY > 0)
	{
		detectCornerY[0][0] = (mc.x + (x - mc.x) * CAMERAW / WINDOWW) * MAPTILEX / WIDTH;//up leftx
		detectCornerY[0][1] = (mc.y + (y - mc.y) * CAMERAH / WINDOWH) * MAPTILEY / HEIGHT;//      y
		detectCornerY[1][0] = (mc.x + ( width / SHRINK + x - mc.x) * CAMERAW / WINDOWW) * MAPTILEX / WIDTH;//up right
		detectCornerY[1][1] = (mc.y + (y - mc.y) * CAMERAH / WINDOWH) * MAPTILEY / HEIGHT;
		detectCornerY[2][0] = (mc.x + (x - mc.x) * CAMERAW / WINDOWW) * MAPTILEX / WIDTH;//bottom left
		detectCornerY[2][1] = (mc.y + (height / SHRINK + y - mc.y + 2 * velY) * CAMERAH / WINDOWH) * MAPTILEY / HEIGHT;
		detectCornerY[3][0] = (mc.x + ( width / SHRINK + x - mc.x) * CAMERAW / WINDOWW) * MAPTILEX / WIDTH;//bottom right 
		detectCornerY[3][1] = (mc.y + (height / SHRINK + y - mc.y + 2 * velY) * CAMERAH / WINDOWH) * MAPTILEY / HEIGHT;
	}
}*/

void AnimeObject::setdetectCorner()
{
	if (velX >= 0)
	{
		detectCornerX[0][0] = x * MAPTILEX / WIDTH;//up leftx
		detectCornerX[0][1] = y * MAPTILEY / HEIGHT;//      y
		detectCornerX[1][0] = (width / SHRINK + x + 2 * velX) * MAPTILEX / WIDTH;//up right
		detectCornerX[1][1] = y  * MAPTILEY / HEIGHT;
		detectCornerX[2][0] = x  * MAPTILEX / WIDTH;//bottom left
		detectCornerX[2][1] = (height / SHRINK + y )  * MAPTILEY / HEIGHT;
		detectCornerX[3][0] = (width / SHRINK + x + 2 * velX) * MAPTILEX / WIDTH;//bottom right 
		detectCornerX[3][1] = (height / SHRINK + y )  * MAPTILEY / HEIGHT;
	}
	else if (velX < 0)
	{
		detectCornerX[0][0] = (x + 2 * velX) * MAPTILEX / WIDTH;//up leftx
		detectCornerX[0][1] = y * MAPTILEY / HEIGHT;//      y
		detectCornerX[1][0] = (width / SHRINK + x ) * MAPTILEX / WIDTH;//up right
		detectCornerX[1][1] = y * MAPTILEY / HEIGHT;
		detectCornerX[2][0] = (x + 2 * velX) * MAPTILEX / WIDTH;//bottom left
		detectCornerX[2][1] = (height / SHRINK + y) * MAPTILEY / HEIGHT;
		detectCornerX[3][0] = (width / SHRINK + x ) * MAPTILEX / WIDTH;//bottom right 
		detectCornerX[3][1] = (height / SHRINK + y) * MAPTILEY / HEIGHT;
	}

	if (velY <= 0)
	{
		detectCornerY[0][0] = (x ) * MAPTILEX / WIDTH;//up leftx
		detectCornerY[0][1] = (y + 2 * velY) * MAPTILEY / HEIGHT;//      y
		detectCornerY[1][0] = (width / SHRINK + x) * MAPTILEX / WIDTH;//up right
		detectCornerY[1][1] = (y + 2 * velY) * MAPTILEY / HEIGHT;
		detectCornerY[2][0] = (x ) * MAPTILEX / WIDTH;//bottom left
		detectCornerY[2][1] = (height / SHRINK + y) * MAPTILEY / HEIGHT;
		detectCornerY[3][0] = (width / SHRINK + x) * MAPTILEX / WIDTH;//bottom right 
		detectCornerY[3][1] = (height / SHRINK + y) * MAPTILEY / HEIGHT;
	}
	else if (velY > 0)
	{
		detectCornerY[0][0] = (x ) * MAPTILEX / WIDTH;//up leftx
		detectCornerY[0][1] = y * MAPTILEY / HEIGHT;//      y
		detectCornerY[1][0] = (width / SHRINK + x) * MAPTILEX / WIDTH;//up right
		detectCornerY[1][1] = y * MAPTILEY / HEIGHT;
		detectCornerY[2][0] = (x ) * MAPTILEX / WIDTH;//bottom left
		detectCornerY[2][1] = (height / SHRINK + (y + 2 * velY)) * MAPTILEY / HEIGHT;
		detectCornerY[3][0] = (width / SHRINK + x) * MAPTILEX / WIDTH;//bottom right 
		detectCornerY[3][1] = (height / SHRINK + (y + 2 * velY)) * MAPTILEY / HEIGHT;
	}
}

void AnimeObject::move() {

	if (jumpFlag)
	{
		velY = -10;
	}
	else if (yDown())
	{
		if(velY<=10)
			velY += 1;
	}
	else
	{
		velY = 0;
	}
	jumpFlag = 0; 
	setdetectCorner();
	moveOrNot();
	
	

	if (x +  width / SHRINK >= WIDTH)
		x = WIDTH - width / SHRINK;
	if (y + height / SHRINK >= HEIGHT)
		y = HEIGHT - height / SHRINK;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;

	printf("x: %d  y: %d\n", x, y);
	printf("xtile: %d  ytile: %d\n", x * MAPTILEX / WIDTH, y * MAPTILEY / HEIGHT);
	
}

bool AnimeObject::xRight()
{
	if (tile[0][detectCornerX[1][1]][detectCornerX[1][0]] == 0 && tile[0][detectCornerX[3][1]][detectCornerX[3][0]] == 0)
		return true;
	return false;
}
bool AnimeObject::xLeft()
{
	if (tile[0][detectCornerX[2][1]][detectCornerX[2][0]] == 0 && tile[0][detectCornerX[0][1]][detectCornerX[0][0]]==0)
		return true;
	return false;
}
bool AnimeObject::yUp()
{
	if (tile[0][detectCornerY[1][1]][detectCornerY[1][0]] == 0 && tile[0][detectCornerY[0][1]][detectCornerY[0][0]] == 0)
		return true;
	return false;
}
bool AnimeObject::yDown()
{
	if (tile[0][detectCornerY[2][1]][detectCornerY[2][0]] == 0 && tile[0][detectCornerY[3][1]][detectCornerY[3][0]] == 0)
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
}
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