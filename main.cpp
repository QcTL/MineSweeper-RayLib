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
    
    Camera2D camera = {0};
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;
    camera.target = (Vector2){ screenWidth/2.0f, screenHeight/2.0f }; 
    while (!WindowShouldClose())   
    {
 
        if(camera.zoom > 1 && IsKeyPressed(KEY_Q)){
           
            Vector2 zoomWhere = GetScreenToWorld2D(GetMousePosition(),camera);
             camera.zoom = camera.zoom -0.5f;
            camera.target = zoomWhere;
            
        }
        else if(camera.zoom < 10 && IsKeyPressed(KEY_E)){
            Vector2 zoomWhere = GetScreenToWorld2D(GetMousePosition(),camera);
            camera.zoom = camera.zoom +0.5f;
            camera.target = zoomWhere;
        }
        if (IsKeyPressed(KEY_R)){
            b.restart();
        }

        //Moving:
        if (IsKeyDown(KEY_W)){
           camera.offset.y = camera.offset.y + 5;
        }else if (IsKeyDown(KEY_S)){
            camera.offset.y = camera.offset.y - 5;
        }
        if (IsKeyDown(KEY_D)){
            camera.offset.x = camera.offset.x - 5;
        }else if (IsKeyDown(KEY_A)){
            camera.offset.x = camera.offset.x + 5;
        }





        if(b.isAlive() && !b.hasWon()){
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                Vector2 Mpos = GetScreenToWorld2D(GetMousePosition(),camera);
                b.discoverPlace(Mpos.x/(screenWidth/nX),Mpos.y/(screenHeight/nY));
            }

            if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                Vector2 Mpos = GetScreenToWorld2D(GetMousePosition(),camera);
                b.flagPlace(Mpos.x/(screenWidth/nX),Mpos.y/(screenHeight/nY));
            }
        }
        
        if (IsKeyPressed(KEY_R))
        {
            camera.zoom = 1.0f;
            camera.rotation = 0.0f;
        }



        BeginDrawing(); 

        ClearBackground(RAYWHITE);
        BeginMode2D(camera);  
        b.show();
        EndMode2D();


        EndDrawing();
    
    }

   
    CloseWindow();     
  

    return 0;
}