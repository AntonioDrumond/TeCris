#include "game.hpp"

int main(){
	srand(time(0));
	piece* testing = new piece();
	int choice = 0;
	do{
		cls();
		std::cout << "type: " << testing->t << "\n";
		std::cout << "block 0: " << testing->blk->xs[0] << "," << testing->blk->ys[0] << "\n";
		std::cout << "block 1: " << testing->blk->xs[1] << "," << testing->blk->ys[1] << "\n";
		std::cout << "block 2: " << testing->blk->xs[2] << "," << testing->blk->ys[2] << "\n";
		std::cout << "block 3: " << testing->blk->xs[3] << "," << testing->blk->ys[3] << "\n";
		std::cout << "0 para sair: ";
		std::cin >> choice; getchar();
	} while(choice!=0);
	std::cout << "\n\npressione ENTER para sair";
	getchar();
	return 0;
}
