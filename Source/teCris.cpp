#include "game.hpp"

bool alive = true;

int main(){
	std::cout << "Press ENTER to play\n";
	stage* stg = new stage();
	getchar();
	cls();
	stg->draw();
	getchar();
	cls();
	/*while(alive){	// Game loop
		cls();
	}*/
	std::cout << "Press ENTER to exit ";
	getchar();
	return 0;
}
