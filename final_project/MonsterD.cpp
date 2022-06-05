#include "MonsterD.h"

MonsterD::MonsterD(const char* path, int n, SDL_Renderer* ren) :Monster(path, n, ren)
{
	AImode = WAIT;
	Flycd = 0;
	FlyTime = 0;
}

MonsterD::MonsterD(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b) : Monster(path, n, ren, r, g, b)
{
	AImode = WAIT;
	Flycd = 0;
	FlyTime = 0;
}

void MonsterD::startAI(Uint32 t)
{
	AIinterval = t;
	AIID = SDL_AddTimer(AIinterval, AIState, this);
}

Uint32 MonsterD::AIState(Uint32 interval, void* param)
{
	MonsterD* p = (MonsterD*)param;
	
	switch (p->AImode)
	{
		case WAIT:
		{
			if (sqrt((MDStartP.x - p->Mchptr->getX()) * (MDStartP.x - p->Mchptr->getX()) + (MDStartP.y - p->Mchptr->getY()) * (MDStartP.y - p->Mchptr->getY())) <= 250 && p->Flycd==0)
			{
				printf("to fly\n");
				p->FlyTime = 0;
				p->AImode = FLY;
				p->XFly = p->Mchptr->getX() - MDStartP.x;
				p->YFly = p->Mchptr->getY() - MDStartP.y;
				printf("x:%d y:%d\n", p->XFly, p->YFly);
			}
			else if(p->Flycd>0)
			{
				p->Flycd--;
				
			}

			return interval;
			break;
		}
		case FLY:
		{
			if (sqrt((MDStartP.x - p->getX()) * (MDStartP.x - p->getX()) + (MDStartP.y - p->getY()) * (MDStartP.y - p->getY())) <= 250)
			{
				p->setVX(p->XFly / 20);
				p->setVY(p->YFly / 20);
				p->move();
				p->FlyTime++;
			}
			else
			{
				printf("to flyback\n");
				p->AImode = FLYBACK;
			}
			return interval;
			break;
		}
		case FLYBACK:
		{
			if (p->FlyTime > 0)
			{
				p->setVX(-p->XFly / 20);
				p->setVY(-p->YFly / 20);
				p->FlyTime--;
			}
			else
			{
				p->setVX(0);
				p->setVY(0);
				p->AImode = WAIT;
				p->Flycd = 10;
			}
			
			p->move();


			return interval;
			break;
		}
	}
}

void MonsterD::move() 
{

	
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


void MonsterD::draw(SDL_Rect dst, SDL_Rect src)
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
	thickLineColor(getRenderer(), d->x, d->y, d->x + d->w, d->y, 3, 0x987654FF);
	thickLineRGBA(getRenderer(), d->x, d->y, d->x + d->w * getHP() / getMaxHP(), d->y, 3, 0x00, 0x80, 0x00, 0xff);
	Monster::draw(dst, src);
}

void MonsterD::setMchptr(AnimeObject2& mainch)
{
	Mchptr = &mainch;
}