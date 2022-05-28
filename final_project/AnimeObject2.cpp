#include "AnimeObject2.h"

AnimeObject2::AnimeObject2()
	: Object()
{
	initialize();
}
AnimeObject2::AnimeObject2(const char* path, SDL_Renderer* ren)
	: Object(path, ren)
{
	initialize();
}
AnimeObject2::AnimeObject2(const char* path, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b)
	: Object(path, ren, r, g, b)
{
	initialize();
}
AnimeObject2::AnimeObject2(const char* path, int n, SDL_Renderer* ren)
	: Object(path, n, ren)
{
	initialize();
}
AnimeObject2::AnimeObject2(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b)
	: Object(path, n, ren, r, g, b)
{
	initialize();
}

void AnimeObject2::initialize()
{
	Mapnum = 0;
	shownFlag = true;
	health = MAXHP;
	deadFlag = false;
}

void AnimeObject2::draw()
{
	if (shownFlag)
		Object::draw();
}
/*
void AnimeObject2::draw(SDL_Rect src)
{

	if (shownFlag)
	{
		image[frame].setSrcRegion(src);
		image[frame].draw();
	}
}

void AnimeObject2::draw(SDL_Rect dst)
{

	if (shownFlag)
	{
		image[frame].setDstRegion(dst);
		image[frame].draw();
	}
}
*/
void AnimeObject2::draw(SDL_Rect src, SDL_Rect dst)
{
	if (shownFlag)
	{
		Object::draw(src, dst);
	}
}

void AnimeObject2::setMapnum(int n)
{
	Mapnum = n;
	printf("%d\n", Mapnum);
}

void AnimeObject2::setShownFlag(bool f)
{
	shownFlag = f;
}

bool AnimeObject2::getShownFlag()
{
	return shownFlag;
}

void AnimeObject2::startFrameTimer(Uint32 t)
{
	time = t;
	timerID = SDL_AddTimer(time, changeFrame, this);
}

void AnimeObject2::stopFrameTimer()
{
	time = 0;
}

Uint32 AnimeObject2::changeFrame(Uint32 interval, void* param)
{
	AnimeObject2* p = (AnimeObject2*)param;
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

void AnimeObject2::startHurt(Uint32 t)
{
	hurtt = t;
	invincet = 0;
	shownFlag = true;
	invinceFlag = true;
	HurtID = SDL_AddTimer(hurtt, invincible, this);
}

void AnimeObject2::stopHurtTimer()
{
	hurtt = 0;
}

Uint32 AnimeObject2::invincible(Uint32 interval, void* param)
{
	AnimeObject2* p = (AnimeObject2*)param;
	if (p->getIVT() < 6)
	{
		p->setShownFlag(!p->getShownFlag());
		p->setIVT(p->getIVT() + 1);
		return interval;
	}
	else
	{
		p->setIVFlag(false);
		return 0;
	}
}

void AnimeObject2::move() 
{

	if (jumpFlag)
	{
		velY = -10;
	}
	else if (yDown())
	{
		if (velY <= 10)
			velY += 1;
	}
	else
	{
		velY = 0;
	}
	jumpFlag = 0;
	setdetectCorner();
	moveOrNot();

	if (x + getWidth() / SHRINK >= WIDTH)
		x = WIDTH - getWidth() / SHRINK;
	if (y + getHeight() / SHRINK >= HEIGHT)
		y = HEIGHT - getHeight() / SHRINK;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;

}

void AnimeObject2::setdetectCorner()
{
	if (velX >= 0)
	{
		detectCornerX[0][0] = x * MAPTILEX / WIDTH;//up leftx
		detectCornerX[0][1] = y * MAPTILEY / HEIGHT;//      y
		detectCornerX[1][0] = (getWidth() / SHRINK + x + 2 * velX) * MAPTILEX / WIDTH;//up right
		detectCornerX[1][1] = y * MAPTILEY / HEIGHT;
		detectCornerX[2][0] = x * MAPTILEX / WIDTH;//bottom left
		detectCornerX[2][1] = (getHeight() / SHRINK + y) * MAPTILEY / HEIGHT;
		detectCornerX[3][0] = (getWidth() / SHRINK + x + 2 * velX) * MAPTILEX / WIDTH;//bottom right 
		detectCornerX[3][1] = (getHeight() / SHRINK + y) * MAPTILEY / HEIGHT;
	}
	else if (velX < 0)
	{
		detectCornerX[0][0] = (x + 2 * velX) * MAPTILEX / WIDTH;//up leftx
		detectCornerX[0][1] = y * MAPTILEY / HEIGHT;//      y
		detectCornerX[1][0] = (getWidth() / SHRINK + x) * MAPTILEX / WIDTH;//up right
		detectCornerX[1][1] = y * MAPTILEY / HEIGHT;
		detectCornerX[2][0] = (x + 2 * velX) * MAPTILEX / WIDTH;//bottom left
		detectCornerX[2][1] = (getHeight() / SHRINK + y) * MAPTILEY / HEIGHT;
		detectCornerX[3][0] = (getWidth() / SHRINK + x) * MAPTILEX / WIDTH;//bottom right 
		detectCornerX[3][1] = (getHeight() / SHRINK + y) * MAPTILEY / HEIGHT;
	}

	if (velY <= 0)
	{
		detectCornerY[0][0] = (x)*MAPTILEX / WIDTH;//up leftx
		detectCornerY[0][1] = (y + 2 * velY) * MAPTILEY / HEIGHT;//      y
		detectCornerY[1][0] = (getWidth() / SHRINK + x) * MAPTILEX / WIDTH;//up right
		detectCornerY[1][1] = (y + 2 * velY) * MAPTILEY / HEIGHT;
		detectCornerY[2][0] = (x)*MAPTILEX / WIDTH;//bottom left
		detectCornerY[2][1] = (getHeight() / SHRINK + y) * MAPTILEY / HEIGHT;
		detectCornerY[3][0] = (getWidth() / SHRINK + x) * MAPTILEX / WIDTH;//bottom right 
		detectCornerY[3][1] = (getHeight() / SHRINK + y) * MAPTILEY / HEIGHT;
	}
	else if (velY > 0)
	{
		detectCornerY[0][0] = (x)*MAPTILEX / WIDTH;//up leftx
		detectCornerY[0][1] = y * MAPTILEY / HEIGHT;//      y
		detectCornerY[1][0] = (getWidth() / SHRINK + x) * MAPTILEX / WIDTH;//up right
		detectCornerY[1][1] = y * MAPTILEY / HEIGHT;
		detectCornerY[2][0] = (x)*MAPTILEX / WIDTH;//bottom left
		detectCornerY[2][1] = (getHeight() / SHRINK + (y + 2 * velY)) * MAPTILEY / HEIGHT;
		detectCornerY[3][0] = (getWidth() / SHRINK + x) * MAPTILEX / WIDTH;//bottom right 
		detectCornerY[3][1] = (getHeight() / SHRINK + (y + 2 * velY)) * MAPTILEY / HEIGHT;
	}
}

void AnimeObject2::setMapFlag(bool f)
{
	mapFlag = f;
}

void AnimeObject2::setIVT(int ivt)
{
	invincet = ivt;
}

void AnimeObject2::setDeadFlag(bool f)
{
	deadFlag = f;
}

bool AnimeObject2::getDeadFlag()
{
	return deadFlag;
}

void AnimeObject2::setIVFlag(bool f)
{
	invinceFlag = f;
}

bool AnimeObject2::getIVFlag()
{
	return invinceFlag;
}

void AnimeObject2::setHP(int hp)
{
	health = hp;
}

int AnimeObject2::getHP()
{
	return health;
}

bool AnimeObject2::xRight()
{
	if (tile[Mapnum][detectCornerX[1][1]][detectCornerX[1][0]] == 1 || tile[Mapnum][detectCornerX[3][1]][detectCornerX[3][0]] == 1)
		return false;
	return true;
}
bool AnimeObject2::xLeft()
{
	if (tile[Mapnum][detectCornerX[2][1]][detectCornerX[2][0]] == 1 || tile[Mapnum][detectCornerX[0][1]][detectCornerX[0][0]] == 1)
		return false;
	return true;
}
bool AnimeObject2::yUp()
{
	if (tile[Mapnum][detectCornerY[1][1]][detectCornerY[1][0]] == 1 || tile[Mapnum][detectCornerY[0][1]][detectCornerY[0][0]] == 1)
		return false;
	return true;
}
bool AnimeObject2::yDown()
{
	if (tile[Mapnum][detectCornerY[2][1]][detectCornerY[2][0]] == 1 || tile[Mapnum][detectCornerY[3][1]][detectCornerY[3][0]] == 1)
		return false;
	return true;
}

bool AnimeObject2::getMapFlag()
{
	return mapFlag;
}
int AnimeObject2::getMapnum()
{
	return Mapnum;
}

int AnimeObject2::getIVT()
{
	return invincet;
}

void AnimeObject2::moveOrNot()
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

void AnimeObject2::setJumpFlag(bool f)
{
	jumpFlag = f;
}