#include "game.hpp"

bool alive = true;

int main(){
	std::cout << "Press ENTER to play\n";
	getchar();
	cls();
	/*while(alive){	// Game loop
		cls();
	}*/
	int i=0;
	stage* stg = new stage();
	while(i<100){
		if(stg->falling==nullptr) stg->newPiece();
		bool shldPlace = !stg->fall();
		if(shldPlace) stg->place();
		stg->drawBoard();
		//std::cout << "flag\n"; getchar();
		if(shldPlace){
			delete stg->falling;
			stg->falling = nullptr;
		}
		sleep(1*sec);
	}
	std::cout << "Press ENTER to exit ";
	getchar();
	return 0;
}
