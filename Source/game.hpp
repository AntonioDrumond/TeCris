#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
	#include <windows.h>
	#define sec 1000
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
		ry = 19;
		blk = new blocks(t);
	}

};

class stage{
	public:
	bool** map;
	piece* falling;
	int* xs; // x and y coords of the falling piece
	int* ys;

	stage(){
		map = new bool*[20];
		for(int i=0; i<20; i++){
			*(map+i) = new bool[10];
			for(int j=0; j<10; j++){
				*(*(map+i)+j) = false;
			}
		}
		falling = new piece();
		xs = new int[4];
		ys = new int[4];
	}
	
	~stage(){
		if(map!=nullptr){
			for(int i=0; i<20; i++){
				if(*(map+i) != nullptr) delete *(map+i);
			}
			delete map;
		}
		delete xs;
		delete ys;
	}
	
	void draw(){
		for(int y=19; y>-1; y--){
			for(int x=0; x<10; x++){
				print(y, x);
			}
			std::cout << "|\n";
		}
	}

	private:
	void print(int y, int x){
		if(map[y][x])
			std::cout << "|x";
		else
			std::cout << "| ";
	}
};
