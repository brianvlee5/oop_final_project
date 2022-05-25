#include "MonsterA.h"

MonsterA::MonsterA(const char* path, int n, SDL_Renderer* ren):Monster(path, n, ren)
{
	
}

MonsterA::MonsterA(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b):Monster(path, n, ren, r, g, b)
{
	
}

void MonsterA::AIstart(AnimeObject2& mainch)
{
	if (fabs(getX() - mainch.getX()) < 100 || fabs(getY() - mainch.getY()) < 100)
		AImode = TRACE;
	else
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
