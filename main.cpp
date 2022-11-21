#include "raylib.h"

using namespace std;
#include <iostream>
#include "board.h"
int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 800;  
    const int genNumMines = 150;
    const int nX = 31;
    const int nY = 31;
    const int scrollSpeed = 1;
  

    InitWindow(screenWidth, screenHeight, "MineSweeper");

    Board b = Board(nX,nY,screenWidth,screenHeight,genNumMines);
    b.restart();

    SetTargetFPS(60);              
	CameraGame c = CameraGame(screenWidth,screenHeight);

    while (!WindowShouldClose())   
    {
 
		b.interactBoard(&c);
		
		c.update();

        BeginDrawing(); 

        ClearBackground(RAYWHITE);
        
        BeginMode2D(c.getcamera());  
        b.show();
        EndMode2D();


        EndDrawing();
    
    }

   
    CloseWindow();     
  

    return 0;
}