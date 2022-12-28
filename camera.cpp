#include "camera.h"

CameraGame::CameraGame(){
    cameraU = {0};
    cameraU.offset = (Vector2){0,0 };
    cameraU.zoom = 1.0f;
    cameraU.rotation = 0.0f;
    cameraU.target = (Vector2){0,0};

    zoomCount = 1;

    prevMousePos = GetMousePosition();
}

CameraGame::CameraGame(int screenWidth,int screenHeight): screenWidth(screenWidth),screenHeight(screenHeight){
    cameraU = {0};
    cameraU.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    cameraU.zoom = 1.0f;
    cameraU.rotation = 0.0f;
    cameraU.target = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };

    zoomCount = 1;

	prevMousePos = GetMousePosition();
}

void CameraGame::update(){
	
    Vector2 thisPos = GetMousePosition();

    Vector2 delta = Vector2Subtract(prevMousePos, thisPos);
    prevMousePos = thisPos;

    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
        cameraU.target = GetScreenToWorld2D(Vector2Add(cameraU.offset, delta),cameraU);


    //ZOOM:
	if(zoomCount > 1 && (IsKeyPressed(KEY_Q) || GetMouseWheelMove() < 0)){
        Vector2 zoomWhere = GetScreenToWorld2D((Vector2){ screenWidth/2.0f, screenHeight/2.0f },cameraU);
        cameraU.zoom = cameraU.zoom - 0.5f;
        zoomCount =zoomCount - 0.5f; 
        cameraU.target = zoomWhere;
    }
    else if(zoomCount < 10 && (IsKeyPressed(KEY_E) || GetMouseWheelMove() > 0)){
        Vector2 zoomWhere = GetScreenToWorld2D((Vector2){ screenWidth/2.0f, screenHeight/2.0f },cameraU);
        cameraU.zoom = cameraU.zoom + 0.5f;
        cameraU.target = zoomWhere;
        zoomCount = zoomCount + 0.5f; 
    }

    //Moving:
    if (IsKeyDown(KEY_W)){
       cameraU.offset.y = cameraU.offset.y + 5;
    }else if (IsKeyDown(KEY_S)){
        cameraU.offset.y = cameraU.offset.y - 5;
    }
    if (IsKeyDown(KEY_D)){
        cameraU.offset.x = cameraU.offset.x - 5;
    }else if (IsKeyDown(KEY_A)){
        cameraU.offset.x = cameraU.offset.x + 5;
    }
		
	        
    if (IsKeyPressed(KEY_R))
    {
        cameraU.zoom = 1.0f;
        cameraU.rotation = 0.0f;
    }
}

Vector2 CameraGame::getPositionClick(){
	return GetScreenToWorld2D(GetMousePosition(),cameraU);
}

Camera2D CameraGame::getcamera(){
    return cameraU;
}

Vector2 CameraGame::Vector2Add(Vector2 a, Vector2 b){
    return (Vector2){a.x+b.x, a.y+b.y};
}
Vector2 CameraGame::Vector2Subtract(Vector2 a, Vector2 b){
    return (Vector2){a.x-b.x, a.y-b.y};
}