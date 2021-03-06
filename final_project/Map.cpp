#include "Map.h"


Map::Map()
{
	initialize();
}

Map::Map(const char* path, SDL_Renderer* ren)
{
	initialize();

	renderer = ren;
	// Load a surface from a PNG file.	
	SDL_Surface* imgSurface = IMG_Load(path);
	if (imgSurface == NULL)
	{
		// Call IMG_GetError to get the error string.
		printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
		exit(0);
	}
	else
	{
		// Create texture from surface pixels	
		texture = SDL_CreateTextureFromSurface(renderer, imgSurface);

		// Also, you can use IMG_LoadTexture() to replace IMG_Load and SDL_CreateTextureFromSurface
		// texture = IMG_LoadTexture(renderer, path);

		if (texture == NULL)
		{
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		}

		width = imgSurface->w;
		height = imgSurface->h;

		// Get rid of old loaded surface
		SDL_FreeSurface(imgSurface);
	}
}

void Map::set(const char* pth, SDL_Renderer* ren)
{
	SDL_DestroyTexture(texture);
	renderer = ren;
	strcpy_s(path, pth);
	// Load a surface from a PNG file.	
	char file[100];
	sprintf_s(file, 100, "%s%02d.png", pth, mapnum+1);
	SDL_Surface* imgSurface = IMG_Load(file);

	if (imgSurface == NULL)
	{
		// Call IMG_GetError to get the error string.
		printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
		exit(0);
	}
	else
	{
		// Create texture from surface pixels	
		texture = SDL_CreateTextureFromSurface(renderer, imgSurface);

		// Also, you can use IMG_LoadTexture() to replace IMG_Load and SDL_CreateTextureFromSurface
		// texture = IMG_LoadTexture(renderer, path);

		if (texture == NULL)
		{
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		}

		width = imgSurface->w;
		height = imgSurface->h;

		// Get rid of old loaded surface
		SDL_FreeSurface(imgSurface);
	}
	
}


void Map::changemap(AnimeObject2& mainch, std::vector<Monster*>& mv)
{

	if (tile[mapnum][(mainch.getY() + mainch.getHeight()) * MAPTILEY / HEIGHT][(mainch.getX() + mainch.getWidth()) * MAPTILEX / WIDTH] == 5)
	{
		//clearing last map
		SDL_DestroyTexture(texture);
		//switch to next map
		mapnum ++;
		mainch.setMapnum(mapnum);
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, mapnum + 1);

		printf("%s%02d.png", path, mapnum);
		SDL_Surface* imgSurface = IMG_Load(file);

		if (imgSurface == NULL)
		{
			// Call IMG_GetError to get the error string.
			printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
			exit(0);
		}
		else
		{
			// Create texture from surface pixels	
			texture = SDL_CreateTextureFromSurface(renderer, imgSurface);

			// Also, you can use IMG_LoadTexture() to replace IMG_Load and SDL_CreateTextureFromSurface
			// texture = IMG_LoadTexture(renderer, path);

			if (texture == NULL)
			{
				printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
			}

			width = imgSurface->w;
			height = imgSurface->h;

			// Get rid of old loaded surface
			SDL_FreeSurface(imgSurface);
		}
		mainch.setPosition(startL[getmapnum()].x, startL[getmapnum()].y);
		setMonster(mv, 1);
		
	}
	else if (mainch.getMapFlag())
	{
		if (tile[mapnum][(mainch.getY() ) * MAPTILEY / HEIGHT][(mainch.getX()) * MAPTILEX / WIDTH] == 6)
		{
			//clearing last map
			SDL_DestroyTexture(texture);
			//switch to next map
			mapnum-=3;
			mainch.setMapnum(mapnum);
			char file[100];
			sprintf_s(file, 100, "%s%02d.png", path, mapnum + 1);

			printf("%s%02d.png", path, mapnum);
			SDL_Surface* imgSurface = IMG_Load(file);

			if (imgSurface == NULL)
			{
				// Call IMG_GetError to get the error string.
				printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
				exit(0);
			}
			else
			{
				// Create texture from surface pixels	
				texture = SDL_CreateTextureFromSurface(renderer, imgSurface);

				// Also, you can use IMG_LoadTexture() to replace IMG_Load and SDL_CreateTextureFromSurface
				// texture = IMG_LoadTexture(renderer, path);

				if (texture == NULL)
				{
					printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
				}

				width = imgSurface->w;
				height = imgSurface->h;

				// Get rid of old loaded surface
				SDL_FreeSurface(imgSurface);
			}
			mainch.setPosition(56 * WIDTH / MAPTILEX, 35 * HEIGHT / MAPTILEY);
			setMonster(mv, -3);
		}
		else if (tile[mapnum][(mainch.getY() + mainch.getHeight()) * MAPTILEY / HEIGHT][(mainch.getX() + mainch.getWidth()) * MAPTILEX / WIDTH] == 7)
		{
			//clearing last map
			SDL_DestroyTexture(texture);
			//switch to next map
			mapnum+=3;
			mainch.setMapnum(mapnum);
			char file[100];
			sprintf_s(file, 100, "%s%02d.png", path, mapnum + 1);

			printf("%s%02d.png", path, mapnum);
			SDL_Surface* imgSurface = IMG_Load(file);

			if (imgSurface == NULL)
			{
				// Call IMG_GetError to get the error string.
				printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
				exit(0);
			}
			else
			{
				// Create texture from surface pixels	
				texture = SDL_CreateTextureFromSurface(renderer, imgSurface);

				// Also, you can use IMG_LoadTexture() to replace IMG_Load and SDL_CreateTextureFromSurface
				// texture = IMG_LoadTexture(renderer, path);

				if (texture == NULL)
				{
					printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
				}

				width = imgSurface->w;
				height = imgSurface->h;

				// Get rid of old loaded surface
				SDL_FreeSurface(imgSurface);
			}
			mainch.setPosition(startL[getmapnum()].x, startL[getmapnum()].y);
			setMonster(mv, 3);
		}
		else if (tile[mapnum][(mainch.getY()) * MAPTILEY / HEIGHT][(mainch.getX()) * MAPTILEX / WIDTH] == 8)
		{
			//clearing last map
			SDL_DestroyTexture(texture);
			//switch to next map
			mapnum--;
			mainch.setMapnum(mapnum);
			char file[100];
			sprintf_s(file, 100, "%s%02d.png", path, mapnum + 1);

			printf("%s%02d.png", path, mapnum);
			SDL_Surface* imgSurface = IMG_Load(file);

			if (imgSurface == NULL)
			{
				// Call IMG_GetError to get the error string.
				printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
				exit(0);
			}
			else
			{
				// Create texture from surface pixels	
				texture = SDL_CreateTextureFromSurface(renderer, imgSurface);

				// Also, you can use IMG_LoadTexture() to replace IMG_Load and SDL_CreateTextureFromSurface
				// texture = IMG_LoadTexture(renderer, path);

				if (texture == NULL)
				{
					printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
				}

				width = imgSurface->w;
				height = imgSurface->h;

				// Get rid of old loaded surface
				SDL_FreeSurface(imgSurface);
			}
			mainch.setPosition(startR[getmapnum()].x, startR[getmapnum()].y);
			setMonster(mv, -1);
		}
		else if (tile[mapnum][(mainch.getY() + mainch.getHeight()) * MAPTILEY / HEIGHT][(mainch.getX() + mainch.getWidth()) * MAPTILEX / WIDTH] == 9)
		{
			//clearing last map
			SDL_DestroyTexture(texture);
			//switch to next map
			mapnum++;
			mainch.setMapnum(mapnum);
			char file[100];
			sprintf_s(file, 100, "%s%02d.png", path, mapnum + 1);

			printf("%s%02d.png", path, mapnum);
			SDL_Surface* imgSurface = IMG_Load(file);

			if (imgSurface == NULL)
			{
				// Call IMG_GetError to get the error string.
				printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
				exit(0);
			}
			else
			{
				// Create texture from surface pixels	
				texture = SDL_CreateTextureFromSurface(renderer, imgSurface);

				// Also, you can use IMG_LoadTexture() to replace IMG_Load and SDL_CreateTextureFromSurface
				// texture = IMG_LoadTexture(renderer, path);

				if (texture == NULL)
				{
					printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
				}

				width = imgSurface->w;
				height = imgSurface->h;

				// Get rid of old loaded surface
				SDL_FreeSurface(imgSurface);
			}
			mainch.setPosition(startL[getmapnum()].x, startL[getmapnum()].y);
			setMonster(mv, 1);
		}
		
		
	}
	
}

void Map::setMonster(std::vector<Monster*>& mv, int mapnumADD)
{
	FILE* fspawn;
	char file2[100];
	int xx, yy, Dflag;
	sprintf_s(file2, 100, "../Mspawn/%02d.txt", mv[0]->getMapnum() + mapnumADD + 1);
	fopen_s(&fspawn, file2, "r");
	for (int i = 0; i < mv.size(); i++)
	{
		mv[i]->setMapnum(mv[i]->getMapnum() + mapnumADD);
		fscanf_s(fspawn, "%d %d %d", &Dflag, &xx, &yy);
		mv[i]->setDeadFlag(Dflag);
		mv[i]->setPosition(xx * WIDTH / MAPTILEX, yy * HEIGHT / MAPTILEY);
		mv[i]->setBase(xx, yy);
		mv[i]->setHPP();
	}
}
void Map::setmap(std::vector<Monster*> &mv)
{
	//clearing last map
	SDL_DestroyTexture(texture);
	//switch to next map
	char file[100];
	sprintf_s(file, 100, "%s%02d.png", path, mapnum + 1);

	//printf("%s%02d.png", path, mapnum);
	SDL_Surface* imgSurface = IMG_Load(file);

	if (imgSurface == NULL)
	{
		// Call IMG_GetError to get the error string.
		printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
		exit(0);
	}
	else
	{
		// Create texture from surface pixels	
		texture = SDL_CreateTextureFromSurface(renderer, imgSurface);

		// Also, you can use IMG_LoadTexture() to replace IMG_Load and SDL_CreateTextureFromSurface
		// texture = IMG_LoadTexture(renderer, path);

		if (texture == NULL)
		{
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		}

		width = imgSurface->w;
		height = imgSurface->h;

		// Get rid of old loaded surface
		SDL_FreeSurface(imgSurface);
	}

	setMonster(mv, getmapnum() - mv[0]->getMapnum());
}

void Map::setmapnum(int n)
{
	mapnum = n;
}

int Map::getmapnum()
{
	return mapnum;
}

void Map::setcamera(AnimeObject2& mainch)
{
	camera.x = (mainch.getX() + mainch.getWidth() / 2 / SHRINK - camera.w / 2);
	camera.y = (mainch.getY() + mainch.getHeight() / 2 / SHRINK - camera.h / 2);
	//camera.x = (int)(WIDTH * (WIDTH / (double)mainch.getX())) ;
	if (camera.x > WIDTH - camera.w)
		camera.x = WIDTH - camera.w;
	if (camera.y > HEIGHT - camera.h)
		camera.y = HEIGHT - camera.h;
	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
}

SDL_Rect Map::getcamera()
{
	return camera;
}

void Map::close()
{
	// Free loaded image	
	SDL_DestroyTexture(texture);
}

void Map::draw(SDL_Rect dst, SDL_Rect src)
{
	SDL_Rect *d = &dst, *s = &src;
	
	if (dst.x == ALLREGION)
	{
		d = NULL;
	}
	if (src.x == ALLREGION)
	{
		s = NULL;
	}

	SDL_RenderCopy(renderer, texture, s, d);
}

int Map::getWidth()
{
	return width;
}

int Map::getHeight()
{
	return height;
}

void Map::initialize()
{
	mapnum = 0;
	camera.h = CAMERAH;
	camera.w = CAMERAW;
	startR[0] = { 57 * WIDTH / MAPTILEX, 36 * HEIGHT / MAPTILEY };
	startR[1] = { 59 * WIDTH / MAPTILEX, 4 * HEIGHT / MAPTILEY };
	startR[2] = { 55 * WIDTH / MAPTILEX, 19 * HEIGHT / MAPTILEY };
	startR[3] = { 59 * WIDTH / MAPTILEX, 19 * HEIGHT / MAPTILEY };
	startR[4] = { 40 * WIDTH / MAPTILEX, 20 * HEIGHT / MAPTILEY };
	startR[5] = { 40 * WIDTH / MAPTILEX, 20 * HEIGHT / MAPTILEY };
	startR[6] = { 40 * WIDTH / MAPTILEX, 20 * HEIGHT / MAPTILEY };

	startL[0] = { 5 * WIDTH / MAPTILEX, 36 * HEIGHT / MAPTILEY };
	startL[1] = { 2 * WIDTH / MAPTILEX, 35 * HEIGHT / MAPTILEY };
	startL[2] = { 2 * WIDTH / MAPTILEX, 36 * HEIGHT / MAPTILEY };
	startL[3] = { 1 * WIDTH / MAPTILEX, 12 * HEIGHT / MAPTILEY };
	startL[4] = { 2 * WIDTH / MAPTILEX, 36 * HEIGHT / MAPTILEY };
	startL[5] = { 3 * WIDTH / MAPTILEX, 2 * HEIGHT / MAPTILEY };
	startL[6] = { 2 * WIDTH / MAPTILEX, 24 * HEIGHT / MAPTILEY };
	width = 0;
	height = 0;
}