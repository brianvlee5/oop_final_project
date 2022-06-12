#include "MAttack.h"

MAttack::MAttack(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b)
{
	frame = 0;
	renderer = ren;
	num = n;
	texture = new SDL_Texture * [num];
	setVX(2);
	health = 30;
	deadFlag = false;
	mapnum = 0;
	Maxhp = 30;
	shownFlag = true;
	atkFly = 50;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 2; j++)
			detectCornerX[i][j] = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 2; j++)
			detectCornerY[i][j] = 0;

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
			width = imgSurface->w / 5;
			height = imgSurface->h / 5;

			// Get rid of old loaded surface
			SDL_FreeSurface(imgSurface);
		}
	}

}

MAttack::MAttack(const char* path, int n, SDL_Renderer* ren)
{
	renderer = ren;
	num = n;
	texture = new SDL_Texture * [num];
	atkFly = 0;


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
			// Create texture from surface pixels	
			texture[i] = SDL_CreateTextureFromSurface(renderer, imgSurface);
			// Also, you can use IMG_LoadTexture() to replace IMG_Load and SDL_CreateTextureFromSurface
			// texture = IMG_LoadTexture(renderer, path);
			if (texture[i] == NULL)
			{
				printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
			}
			width = imgSurface->w / 5;
			height = imgSurface->h / 5;

			// Get rid of old loaded surface
			SDL_FreeSurface(imgSurface);
		}
	}

}

Uint32 MAttack::damaged(Uint32 interval, void* param)
{
	MAttack* p = (MAttack*)param;
	if (p->damageCD < 4)
	{
		p->setShownFlag(!p->getShownFlag());
		p->damageCD++;
		return interval;
	}
	else
	{
		p->cdFlag = false;
		return 0;
	}
}


Uint32 MAttack::changeData(Uint32 interval, void* param)
{
	MAttack* p = (MAttack*)param;
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

Uint32 MAttack::Straight(Uint32 interval, void* param)
{
	MAttack* p = (MAttack*)param;
	if (p->STTime != 0 && p->atkFly <= 30)
	{
		p->atkFly++;
		p->move();
		return interval;
	}
	else
	{
		p->setShownFlag(false);
		return 0;
	}
}

void MAttack::setMapnum(int mapnumm)
{
	mapnum = mapnumm;
}

int MAttack::getMapnum()
{
	return mapnum;
}

void MAttack::setDeadFlag(bool f)
{
	deadFlag = f;
}

bool MAttack::getDeadFlag()
{
	return deadFlag;
}

void MAttack::setShownFlag(bool f)
{
	shownFlag = f;
}

bool MAttack::getShownFlag()
{
	return shownFlag;
}

void MAttack::setcdFlag(bool f)
{
	cdFlag = f;
}

bool MAttack::getcdFlag()
{
	return cdFlag;
}

void MAttack::startCD(Uint32 t)
{
	hurtT = t;
	damageCD = 0;
	cdFlag = true;
	damageID = SDL_AddTimer(hurtT, damaged, this);
}

void MAttack::startTimer(Uint32 t)
{
	time = t;
	timerID = SDL_AddTimer(time, changeData, this);
}

void MAttack::stopTimer()
{
	time = 0;
}

void MAttack::startST(Uint32 t)
{
	STTime = t;
	STID = SDL_AddTimer(STTime, Straight, this);
}

void MAttack::close()
{
	for (int i = 0; i < num; i++) {
		SDL_DestroyTexture(texture[i]);
	}
}


void MAttack::draw(SDL_Rect dst, SDL_Rect src) {
	SDL_Rect* d = &dst, * s = &src;

	if (dst.x == ALLREGION)
	{
		d = NULL;
	}
	if (src.x == ALLREGION)
	{
		s = NULL;
	}

	if (shownFlag && !getDeadFlag())
	{
		if (SDL_RenderCopy(renderer, texture[frame], s, d) == -1)
		{
			printf("%s\n", SDL_GetError());
		}
	}
}
/*
void MAttack::draw()
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
void MAttack::setdetectCorner(SDL_Rect mc)
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

void MAttack::collisionAABB(AnimeObject2& mainch)
{
	if (!mainch.getIVFlag())
	{
		if (getX() < mainch.getX() + mainch.getWidth() / SHRINK &&
			mainch.getX() < x + width / SHRINK &&
			y < mainch.getY() + mainch.getHeight() / SHRINK &&
			mainch.getY() < y + height / SHRINK)
		{
			mainch.setHP(mainch.getHP() - 1);
			if (mainch.getHP() <= 0)
			{
				mainch.setDeadFlag(true);
			}
			//printf("HP remain: %d\n", mainch.getHP());
			mainch.startHurt(300);
		}
	}
}

void MAttack::setdetectCorner()
{
	if (velX >= 0)
	{
		detectCornerX[0][0] = x * MAPTILEX / WIDTH;//up leftx
		detectCornerX[0][1] = y * MAPTILEY / HEIGHT;//      y
		detectCornerX[1][0] = (width / SHRINK + x + 2 * velX) * MAPTILEX / WIDTH;//up right
		detectCornerX[1][1] = y * MAPTILEY / HEIGHT;
		detectCornerX[2][0] = x * MAPTILEX / WIDTH;//bottom left
		detectCornerX[2][1] = (height / SHRINK + y) * MAPTILEY / HEIGHT;
		detectCornerX[3][0] = (width / SHRINK + x + 2 * velX) * MAPTILEX / WIDTH;//bottom right 
		detectCornerX[3][1] = (height / SHRINK + y) * MAPTILEY / HEIGHT;
	}
	else if (velX < 0)
	{
		detectCornerX[0][0] = (x + 2 * velX) * MAPTILEX / WIDTH;//up leftx
		detectCornerX[0][1] = y * MAPTILEY / HEIGHT;//      y
		detectCornerX[1][0] = (width / SHRINK + x) * MAPTILEX / WIDTH;//up right
		detectCornerX[1][1] = y * MAPTILEY / HEIGHT;
		detectCornerX[2][0] = (x + 2 * velX) * MAPTILEX / WIDTH;//bottom left
		detectCornerX[2][1] = (height / SHRINK + y) * MAPTILEY / HEIGHT;
		detectCornerX[3][0] = (width / SHRINK + x) * MAPTILEX / WIDTH;//bottom right 
		detectCornerX[3][1] = (height / SHRINK + y) * MAPTILEY / HEIGHT;
	}

	if (velY <= 0)
	{
		detectCornerY[0][0] = (x)*MAPTILEX / WIDTH;//up leftx
		detectCornerY[0][1] = (y + 2 * velY) * MAPTILEY / HEIGHT;//      y
		detectCornerY[1][0] = (width / SHRINK + x) * MAPTILEX / WIDTH;//up right
		detectCornerY[1][1] = (y + 2 * velY) * MAPTILEY / HEIGHT;
		detectCornerY[2][0] = (x)*MAPTILEX / WIDTH;//bottom left
		detectCornerY[2][1] = (height / SHRINK + y) * MAPTILEY / HEIGHT;
		detectCornerY[3][0] = (width / SHRINK + x) * MAPTILEX / WIDTH;//bottom right 
		detectCornerY[3][1] = (height / SHRINK + y) * MAPTILEY / HEIGHT;
	}
	else if (velY > 0)
	{
		detectCornerY[0][0] = (x)*MAPTILEX / WIDTH;//up leftx
		detectCornerY[0][1] = y * MAPTILEY / HEIGHT;//      y
		detectCornerY[1][0] = (width / SHRINK + x) * MAPTILEX / WIDTH;//up right
		detectCornerY[1][1] = y * MAPTILEY / HEIGHT;
		detectCornerY[2][0] = (x)*MAPTILEX / WIDTH;//bottom left
		detectCornerY[2][1] = (height / SHRINK + (y + 2 * velY)) * MAPTILEY / HEIGHT;
		detectCornerY[3][0] = (width / SHRINK + x) * MAPTILEX / WIDTH;//bottom right 
		detectCornerY[3][1] = (height / SHRINK + (y + 2 * velY)) * MAPTILEY / HEIGHT;
	}
}

void MAttack::move() {

	setVY(0);
	setdetectCorner();

	moveOrNot();



	if (x + width / SHRINK >= WIDTH)
		x = WIDTH - width / SHRINK;
	if (y + height / SHRINK >= HEIGHT)
		y = HEIGHT - height / SHRINK;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
}

bool MAttack::xRight()
{
	if (tile[mapnum][detectCornerX[1][1]][detectCornerX[1][0]] == 0 && tile[mapnum][detectCornerX[3][1]][detectCornerX[3][0]] == 0)
		return true;
	return false;
}
bool MAttack::xLeft()
{
	if (tile[mapnum][detectCornerX[2][1]][detectCornerX[2][0]] == 0 && tile[mapnum][detectCornerX[0][1]][detectCornerX[0][0]] == 0)
		return true;
	return false;
}
bool MAttack::yUp()
{
	if (tile[mapnum][detectCornerY[1][1]][detectCornerY[1][0]] == 0 && tile[mapnum][detectCornerY[0][1]][detectCornerY[0][0]] == 0)
		return true;
	return false;
}
bool MAttack::yDown()
{
	if (tile[mapnum][detectCornerY[2][1]][detectCornerY[2][0]] == 0 && tile[mapnum][detectCornerY[3][1]][detectCornerY[3][0]] == 0)
		return true;
	return false;
}

void MAttack::moveOrNot()
{

	if (velX > 0)
	{
		if (xRight())
		{
			x += velX;
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
void MAttack::setPosition(int xx, int yy)
{
	x = xx;
	y = yy;
}
int MAttack::getWidth()
{
	return width;
}
int MAttack::getHeight()
{
	return height;
}
int MAttack::getX() const
{
	return x;
}
int MAttack::getY() const
{
	return y;
}
int MAttack::getHP()
{
	return health;
}
int MAttack::getVY() {
	return velY;
}
int MAttack::getMaxHP()
{
	return Maxhp;
}
void MAttack::setHP(int hp)
{
	health = hp;
}
void MAttack::setVY(int yy) {
	velY = yy;
}
int MAttack::getVX() {
	return velX;
}
void MAttack::setVX(int xx) {
	velX = xx;
}
void MAttack::setJumpFlag(bool f)
{
	jumpFlag = f;
}
int MAttack::getDPX(int a, int b)
{
	return detectCornerX[a][b];
}
int MAttack::getDPY(int a, int b)
{
	return detectCornerY[a][b];
}
bool MAttack::getJumpFlag()
{
	return jumpFlag;
}
SDL_Renderer* MAttack::getRenderer()
{
	return renderer;
}

void MAttack::setAF(int af)
{
	atkFly = af;
}

int MAttack::getAF()
{
	return atkFly;
}
