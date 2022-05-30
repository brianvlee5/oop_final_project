#include "GSManager.h"

//global functions
static void pauseEvents(SDL_Event e, int& state, GSManager* gsm)
{
	int x, y;
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			state = PAUSE;
		}

	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{

		}
	}

	if (e.type == SDL_MOUSEBUTTONUP)
	{
		SDL_GetMouseState(&x, &y);
		if (e.button.button == SDL_BUTTON_LEFT && x >= (WINDOWW / 2 - 150) && x <= (WINDOWW / 2 + 100) && y >= (WINDOWH / 2) && y <= (WINDOWH / 2 + 50))
		{
			state = PLAY;
		}
		if (e.button.button == SDL_BUTTON_LEFT && x >= (WINDOWW / 2 - 150) && x <= (WINDOWW / 2 + 100) && y >= (WINDOWH / 2 + 45) && y <= (WINDOWH / 2 + 95))
		{
			gsm->setGameState(MAINMENU);
		}
	}
}

static void MenuEvents(SDL_Event e, GSManager* gsm)
{
	int x, y;

	if (e.type == SDL_MOUSEBUTTONUP)
	{
		SDL_GetMouseState(&x, &y);
		if (e.button.button == SDL_BUTTON_LEFT && x >= (WINDOWW / 2 - 150) && x <= (WINDOWW / 2 + 100) && y >= (WINDOWH / 2) && y <= (WINDOWH / 2 + 50))
		{
			gsm->setGameState(GAMEPLAY);
		}
		else if (e.button.button == SDL_BUTTON_LEFT && x >= (WINDOWW / 2 - 150) && x <= (WINDOWW / 2 + 100) && y >= (WINDOWH / 2 + 45) && y <= (WINDOWH / 2 + 95))
		{
			
		}
	}
}


GSManager::GSManager()
{
	quit = false;
	GameState = GAMEPLAY;
}

void GSManager::startGame(RenderWindow& window)
{
	while (!quit)
	{
		switch (GameState)
		{
			case MAINMENU:
			{
				MainMenu(window);
				break;
			}
			case GAMEPLAY:
			{
				GamePlay(window);
				break;
			}

		}
	}
}

void GSManager::MainMenu(RenderWindow& window)
{
	Object mainmenu("../images/mapdemo1.png", window.getRenderer());
	Text startNewGame("New Game", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 150, WINDOWH / 2 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	while (!quit && GameState == MAINMENU)
	{
		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				quit = true;
			MenuEvents(ev, this);
		}
		window.clear();
		mainmenu.draw({ALLREGION}, {ALLREGION});
		startNewGame.draw();


		window.display();
	}
	startNewGame.close();
	mainmenu.close();
}

void GSManager::GamePlay(RenderWindow& window)
{
	int state=0;
	Coordinate coord, coo[6], enemycord[3], enemyhp[3];
	vector<MonsterA> monsv;

	Text fail("Game Over", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 150, WINDOWH / 2 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text resume("resume", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 100, WINDOWH / 2-30 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text menu("menu", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2+15 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);

	AnimeObject2 pan("../images/panda/", 4, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	
	vector<Attack> fire; // (6, Attack("../images/attack/fire2.png", 1, 1, 1, window.getRenderer(), 0xFF, 0xFF, 0xFF));
	Object h("../images/heart.png", window.getRenderer(), 0xFF, 0xFF, 0xFF);
	h.setPosition(0, 0);
	
	for (int i = 0; i < pan.getHP(); i++) {
		window.addVPregion({ {h.getWidth() / 2 * i, 0, h.getWidth() / 2, h.getHeight()} });
	}



	Map demo1;
	demo1.set("../images/map/map", window.getRenderer());
	window.addVPregion({ {WINDOWW / 6 * 5, 0, WINDOWW / 4, WINDOWH / 4} }); // VP: 6
	pan.setPosition(demo1.startL[demo1.getmapnum()].x, demo1.startL[demo1.getmapnum()].y);


	for (int i = 0; i < 3; i++)
	{
		MonsterA enemy("../images/pooh/", 22, window.getRenderer(), 0xFF, 0xFF, 0xFF);
		enemy.setPosition(MonstP[demo1.getmapnum()][i].x, MonstP[demo1.getmapnum()][i].y);
		monsv.push_back(enemy);
	}
	for (int i = 0; i < 6; i++)
	{
		fire.push_back(Attack("../images/fire2.png",window.getRenderer(), 0xFF, 0xFF, 0xFF));
	}
	while (!quit && GameState==GAMEPLAY)
	{

		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				quit = true;
			poohKeyboard(ev, pan);
			attackKeyboard(ev, fire, pan);
			pauseEvents(ev, state, this);
		}

		switch (state)
		{
			case PLAY:
			{
				window.clear();
				window.setVP(-1);
				pan.move();

				for (int i = 0; i < 3; i++)
				{
					if (!monsv[i].getDeadFlag())
						monsv[i].AIstart(pan);
					//monsv[i].StartWait(30);
				}
				demo1.setcamera(pan);
				demo1.changemap(pan, monsv);


				coord.calMapCamera(demo1, pan);
				for (int i = 0; i < 6; i++)
					coo[i].calMapCamera(demo1, fire[i]);



				demo1.draw({ ALLREGION }, demo1.getcamera());
				pan.draw({ ALLREGION }, { coord.getpCX(), coord.getpCY(), pan.getWidth() / SHRINK, pan.getHeight() / SHRINK });

				for (int i = 0; i < 3; i++)
				{
					if (!monsv[i].getDeadFlag())
					{
						enemycord[i].calMapCamera(demo1, monsv[i]);
						monsv[i].draw({ enemycord[i].getpCX(),enemycord[i].getpCY(),monsv[i].getWidth() / SHRINK,monsv[i].getHeight() / SHRINK }, { ALLREGION });
					}
				}

				for (int i = 0; i < 3; i++)
				{
					if (!monsv[i].getDeadFlag())
						monsv[i].collisionAABB(pan);
				}




				for (int i = 0; i < 6; i++)
				{
					fire[i].collision_mons(monsv);
					//printf("x: %d y: %d\n", fire[i].getX(), fire[i].getY());
				}

				for (int i = 0; i < 6; i++)
					fire[i].draw({ ALLREGION }, { coo[i].getpCX(), coo[i].getpCY(), fire[i].getWidth(), fire[i].getHeight() });


				for (int i = 0; i < MAXHP; i++) {
					window.setVP(i);
					h.draw({ h.getWidth() / 2, 0, h.getWidth() , h.getHeight() }, { 0, 0,h.getWidth() / 2, h.getHeight() });
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
				window.setVP(8);
				demo1.draw({ 0, 0, WINDOWW / 6 , WINDOWW / 6 }, { ALLREGION });
				filledCircleColor(window.getRenderer(), (pan.getX() + pan.getWidth() / 2) / 12, (pan.getY() + pan.getHeight() / 2) / 8, 2, 0xFF0000FF);
				window.display();
				break;
			}
			case PAUSE:
			{
				demo1.draw({ ALLREGION }, demo1.getcamera());
				pan.draw({ ALLREGION }, { coord.getpCX(), coord.getpCY(), pan.getWidth() / SHRINK, pan.getHeight() / SHRINK });
				for (int i = 0; i < 3; i++)
				{
					if (!monsv[i].getDeadFlag())
					{
						enemycord[i].calMapCamera(demo1, monsv[i]);
						monsv[i].draw({ enemycord[i].getpCX(),enemycord[i].getpCY(),monsv[i].getWidth() / SHRINK,monsv[i].getHeight() / SHRINK }, { ALLREGION });
					}
				}
				for (int i = 0; i < 6; i++)
					fire[i].draw({ ALLREGION }, { coo[i].getpCX(), coo[i].getpCY(), fire[i].getWidth(), fire[i].getHeight() });
				for (int i = 0; i < MAXHP; i++) {
					window.setVP(i);
					h.draw({ h.getWidth() / 2, 0, h.getWidth() , h.getHeight() }, { 0, 0,h.getWidth() / 2, h.getHeight() });
				}
				for (int i = 0; i < pan.getHP(); i++) {
					window.setVP(i);
					h.draw();
				}
				window.setVP(8);
				demo1.draw({ 0, 0, WINDOWW / 6 , WINDOWW / 6 }, { ALLREGION });
				filledCircleColor(window.getRenderer(), (pan.getX() + pan.getWidth() / 2) / 12, (pan.getY() + pan.getHeight() / 2) / 8, 2, 0xFF0000FF);
				
				window.setVP(-1);
				resume.draw();
				menu.draw();
				window.display();
				
				break;
			}
		}
	}
	pan.close();
	demo1.close();
	fail.close();
	resume.close();
	menu.close();

	for (int i = 0; i < 3; i++)
		monsv[i].close();

	for (int i = 0; i < 6; i++)
		fire[i].close();
}

void GSManager::setGameState(int gs)
{
	GameState = gs;
}

int GSManager::getGameState()
{
	return GameState;
}

