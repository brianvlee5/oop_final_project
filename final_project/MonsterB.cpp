#include "MonsterB.h"


MonsterB::MonsterB(const char* path, int n, SDL_Renderer* ren) :Monster(path, n, ren)
{

}

MonsterB::MonsterB(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b) : Monster(path, n, ren, r, g, b)
{

}


void MonsterB::AIstate(AnimeObject2& mainch)
{
	AImode = WANDER;

	switch (AImode)
	{
	case TRACE:
	{
		if (getX() - mainch.getX() < 0)
		{
			setVX(2);
			if (tile[getMapnum()][getDPX(1, 1) - 1][getDPX(1, 0)] == 0 && (tile[getMapnum()][getDPX(1, 1)][getDPX(1, 0)] == 1 || tile[getMapnum()][getDPX(3, 1)][getDPX(3, 0)] == 1))
				setJumpFlag(1);
		}
		else if (getX() - mainch.getX() > 0)
		{
			setVX(-2);
			if (tile[getMapnum()][getDPX(2, 1) - 1][getDPX(2, 0)] == 0 && (tile[getMapnum()][getDPX(2, 1)][getDPX(2, 0)] == 1 || tile[getMapnum()][getDPX(0, 1)][getDPX(0, 0)] == 1))
				setJumpFlag(1);
		}
		else
			setVX(0);
		break;
	}
	case WANDER:
	{
		if (tile[getMapnum()][getDPY(2, 1)][getDPY(2, 0)] == 0 && tile[getMapnum()][getDPY(3, 1)][getDPY(3, 0)] == 1)
			WANDERmode = PLATFORMLB;
		else if (tile[getMapnum()][getDPY(2, 1)][getDPY(2, 0)] == 1 && tile[getMapnum()][getDPY(3, 1)][getDPY(3, 0)] == 0)
			WANDERmode = PLATFORMRB;
		else if (tile[getMapnum()][getDPX(1, 1)][getDPX(1, 0)] == 1 || tile[getMapnum()][getDPX(3, 1)][getDPX(3, 0)] == 1)
			WANDERmode = WALLR;
		else if (tile[getMapnum()][getDPX(2, 1)][getDPX(2, 0)] == 1 || tile[getMapnum()][getDPX(0, 1)][getDPX(0, 0)] == 1)
			WANDERmode = WALLL;
		else
			WANDERmode = FLOOR;

		switch (WANDERmode)
		{
		case WALLL:
			setVX(2);
			break;
		case WALLR:
			setVX(-2);
			break;
		case PLATFORMLB:
			setVX(2);
			break;
		case PLATFORMRB:
			setVX(-2);
			break;
		case FLOOR:
		{

		}
		}
		break;
	}


	}

	move();

}






void MonsterB::draw(SDL_Rect dst, SDL_Rect src)
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