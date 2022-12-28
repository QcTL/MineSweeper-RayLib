#ifndef board_H
#define board_H

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include "raylib.h"
#include "camera.h"
using namespace  std;

class Board{

	private:
		bool ** ShowedMat;
		bool ** FlagedMat;
		int ** ValueMat; //Including mines 
		int mX, mY;
		float screenX, screenY;
		vector<pair<int,int>> Surround;
		int nMines;
		bool startTouch;
		int nFound;

		bool alive;
		bool won;

		int nFlags;


		int setNumberBoard(int i, int j);
		void cleanTables();
		void generateMines();
	public:
		Board();
		Board(int mX, int mY,int screenX, int screenY, int nMines);
		~Board();
		int discoverPlace(int disX, int disY);
		int flagPlace(int disX, int disY);
		
		void show();
		void showGUI();

		Color getColorNumber(int n);

		void restart();
		bool isAlive();
		bool hasWon();
		
		void interactBoard(CameraGame* c);
};


#endif