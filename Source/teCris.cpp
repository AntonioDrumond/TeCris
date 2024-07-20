#include "game.hpp"
#include <SDL2/SDL.h>

bool alive = true;

int main(){
	if(SDL_Init(SDL_INIT_VIDEO) != 0) return 1;
	SDL_Event event;
	
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

	std::cout << "Focus the \"controller\" window and press LEFT and RIGHT to move, UP and DOWN to rotate and C to swap the piece\nPress ENTER to play\n";
	getchar();
	cls();

	int i=0;
	stage* stg = new stage();
	while(i<100 && alive){
		// Game updates
		if(stg->falling==nullptr) stg->newPiece();
		bool shldPlace = !stg->fall();
		if(shldPlace) stg->place();
		stg->drawBoard();
		if(shldPlace){
			delete stg->falling;
			stg->falling = nullptr;
		}

		wait(0.5);
		// Input handling
		while (SDL_PollEvent(&event)){
			switch (event.type){
				case SDL_QUIT:
					alive = false;
					std::cout << "SDL_QUIT\n";
				break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_LEFT){
						stg->left();
					}
					else if (event.key.keysym.sym == SDLK_RIGHT){
						stg->right();
					}
				break;
			}
		}

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	std::cout << "Press ENTER to exit ";
	getchar();
	return 0;
}

