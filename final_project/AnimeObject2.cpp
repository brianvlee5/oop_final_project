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
	cd_count = 30;
	dir = 1;
	Mapnum = 0;
	shownFlag = true;
	health = MAXHP;
	deadFlag = false;
	rushFlag = true;
	gravityFlag = true;
	num_potion = 7;
	gateFlag = false;
	coin = 50;
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
	SDL_Rect* d = &dst, * s = &src;

	if (shownFlag)
	{
		Object::draw(src, dst);

		thickLineRGBA(renderer, d->x, d->y-5, d->x + d->w, d->y-5, 2, 0x65, 0x43, 0x21, 0xFF);
		thickLineRGBA(renderer, d->x, d->y-5, d->x + d->w*cd_count / (RUSHCD / RUSHTIMER), d->y-5, 2, 0xFF, 0xFF, 0xFF, 0xFF);
	}
}

void AnimeObject2::setMapnum(int n)
{
	Mapnum = n;
	printf("%d\n", Mapnum);
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

void AnimeObject2::startRush(Uint32 t)
{
	if (rushFlag) {
		init_vx = getVx();
		rush = t;
		rush_count = 0;
		invinceFlag = true;
		gravityFlag = false;
		startRushCD(RUSHTIMER);
		RushID = SDL_AddTimer(rush, rushing, this);
	}
}

void AnimeObject2::stopRushTimer()
{
	rush = 0;
}

Uint32 AnimeObject2::rushing(Uint32 interval, void* param)
{
	AnimeObject2* p = (AnimeObject2*)param;
	if (p->getRush() < 3) //0 1 2
	{
		p->setVx(p->getVx()+5 * p->getDir() * VELOCITY);
		p->setRush(p->getRush() + 1);
		return interval;
	}
	else if (p->getRush() < 20)
	{
		if (p->getRush() <6)//3 4 5
		{
			p->setVx(p->getVx() - 5 * p->getDir() * VELOCITY);
			p->gravityFlag = true;
		}
		p->setRush(p->getRush() + 1);
		return interval;
	}
	else
	{
		p->setIVFlag(false);
		return 0;
	}
}

void AnimeObject2::startRushCD(Uint32 t)
{
	cd = t;
	cd_count = 0;
	rushFlag = false;
	cd_ID = SDL_AddTimer(cd, rushCD, this);
}

Uint32 AnimeObject2::rushCD(Uint32 interval, void* param)
{
	AnimeObject2* p = (AnimeObject2*)param;
/*
	static int lasttime = SDL_GetTicks64();
	static int curtime = SDL_GetTicks64();
	int timediv;
	static int timeacc=0;

	lasttime = curtime;
	curtime = SDL_GetTicks64();
	timediv = curtime - lasttime;
	timeacc += timediv;
	if (p->cd_count)
	{
		printf("time: %d\n", timeacc);
	}
*/		
	if (p->cd_count < RUSHCD/RUSHTIMER) 
	{
		p->cd_count++;
		return interval;
	}
	else
	{
		p->rushFlag = true;
		return 0;
	}
}

void AnimeObject2::move() 
{

	if (jumpFlag)
	{
		velY = -12;
	}
	else if (yDown()&& gravityFlag)
	{
		if (velY <= 12)
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

void AnimeObject2::setRush(int ru)
{
	rush_count = ru;
}
int AnimeObject2::getRush()
{
	return rush_count;
}

int AnimeObject2::getHP()
{
	return health;
}

void AnimeObject2::setKey(bool f)
{
	key = f;
}

bool AnimeObject2::getKey()
{
	return key;
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


void AnimeObject2::setDir(int d)
{
	dir = d;
}

int AnimeObject2::getDir()
{
	return dir;
}

int AnimeObject2::getRushCD()
{
	return cd_count;
}

void AnimeObject2::moveOrNot()
{

	if (velX > 0)
	{
		if (xRight() && !getGateFlag())
		{
			x += velX;
		}
	}
	else if (velX < 0)
	{
		if (xLeft() && !getGateFlag())
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

void AnimeObject2::setGateFlag(bool f)
{
	gateFlag = f;
}

bool AnimeObject2::getGateFlag()
{
	return gateFlag;
}

void AnimeObject2::usePotion()
{
	if (num_potion > 0)
	{
		num_potion--;
		if (health + 2 < MAXHP)
		{
			health += 2;
		}
		else
		{
			health = MAXHP;
		}
	}
}

void AnimeObject2::operator-(int minus)
{
	health -= minus;
}



void AnimeObject2::setPotionNum(int n)
{
	num_potion = n;
}

int AnimeObject2::getPotionNum()
{
	return num_potion;
}

void AnimeObject2::setCoin(int c)
{
	coin = c;
}

int AnimeObject2::getCoin()
{
	return coin;
}