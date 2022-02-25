#include "raylib.h"

using namespace std;
#include <iostream>
#include "board.h"
int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 800;  
    const int genNumMines = 5;
    const int nX = 10;
    const int nY = 10;

  

    InitWindow(screenWidth, screenHeight, "MineSweeper");

    Board b = Board(nX,nY,screenWidth,screenHeight,genNumMines);
    b.restart();

    SetTargetFPS(60);              
    
    while (!WindowShouldClose())   
    {
        if (IsKeyPressed(KEY_R)){
            b.restart();
        }

        if(b.isAlive() && !b.hasWon()){
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                Vector2 Mpos = GetMousePosition();
                b.discoverPlace(Mpos.x/(screenWidth/nX),Mpos.y/(screenHeight/nY));
            }

            if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                Vector2 Mpos = GetMousePosition();
                b.flagPlace(Mpos.x/(screenWidth/nX),Mpos.y/(screenHeight/nY));
            }
        }
       

        BeginDrawing();
        b.show();
        EndDrawing();
    
    }

   
    CloseWindow();     
  

    return 0;
}