#include "MAttack.h"

MAttack::MAttack(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b):
	Monster(path, n, ren, r, g, b)
{
	atkFly = 50;
}

MAttack::MAttack(const char* path, int n, SDL_Renderer* ren):
	Monster(path, n ,ren)
{	
	atkFly = 50;
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

void MAttack::startST(Uint32 t)
{
	STTime = t;
	STID = SDL_AddTimer(STTime, Straight, this);
}


void MAttack::draw(SDL_Rect dst, SDL_Rect src) 
{
	SDL_Rect* d = &dst, * s = &src;

	if (dst.x == ALLREGION)
	{
		d = NULL;
	}
	if (src.x == ALLREGION)
	{
		s = NULL;
	}
	Monster::draw(dst, src);
}

void MAttack::move() {

	setVY(0);
	setdetectCorner();

	moveOrNot();



	if (getX() + getWidth() / SHRINK >= WIDTH)
		setPosition(WIDTH - getWidth() / SHRINK, getY());
	if (getY() + getHeight() / SHRINK >= HEIGHT)
		setPosition(getX(), HEIGHT - getHeight() / SHRINK);
	if (getX() < 0)
		setPosition(0, getY());
	if (getY() < 0)
		setPosition(getX(), 0);
}

void MAttack::setMchptr(AnimeObject2& mainch)
{

}

void MAttack::setAF(int af)
{
	atkFly = af;
}

int MAttack::getAF()
{
	return atkFly;
}

void MAttack::startAI(Uint32 t)
{

}

void MAttack::stopAI()
{

}