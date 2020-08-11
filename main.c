#include<SDL2/SDL.h>
#include<stdio.h>
//720x 480
//480x320 ? 
#define SCREEN_WIDTH	720
#define SCREEN_HEIGHT	480
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
		"6dn9 PiTouch v420",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_FULLSCREEN
    );
    //Initialize Window STUFF
    if(window == NULL){
        fprintf(stderr, "Couldn't initialize SDL_CreateWindow: %s\n", SDL_GetError());
        return 1;
    }
    screenSurface  = SDL_GetWindowSurface(window); //why do we set surface to window?
    renderer = SDL_CreateSoftwareRenderer(screenSurface);
    //SDL_Rect dBackground	= {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	
    SDL_Rect dLeft		= {0,0,SCREEN_WIDTH/3,SCREEN_HEIGHT/3};
    SDL_Rect dCenter	= {(SCREEN_WIDTH/3),0,SCREEN_WIDTH/3,SCREEN_HEIGHT/3};
    SDL_Rect dRight		= {((SCREEN_WIDTH/3)*2),0,SCREEN_WIDTH/3,SCREEN_HEIGHT/3};
	
	int dR = 0;
	int dG = 0;
	int dB = 0;
	
	while(1)
	{
		
		SDL_RenderClear(renderer); //do i need this?
		SDL_FillRect(screenSurface, NULL, SDL_MapRGBA(screenSurface->format, dR, dG, dB, 0));
		SDL_FillRect(screenSurface, &dLeft, SDL_MapRGBA(screenSurface->format, 255, 0, 0, 0));
		SDL_FillRect(screenSurface, &dCenter, SDL_MapRGBA(screenSurface->format, 0, 255, 0, 0));
		SDL_FillRect(screenSurface, &dRight, SDL_MapRGBA(screenSurface->format, 0, 0, 255, 0));
		SDL_SetRenderDrawColor(renderer, 250, 250, 250, 0);
		drawBox(renderer, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT/3);
		SDL_UpdateWindowSurface(window);
		
		//Handle Events Here
		SDL_Event testEvent;
		
		while(SDL_PollEvent(&testEvent)){
			if (testEvent.type == SDL_QUIT || (testEvent.type == SDL_KEYDOWN && testEvent.key.keysym.sym == SDLK_ESCAPE))
            {
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;
            }
			if(testEvent.type == SDL_FINGERDOWN && testEvent.tfinger.x >= dLeft.x && testEvent.tfinger.x <= (dLeft.x+ dLeft.w))
			{
				dR = 255;
				dG = 0;
				dB = 0;
				printf("Red\n");
				printf("%f\n", testEvent.tfinger.x);
			}
			if(testEvent.type == SDL_FINGERDOWN && testEvent.tfinger.x >= dCenter.x && testEvent.tfinger.x <= (dCenter.x+ dCenter.w))
			{
				dR = 0;
				dG = 255;
				dB = 0;
				printf("Green\n");
				printf("%f\n", testEvent.tfinger.x);
			}
			if(testEvent.type == SDL_FINGERDOWN && testEvent.tfinger.x >= dRight.x && testEvent.tfinger.x <= (dRight.x+ dRight.w))
			{
				dR = 0;
				dG = 0;
				dB = 255;
				printf("Blue\n");
				printf("%f\n", testEvent.tfinger.x);
			}
		}
		SDL_Delay(10);
	}
	return 0;
}
/*
if (testEvent.type == SDL_MOUSEBUTTONDOWN && testEvent.button.button == SDL_BUTTON_LEFT && testEvent.button.x >= exitButton.x && testEvent.button.x <= (exitButton.x + exitButton.w) && testEvent.button.y >= exitButton.y && testEvent.button.y<= (exitButton.y + exitButton.h))
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 0;
	}
*/