#include<SDL2/SDL.h>
#include<stdio.h>

#define SCREEN_WIDTH	480
#define SCREEN_HEIGHT	320
#define BLOCKSIZE		32
#define BOARD_WIDTH		15
#define BOARD_HEIGHT	10

//my custom box drawing function
int drawBox(SDL_Renderer* renderer, int x, int y, int w, int h){
    SDL_RenderDrawLine(renderer, x    , y    , x+w-1, y    );
    SDL_RenderDrawLine(renderer, x    , y+h-1, x+w-1, y+h-1);
    SDL_RenderDrawLine(renderer, x    , y    , x    , y+h-1);
    SDL_RenderDrawLine(renderer, x+w-1, y    , x+w-1, y+h-1);
    return 0;
}
int main()
{
	//These are a part of the necessary initialization
	SDL_Window* window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);//I think I read that this will crash pi.
    if (SDL_Init(SDL_INIT_VIDEO)<0){
        fprintf(stderr, "Couldn't initialize SDL2: %s\n", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow(
		"Shockingly Generic Video Game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0
    );
    //Initialize Window STUFF
    if(window == NULL){
        fprintf(stderr, "Couldn't initialize SDL_CreateWindow: %s\n", SDL_GetError());
        return 1;
    }
	//Initialize PNG STUFF
	//int imgFlags = IMG_INIT_PNG;
	//if( !( IMG_Init( imgFlags ) & imgFlags ) ){
			//printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		//}
	
	//Create Surface
    screenSurface  = SDL_GetWindowSurface(window); //why do we set surface to window?
    renderer = SDL_CreateSoftwareRenderer(screenSurface);

    SDL_Rect dBackground	= {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	int dColor = 0;
	while(1)
	{
		//SDL_RenderFillRect(renderer, &menuBackground);
		//SDL_RenderCopy(renderer, startPNG, NULL, &startButton);
		//SDL_RenderCopy(renderer, exitPNG, NULL, &exitButton);
		
		SDL_RenderClear(renderer); //do i need this?

		SDL_FillRect(screenSurface, NULL, SDL_MapRGBA(screenSurface->format, 255, dColor, 0, 0));
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		drawBox(renderer, 0,0,32,32);
		SDL_UpdateWindowSurface(window);
		
		//Handle Events Here
		SDL_Event testEvent;
		//if(menuStatus == 1)
		//{
		while(SDL_PollEvent(&testEvent)){
			//if (testEvent.type == SDL_KEYDOWN && testEvent.key.keysym.sym == SDLK_y)
            //{
				//menuStatus = 0;
            //}
			//if (testEvent.type == SDL_MOUSEBUTTONDOWN && testEvent.button.button == SDL_BUTTON_LEFT && testEvent.button.x >= startButton.x && testEvent.button.x <= (startButton.x + startButton.w) && testEvent.button.y >= startButton.y && testEvent.button.y<= (startButton.y + startButton.h))
            //{
				//menuStatus = 0;
            //}
			if (testEvent.type == SDL_QUIT || (testEvent.type == SDL_KEYDOWN && testEvent.key.keysym.sym == SDLK_ESCAPE))
            {
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;
            }
			if (testEvent.type == SDL_FINGERDOWN || testEvent.button.button == SDL_BUTTON_LEFT)
			{
				dColor = 255;
			}
			//if (testEvent.type == SDL_MOUSEBUTTONDOWN && testEvent.button.button == SDL_BUTTON_LEFT && testEvent.button.x >= exitButton.x && testEvent.button.x <= (exitButton.x + exitButton.w) && testEvent.button.y >= exitButton.y && testEvent.button.y<= (exitButton.y + exitButton.h))
            //{
				//SDL_DestroyRenderer(renderer);
				//SDL_DestroyWindow(window);
                //SDL_Quit();
                //return 0;
            //}
		}
		//}
		SDL_Delay(10);
	}
	return 0;
}
//Abstracting the game play
/*
int gamePlay(SDL_Surface* screenSurface, SDL_Renderer* renderer, SDL_Window* window, int menuStatus){
	//Create Rectangles
    SDL_Rect backgroundBoy 	= {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    SDL_Rect appleBoy			= {0,0,BLOCK_SIZE-4,BLOCK_SIZE-4};
    SDL_Rect snakeBoy		= {0,0,BLOCK_SIZE-4,BLOCK_SIZE-4};
	SDL_Rect tileDirection 	= {0,0,8,8};
	
	//head = snakeHead
    gameTile snakeHead; 			
    snakeHead.y = BOARD_HEIGHT/2;
    snakeHead.x = BOARD_WIDTH/2;
    snakeHead.vY = 0;
    snakeHead.vX = 0;
    
    gameTile snakeTail;
    snakeTail.y = snakeHead.y;
    snakeTail.x = snakeHead.x;
	snakeTail.vY = 0;
	snakeTail.vX = 0;

	//applesGrid = gameGrid
    gridInfo gameGrid[BOARD_HEIGHT][BOARD_WIDTH] = {EMPTY};
    gameGrid[3][3].content = APPLE;
    gameGrid[5][8].content = APPLE;    
    gameGrid[5][9].content = APPLE;    
    gameGrid[5][10].content = APPLE;    
    gameGrid[5][11].content = APPLE;    
    gameGrid[10][9].content = APPLE;    
    gameGrid[10][10].content = APPLE;    
    
    gameGrid[snakeTail.y][snakeTail.x].vXa = 0;
    gameGrid[snakeTail.y][snakeTail.x].vYa = 0;
	
	///*
	//quedVelocityY = QvY
	//quedVelocityX = QvX
	//lastSample = lastTime
	int QvY = 0;
	int QvX = 0;
    int gameLoop = 1;
	Uint32 lastTime = 0;
    Uint32 currentTime = 0;
    const int delayCustom = 50;
	//while loop
	while(gameLoop == 1){
		currentTime = SDL_GetTicks();
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));
		SDL_SetRenderDrawColor(renderer, 237, 191, 157, 0);
		SDL_RenderFillRect(renderer, &backgroundBoy);
		int colorR = 255;
		int colorG = 255;
		int colorB = 255;
		int gridRunnerX = 0;
		int gridRunnerY = 0;
			
		//DRAW - GRID
		while(gridRunnerY<BOARD_HEIGHT){
			gridRunnerX = 0;
			while(gridRunnerX<BOARD_WIDTH){
				if(colorR==255){
					colorR = colorG = colorB = 0;
				}
				else{
					colorR = colorG = colorB = 255;
				}
				SDL_SetRenderDrawColor(renderer, colorR, colorG, colorB, 0);
				drawBox(renderer,gridRunnerX*BLOCK_SIZE,gridRunnerY*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE);
				++gridRunnerX;
			}
			if(colorR==255){
					colorR = colorG = colorB = 0;
				}
				else{
					colorR = colorG = colorB = 255;
				}
			++gridRunnerY;
		}
		drawBox(renderer, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
		
		//MOVEMENT
        if(currentTime > lastTime + delayCustom){
		//MOVEMENT - HEAD
			snakeHead.vY = QvY;
			snakeHead.vX = QvX;
            gameGrid[snakeHead.y][snakeHead.x].vYa = snakeHead.vY;
			gameGrid[snakeHead.y][snakeHead.x].vXa = snakeHead.vX; 
            snakeHead.y = snakeHead.y + snakeHead.vY;
            snakeHead.x = snakeHead.x + snakeHead.vX;
		//DEATH - SELF COLLISION
			if(gameGrid[snakeHead.y][snakeHead.x].content == SNAKE && (snakeHead.vY != 0 || snakeHead.vX != 0)){
				SDL_DestroyWindow(window);
				SDL_Quit();
				return 0;
			}
		//MOVEEMENT - TAIL
            if(gameGrid[snakeHead.y][snakeHead.x].content == EMPTY){
				gameGrid[snakeTail.y][snakeTail.x].content = EMPTY;
				const int newY = snakeTail.y+gameGrid[snakeTail.y][snakeTail.x].vYa;
				snakeTail.x = snakeTail.x+gameGrid[snakeTail.y][snakeTail.x].vXa;
				snakeTail.y = newY;
            }
			gameGrid[snakeHead.y][snakeHead.x].content = SNAKE;
            lastTime = currentTime;
        }
		//DEATH - SCREEN COLLISION
		if(snakeHead.y < 0 || snakeHead.y >= BOARD_HEIGHT || snakeHead.x < 0 || snakeHead.x >= BOARD_WIDTH){
			SDL_DestroyWindow(window);
			SDL_Quit();
			return 0;
		}
			
        gridRunnerX = 0;
        gridRunnerY = 0;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		//DRAW - ENTITIES
		while(gridRunnerY<BOARD_HEIGHT){
            gridRunnerX = 0;
            while(gridRunnerX<BOARD_WIDTH){
                if(gameGrid[gridRunnerY][gridRunnerX].content==APPLE){
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
                    appleBoy.x = gridRunnerX*BLOCK_SIZE+2;
                    appleBoy.y = gridRunnerY*BLOCK_SIZE+2;
                    SDL_RenderFillRect(renderer, &appleBoy);
                }
                if(gameGrid[gridRunnerY][gridRunnerX].content==SNAKE){
                    
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                    snakeBoy.x = gridRunnerX*BLOCK_SIZE+2;
                    snakeBoy.y = gridRunnerY*BLOCK_SIZE+2;
                    SDL_RenderFillRect(renderer, &snakeBoy);
                }
		//DRAW - DIRECTIONAL INDICATORS		
				SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0);
				tileDirection.x = gridRunnerX*BLOCK_SIZE + BLOCK_SIZE/2 - tileDirection.w/2 + gameGrid[gridRunnerY][gridRunnerX].vXa*BLOCK_SIZE/4;
				tileDirection.y = gridRunnerY*BLOCK_SIZE + BLOCK_SIZE/2 - tileDirection.h/2 + gameGrid[gridRunnerY][gridRunnerX].vYa*BLOCK_SIZE/4;
				SDL_RenderFillRect(renderer, &tileDirection);
                ++gridRunnerX;
            }
            ++gridRunnerY;
        }
		//DRAW - HEAD INDICATOR
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		snakeBoy.x = snakeHead.x*BLOCK_SIZE+2;
		snakeBoy.y = snakeHead.y*BLOCK_SIZE+2;
		SDL_RenderDrawRect(renderer, &snakeBoy);
		//DRAW - TAIL INDICATOR
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
		snakeBoy.x = snakeTail.x*BLOCK_SIZE + 2;
		snakeBoy.y = snakeTail.y*BLOCK_SIZE + 2;
		SDL_RenderDrawRect(renderer, &snakeBoy);
		
		SDL_UpdateWindowSurface(window);
		//EVENTS
		SDL_Event gameEvent;
		//if(menuStatus == 0){
        while(SDL_PollEvent(&gameEvent)){
            if (gameEvent.type == SDL_QUIT || (gameEvent.type == SDL_KEYDOWN && gameEvent.key.keysym.sym == SDLK_ESCAPE))
            {
				SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;
            }
            if (gameEvent.type == SDL_KEYDOWN && gameEvent.key.keysym.sym == SDLK_w && snakeHead.vY != 1)
            {
                QvY = -1;
				QvX =  0;
            }
            if (gameEvent.type == SDL_KEYDOWN && gameEvent.key.keysym.sym == SDLK_s && snakeHead.vY != -1)
            {
                QvY =  1;
				QvX =  0;
            }
            if (gameEvent.type == SDL_KEYDOWN && gameEvent.key.keysym.sym == SDLK_a && snakeHead.vX != 1)
            {
                QvY =  0;
				QvX = -1;
            }
            if (gameEvent.type == SDL_KEYDOWN && gameEvent.key.keysym.sym == SDLK_d && snakeHead.vX != -1)
            {
				QvY =  0;
				QvX =  1;
            }
        }
		//}
        SDL_Delay(5);
		
	}
return EXIT_SUCCESS;
}
*/
/*
int main(int argc, char* args[])
{
    //These are a part of the necessary initialization
	SDL_Window* window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);
    if (SDL_Init(SDL_INIT_VIDEO)<0){
        fprintf(stderr, "Couldn't initialize SDL2: %s\n", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow(
		"Shockingly Generic Video Game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0
    );
    //Initialize Window STUFF
    if(window == NULL){
        fprintf(stderr, "Couldn't initialize SDL_CreateWindow: %s\n", SDL_GetError());
        return 1;
    }
	//Initialize PNG STUFF
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ){
			printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		}
	
	//Create Surface
    screenSurface  = SDL_GetWindowSurface(window);
    renderer = SDL_CreateSoftwareRenderer(screenSurface);

	int menuStatus = 1;
	int gameStatus = 1;
    while(1)
    {
		switch(gameStatus){
		case 1 : //startMenu
			printf("case: 1\tstartMenu\n");
			startMenu(screenSurface, renderer, window, menuStatus);
			gameStatus = 2;
			menuStatus = 0;
			break;
		case 2 ://gamePlay
			printf("case: 2\tgamePlay\n");
			gamePlay(screenSurface, renderer, window, menuStatus);
			menuStatus = 1;
			gameStatus = 3;
			break;
		case 3 ://gamePlay
			printf("case: 3\tgameOver\n");
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			//return 0;
			break;
		}
	}
}
	*/