#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
	#include <windows.h>
	#define sec 1000
	#define sleep Sleep
#elif defined(__linux__)
	#include <unistd.h>
	#define sec 1
#else
	#error Unknown_OS
#endif


void cls(){
#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
    system ( "cls"   );
#elif defined(__linux__)
    system ( "clear" );
#elif defined(__APPLE__) && defined(__MACH__)
    system ( "clear" );
#elif defined(unix) || defined(__unix__) || defined(__unix)
    system ( "clear" );
#else
    #error Unknown_OS
#endif
}

int rnd(){
	srand(time(0));
	return rand();
}

class blocks{ //Stores the relative positions of all pieces
	public:
	int* xs;
	int* ys;
	blocks(char t){
		xs = new int[4];
		ys = new int[4];
		relatives(t);
	}
	~blocks(){
		delete xs;
		delete ys;
	}
	void relatives(char t){
		// rel 0
		xs[0] = 0;
		ys[0] = 0;
		// rel 1
		xs[1] = 0;
		ys[1] = 1;
		// rel 2
		if(t=='o' || t=='s'){
			xs[2] = 1;
			ys[2] = 1;
		}
		else if(t=='z'){
			xs[2] = -1;
			ys[2] = 1;
		}
		else if(t=='i' || t=='l' || t=='j'){
			xs[2] = 0;
			ys[2] = 2;
		}
		else{
			xs[2] = -1;
			ys[2] = 0;
		}
		// rel 3
		if(t=='o' || t=='z' || t=='l' || t=='t'){
			xs[3] = 1;
			ys[3] = 0;
		}
		else if(t=='j' || t=='s'){
			xs[3] = -1;
			ys[3] = 0;
		}
		else{
			xs[3] = 0;
			ys[3] = -1;
		}
	}
};

class piece{
	public:
	int rx;  //x and y coords of the root
	int ry;
	char t;  //type of piece {i, j, l, o, s, z, t} <- {0, 1, 2, 3, 4, 5, 6}
	int rot; //rotation of the piece k%4=={0, 1, 2, 3} will do ++ or -- operations
	blocks* blk;
	
	piece(){ // start pos is at x=5, y=19
		int type = rand() % 7;
		if(type==0) t = 'i';
		else if(type==1) t = 'j';
		else if(type==2) t = 'l';
		else if(type==3) t = 'o';
		else if(type==4) t = 's';
		else if(type==5) t = 'z';
		else t = 't';
		rot = 0;
		rx = 5;
		ry = 20;
		blk = new blocks(t);
	}

	piece(char nT){
		t = nT;
		rot = 0;
		rx = 5;
		ry = 20;
		blk = new blocks(t);
	}

	~piece(){
		delete blk;
	}

};

class stage{
	public:
	bool** map;
	piece* falling; // Currently falling piece
	piece* hold; // for when pressing C and holding a piece
	int RX;
	int RY; // Root coords of falling piece

	stage(){
		map = new bool*[21];
		for(int i=0; i<21; i++){
			*(map+i) = new bool[10];
			for(int j=0; j<10; j++){
				*(*(map+i)+j) = false;
			}
		}
		falling = nullptr;
		hold = nullptr;
	}
	
	~stage(){
		if(map!=nullptr){
			for(int i=0; i<21; i++){
				if(*(map+i) != nullptr) delete *(map+i);
			}
			delete map;
		}
		if(falling!=nullptr) delete falling;
		if(hold!=nullptr) delete hold;
	}
	
	void drawBoard(){
		cls();
		for(int y=20; y>0; y--){
			for(int x=0; x<10; x++){
				if(checkDraw(y, x)) print();
				else print(y, x);
			}
			std::cout << "|\n";
		}
	}

	void drawStats(){
		// Stats and scoreboard, held piece, etc
		// Will need a small board for held piece
	}

	void newPiece(){ // Spawns a random piece
		if(falling!=nullptr) delete falling;
		falling = new piece();
		RX = 5;
		RY = 19;
	}

	void newPiece(char t){ // Spawns a piece of type t
		if(falling!=nullptr) delete falling;
		falling = new piece(t);
		RX = 5;
		RY = 19;
	}

	bool fall(){ // Makes the current falling piece go down, if possible
		if(checkFall()){
			RY--;
			return true;
		}
		else return false;
	}

	void place(){
		map[falling->blk->ys[0]+RY][falling->blk->xs[0]+RX] = true;
		map[falling->blk->ys[1]+RY][falling->blk->xs[1]+RX] = true;
		map[falling->blk->ys[2]+RY][falling->blk->xs[2]+RX] = true;
		map[falling->blk->ys[3]+RY][falling->blk->xs[3]+RX] = true;
		std::cout << "PLACED\n";
	}

	void checkLines(){

	}

	void rotLeft(){

	}

	void rotRight(){

	}

	private:
	bool checkDraw(int y, int x){
		if(x==(falling->blk->xs[0]+RX) && y==(falling->blk->ys[0]+RY)) return true;
		else if(x==(falling->blk->xs[1]+RX) && y==(falling->blk->ys[1]+RY)) return true;
		else if(x==(falling->blk->xs[2]+RX) && y==(falling->blk->ys[2]+RY)) return true;
		else if(x==(falling->blk->xs[3]+RX) && y==(falling->blk->ys[3]+RY)) return true;
		else return false;
	}

	bool checkFall(){
		// If theres a block beneath
		if(map[falling->blk->ys[0]+RY-1][falling->blk->xs[0]+RX]) return false;
		else if(map[falling->blk->ys[1]+RY-1][falling->blk->xs[1]+RX]) return false;
		else if(map[falling->blk->ys[2]+RY-1][falling->blk->xs[2]+RX]) return false;
		else if(map[falling->blk->ys[3]+RY-1][falling->blk->xs[3]+RX]) return false;
		// If hit bottom
		else if((falling->blk->ys[0]+RY-1)<1) return false;
		else if((falling->blk->ys[1]+RY-1)<1) return false;
		else if((falling->blk->ys[2]+RY-1)<1) return false;
		else if((falling->blk->ys[3]+RY-1)<1) return false;
		else return true;
	}

	void print(int y, int x){
		if(map[y][x])
			std::cout << "|x";
		else
			std::cout << "| ";
	}

	void print(){
		std::cout << "|x";
	}
};
