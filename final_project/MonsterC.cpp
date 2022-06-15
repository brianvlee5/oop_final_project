#include "MonsterC.h"

MonsterC::MonsterC()
	:Monster()
{
	initialize();
}

MonsterC::MonsterC(const char* path, int n, SDL_Renderer* ren) :Monster(path, n, ren)
{
	initialize();
}

MonsterC::MonsterC(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b) : Monster(path, n, ren, r, g, b)
{
	initialize();
}


void MonsterC::startAI(Uint32 t)
{
	AIinterval = t;
	AIID = SDL_AddTimer(AIinterval, AIState, this);
}
void MonsterC::stopAI()
{
	AIinterval = 0;
}

Uint32 MonsterC::AIState(Uint32 interval, void* param)
{
	MonsterC* p = (MonsterC*)param;

	switch (p->AImode)
	{
		case TELEPORT:
		{
			int dist;
			dist = rand() % 200;
			if (p->getX() - p->Mchptr->getX() < 0)
			{
				p->setVX(dist);
			}
			else if (p->getX() - p->Mchptr->getX() > 0)
			{
				p->setVX(-dist);
			}
			p->move();
			p->WaitTime = rand() % 50 + 50;
			p->AImode = WAIT;
			return interval;
			break;
		}
		case WAIT:
		{
			if (fabs(p->getX() - p->Mchptr->getX()) < 400 && fabs(p->getY() - p->Mchptr->getY()) < 75 && p->WaitTime<=0)
			{
				p->AImode = TELEPORT;
			}
			else if (p->WaitTime > 0)
			{
				p->WaitTime--;
			}
			else
			{
				p->AImode = WANDER;
				p->WanderTime = rand() % 50 + 50;

				if (tile[p->getMapnum()][p->getDPY(2, 1)][p->getDPY(2, 0)] == 0 && tile[p->getMapnum()][p->getDPY(3, 1)][p->getDPY(3, 0)] == 1)
					p->WANDERmode = RIGHT;
				else if (tile[p->getMapnum()][p->getDPY(2, 1)][p->getDPY(2, 0)] == 1 && tile[p->getMapnum()][p->getDPY(3, 1)][p->getDPY(3, 0)] == 0)
					p->WANDERmode = LEFT;
				else if (tile[p->getMapnum()][p->getDPX(1, 1)][p->getDPX(1, 0)] == 1 || tile[p->getMapnum()][p->getDPX(3, 1)][p->getDPX(3, 0)] == 1)
					p->WANDERmode = LEFT;
				else if (tile[p->getMapnum()][p->getDPX(2, 1)][p->getDPX(2, 0)] == 1 || tile[p->getMapnum()][p->getDPX(0, 1)][p->getDPX(0, 0)] == 1)
					p->WANDERmode = RIGHT;
				else
					p->WANDERmode = rand() % 2;
			}
			return interval;
			break;
		}
		case WANDER:
		{

			if (tile[p->getMapnum()][p->getDPY(2, 1)][p->getDPY(2, 0)] == 0 && tile[p->getMapnum()][p->getDPY(3, 1)][p->getDPY(3, 0)] == 1)
				p->WANDERmode = LEFT;
			else if (tile[p->getMapnum()][p->getDPY(2, 1)][p->getDPY(2, 0)] == 1 && tile[p->getMapnum()][p->getDPY(3, 1)][p->getDPY(3, 0)] == 0)
				p->WANDERmode = RIGHT;
			else if (tile[p->getMapnum()][p->getDPX(1, 1)][p->getDPX(1, 0)] == 1 || tile[p->getMapnum()][p->getDPX(3, 1)][p->getDPX(3, 0)] == 1)
				p->WANDERmode = RIGHT;
			else if (tile[p->getMapnum()][p->getDPX(2, 1)][p->getDPX(2, 0)] == 1 || tile[p->getMapnum()][p->getDPX(0, 1)][p->getDPX(0, 0)] == 1)
				p->WANDERmode = LEFT;

			if (p->WanderTime > 0)
			{

				if (p->WANDERmode == LEFT)
					p->setVX(2);
				else
					p->setVX(-2);

				p->move();
				p->WanderTime--;
			}
			else
			{
				p->WaitTime = rand() % 50 + 50;
				p->AImode = WAIT;
			}

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




void MonsterC::draw(SDL_Rect dst, SDL_Rect src)
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
	//thickLineColor(getRenderer(), d->x, d->y, d->x + d->w, d->y, 3, 0x987654FF);
	//thickLineRGBA(getRenderer(), d->x, d->y, d->x + d->w * getHP() / getMaxHP(), d->y, 3, 0x00, 0x80, 0x00, 0xff);

	Monster::draw(dst, src);
}

void MonsterC::setMchptr(AnimeObject2& mainch)
{
	Mchptr = &mainch;
}
void MonsterC::setAImode(int mode)
{
	AImode = mode;
}
void MonsterC::initialize()
{
	setHP(10);
	TPcd = 0;
	AIinterval = 0;
	Mchptr = nullptr;
	AImode = WANDER;
	WANDERmode = LEFT;
	WaitTime = 0;
	WanderTime = 0;
}

void MonsterC::operator<<(AnimeObject2& mainch)
{
	Mchptr = &mainch;
}
void MonsterC::setHPP()
{
	setHP(10);
}