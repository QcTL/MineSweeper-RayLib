#ifndef board_H
#define board_H

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include "raylib.h"
using namespace  std;

class Board{

	private:
		bool ** ShowedMat;
		bool ** FlagedMat;
		int ** ValueMat; //Including mines 
		int mX, mY;
		int screenX, screenY;
		vector<pair<int,int>> Surround;
		int nMines;
		bool startTouch;
		int nFound;

		bool alive;
		bool won;

		int setNumberBoard(int i, int j);
		void cleanTables();
		void generateMines();
	public:
		Board();
		Board(int mX, int mY,int screenX, int screenY, int nMines);
		void discoverPlace(int disX, int disY);
		void flagPlace(int disX, int disY);
		
		void show();

		void restart();
		bool isAlive();
		bool hasWon();
};


#endif