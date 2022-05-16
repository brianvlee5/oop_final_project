#include "main.h"

using namespace std;

SDL_Texture* texture = NULL;

void spacial_hash(const vector<Monster>& Mv, vector<vector<Monster>>& MvM)
{
	for (int i = 0; i < Mv.size(); i++)
	{
		//0 -> 1st quadrant, and so on
		if (Mv[i].getX() < WIDTH / 2 && Mv[i].getY() < HEIGHT / 2)
			MvM[0].push_back(Mv[i]);
		else if (Mv[i].getX() >= WIDTH / 2 && Mv[i].getY() < HEIGHT / 2)
			MvM[1].push_back(Mv[i]);
		else if (Mv[i].getX() < WIDTH / 2 && Mv[i].getY() >= HEIGHT / 2)
			MvM[2].push_back(Mv[i]);
		else
			MvM[3].push_back(Mv[i]);
	}
}

int main(int argc, char* args[])
{
	System sdl;
	if (!sdl.init())
	{
		printf("Failed to initialize SDL system!\n");
		return -1;
	}
	RenderWindow window("Elden's rOng", 300, 170, WINDOWW, WINDOWH);
	const int num=6;
	Coordinate coord, coo[num], enemycord[3], enemyhp[3];
	vector<Monster> monsv;
	SDL_RendererFlip no = SDL_FLIP_NONE;
	Text fail("Game Over", "../fonts/akabara-cinderella.ttf", 60,  TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW/2-150, WINDOWH/2 }, { NULL, NULL }, NULL, no, 100);
	
	AnimeObject panda("../images/panda/", 4, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	AnimeObject2 pan("../images/panda.png", 4, 1, 4, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	AnimeObject2 p("../images/panda.png", window.getRenderer());
	Attack fire[num] = { Attack("../images/fire1.png", 1, 1, 1, window.getRenderer(), 0x00, 0x00, 0x00),
					   Attack("../images/fire1.png", 1, 1, 1, window.getRenderer(), 0x00, 0x00, 0x00),
					   Attack("../images/fire2.png", 1, 1, 1, window.getRenderer(), 0x00, 0x00, 0x00),
					   Attack("../images/fire2.png", 1, 1, 1, window.getRenderer(), 0x00, 0x00, 0x00),
					   Attack("../images/fire1.png", 1, 1, 1, window.getRenderer(), 0x00, 0x00, 0x00),
					   Attack("../images/fire1.png", 1, 1, 1, window.getRenderer(), 0x00, 0x00, 0x00)
	};
	vector<Object> heart;
	Object h("../images/heart.png", 1, 1, 1, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	h.setPosition(0, 0);
	for (int i = 0; i < pan.getHP(); i++) {
		//		heart.push_back(h);
		window.addVPregion({ {h.getWidth() / 2 * i, 0, h.getWidth() / 2, h.getHeight()} });
	}

	


	Map demo1;
	demo1.set("../images/map/mapdemo", window.getRenderer());
	pan.setPosition(demo1.startL[demo1.getmapnum()].x, demo1.startL[demo1.getmapnum() ].y);
	SDL_Event e;

	for (int i = 0; i < 3; i++)
	{
		Monster enemy("../images/pooh/", 22, window.getRenderer(), 0xFF, 0xFF, 0xFF);
		enemy.setPosition(MonstP[demo1.getmapnum()][i].x, MonstP[demo1.getmapnum()][i].y);
		monsv.push_back(enemy);
	}

	bool quit = false;
	while (!quit)
	{
		
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
			poohKeyboard(e, pan);
			attackKeyboard(e, fire, pan);
		}
		
		pan.move();
		
		for (int i = 0; i < 3; i++)
		{
			if (!monsv[i].getDeadFlag())
				monsv[i].AIstart(pan);
		}
		demo1.setcamera(pan);
		demo1.changemap(pan, monsv);


		window.clear();
		window.setVP(-1);
		coord.calMapCamera(demo1, pan);
		for (int i = 0; i < 6; i++)
			coo[i].calMap(demo1, fire[i]);
		
				

		demo1.draw({ ALLREGION }, demo1.getcamera());
		pan.draw({ coord.getpCX(),coord.getpCY(),pan.getWidth() / SHRINK ,pan.getHeight() / SHRINK });
		
		for (int i = 0; i < 3; i++)
		{
			if (!monsv[i].getDeadFlag())
			{
				enemycord[i].calMapCamera(demo1, monsv[i]);
				monsv[i].draw({ enemycord[i].getpCX(),enemycord[i].getpCY(),monsv[i].getWidth() / SHRINK,monsv[i].getHeight() / SHRINK }, { NULL });
			}
		}

		for (int i = 0; i < 3; i++)
		{
			if(!monsv[i].getDeadFlag())
				monsv[i].collisionAABB(pan);
		}

		


		for (int i = 0; i < 6; i++)
		{
			fire[i].collision_mons(monsv);
			//printf("x: %d y: %d\n", fire[i].getX(), fire[i].getY());
		}

		for (int i = 0; i < num; i++)
			fire[i].draw({ coo[i].getpCX(),coo[i].getpCY(),fire[i].getWidth(),fire[i].getHeight() });

		
		for (int i = 0; i < MAXHP; i++) {
			window.setVP(i);
			h.draw({h.getWidth()/2, 0, h.getWidth()/2, h.getWidth()}, {ALLREGION});
		}
		for (int i = 0; i < pan.getHP(); i++) {
			window.setVP(i);		
			h.draw();
		}
		window.setVP(-1);
		if (pan.getDeadFlag())
		{
			fail.draw();
			window.display();
			system("pause");
			
			break;
		}
		window.display();
	}
	SDL_DestroyTexture(texture);
	pan.close();
	demo1.close();

	for (int i = 0; i < 3; i++)
		monsv[i].close();

	for(int i=0; i<num; i++)
		fire[i].close();
	window.close();
	sdl.close();
	

	return 0;
}



