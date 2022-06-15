#include "MonsterD.h"

MonsterD::MonsterD()
	:Monster()
{
	initialize();
}
MonsterD::MonsterD(const char* path, int n, SDL_Renderer* ren) :Monster(path, n, ren)
{
	initialize();
}

MonsterD::MonsterD(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b) : Monster(path, n, ren, r, g, b)
{
	initialize();
}

void MonsterD::initialize()
{
	setHP(30);
	AImode = WAIT;
	Flycd = 0;
	FlyTime = 0;
	AIinterval = 0;	
	XBase = YBase = XFly = YFly = WANDERmode = 0;
	Mchptr = nullptr;
}

void MonsterD::startAI(Uint32 t)
{
	AIinterval = t;
	AIID = SDL_AddTimer(AIinterval, AIState, this);
}
void MonsterD::stopAI()
{
	AIinterval = 0;
}

Uint32 MonsterD::AIState(Uint32 interval, void* param)
{
	MonsterD* p = (MonsterD*)param;
	
	switch (p->AImode)
	{
		case WAIT:
		{
			if (sqrt((p->XBase - p->Mchptr->getX()) * (p->XBase - p->Mchptr->getX()) + (p->YBase - p->Mchptr->getY()) * (p->YBase - p->Mchptr->getY())) <= 150 && p->Flycd==0)
			{
				p->FlyTime = 0;
				p->AImode = FLY;
				p->XFly = p->Mchptr->getX() - p->XBase;
				p->YFly = p->Mchptr->getY() - p->YBase;
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
			if (sqrt((p->XBase - p->getX()) * (p->XBase - p->getX()) + (p->YBase - p->getY()) * (p->YBase - p->getY())) <= 150)
			{
				p->setVX(p->XFly / 30);
				p->setVY(p->YFly / 30);
				p->move();
				p->FlyTime++;
				if (!p->xLeft() || !p->xRight() || !p->yUp() || !p->yDown())
					p->AImode = FLYBACK;
			}
			else
			{
				p->AImode = FLYBACK;
			}
			return interval;
			break;
		}
		case FLYBACK:
		{
			if (p->FlyTime > 0)
			{
				p->setVX(-p->XFly / 30);
				p->setVY(-p->YFly / 30);
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
		case STOP:
		{
			p->setVX(0);
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
	thickLineColor(getRenderer(), dst.x, dst.y, dst.x + dst.w, dst.y, 3, 0x987654FF);
	thickLineRGBA(getRenderer(), dst.x, dst.y, dst.x + dst.w * getHP() / getMaxHP(), dst.y, 3, 0x00, 0x80, 0x00, 0xff);
	Monster::draw(dst, src);
}

void MonsterD::setMchptr(AnimeObject2& mainch)
{
	Mchptr = &mainch;
}

void MonsterD::setBase(int xx, int yy)
{
	XBase = xx * WIDTH / MAPTILEX;
	YBase = yy * HEIGHT / MAPTILEY;
}
void MonsterD::setAImode(int mode)
{
	AImode = mode;
}
void MonsterD::operator<<(AnimeObject2& mainch)
{
	Mchptr = &mainch;
}
void MonsterD::setHPP()
{
	setHP(30);
}