#ifndef camera_H
#define camera_H

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include "raylib.h"
using namespace  std;

class CameraGame{

	private:
		Camera2D cameraU;
		
		Vector2 prevMousePos; 
		Vector2 curMousePos;

		int screenWidth;int screenHeight;
		float zoomCount;

		Vector2 Vector2Add(Vector2 a, Vector2 b);
		Vector2 Vector2Subtract(Vector2 a, Vector2 b);
	public:
		CameraGame();
		CameraGame(int mX, int mY);
		
		void update();
		
		Vector2 getPositionClick();
		Camera2D getcamera();
};


#endif