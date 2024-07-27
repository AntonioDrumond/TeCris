#include "game.hpp"
#include <SDL2/SDL.h>

int main(){
	if(SDL_Init(SDL_INIT_VIDEO) != 0) return 1;
	SDL_Event event;
	
	std::cout << "Focus the \"controller\" window and press LEFT and RIGHT to move, UP and DOWN to rotate and C to swap the piece\nPress ENTER to play\n";
	getchar();

	// Creating "controller" window
	SDL_Window* window = SDL_CreateWindow("Controller", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 200, 200, SDL_WINDOW_SHOWN);
	if(window == nullptr){
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == nullptr){
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	cls();
	stage* stg = new stage();
	int alive = 0;
	bool canSwap = true;

	while(alive == 0){
		// Game updates
		if(stg->falling==nullptr){
			stg->newPiece();
			canSwap = true;
		}
		bool shldPlace = !stg->fall();
		if(shldPlace && stg->RY> 18) alive = 1;
		if(shldPlace && stg->RY<=18) stg->place();
		stg->drawBoard();
		if(shldPlace){
			delete stg->falling;
			stg->falling = nullptr;
			stg->checkLines();
		}

		wait(0.5);
		// Input handling
		if(!shldPlace){
			while (SDL_PollEvent(&event)){
				switch (event.type){
					case SDL_QUIT:
						alive = 2;
						std::cout << "Quitting game...\n";
						wait(0.3);
					break;
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_LEFT){
							stg->left();
						}
						else if(event.key.keysym.sym == SDLK_RIGHT){
							stg->right();
						}
						else if(event.key.keysym.sym== SDLK_UP){
							stg->rotRight();
						}
						else if(event.key.keysym.sym == SDLK_DOWN){
							stg->rotLeft();
						}
						else if(event.key.keysym.sym == SDLK_c){
							if(canSwap){
								canSwap = false;
								stg->swap();
							}
						}
					break;
				}
			}
		}
	}

	if(alive == 1){
		std::cout << "YOU LOST!\n";
		wait(1);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	std::cout << "Press ENTER to exit ";
	getchar();
	return 0;
}

