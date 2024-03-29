#include "board.h"

Board::Board(){
    //Non parameters inicialitzation => 20<-x, 20<-y

    (*this).mX = 20;
    (*this).mY = 20;
    startTouch = true;
    alive = true;
    won = false;

    nFound = 0;
    nFlags = 0;
    ValueMat = new int*[mX];
    ShowedMat = new bool*[mX];
    FlagedMat = new bool*[mX];
    for (int i = 0; i < mX; ++i){
        ValueMat[i] = new int[mY];
        ShowedMat[i] = new bool[mY];
        FlagedMat[i] = new bool[mY];
    }
     vector<pair<int,int>> vect1 = {{1,1},{0,1},{-1,1}, {1,0},{-1,0}, {1,-1},{0,-1},{-1,-1}};
     Surround=vect1;
}


Board::~Board() {
	//Free each sub-array (row)
	for(int i = 0; i< mX; ++i) {
		delete[] ValueMat[i]; 
		delete[] ShowedMat[i]; 
		delete[] FlagedMat[i]; 		
	}
	delete[] ValueMat; 
	delete[] ShowedMat; 
	delete[] FlagedMat; ;  //Free the array of pointers
}


Board::Board(int mX, int mY,int screenX, int screenY, int nMines){

    (*this).mX = mX;
    (*this).mY = mY;
    (*this).screenX = screenX;
    (*this).screenY = screenY;
    (*this).nMines = nMines;
    startTouch = true;
    alive = true;
    won = false;

    nFound = 0;
    nFlags = 0;

    ValueMat = new int*[mX];
    ShowedMat = new bool*[mX];
    FlagedMat = new bool*[mX];
    for (int i = 0; i < mX; ++i){
        ValueMat[i] = new int[mY];
        ShowedMat[i] = new bool[mY];
        FlagedMat[i] = new bool[mY];
        for (int j = 0; j < mY; ++j){
            ValueMat[i][j] = 0;
            ShowedMat[i][j] = false;
            FlagedMat[i][j] = false;
        }
    }
    vector<pair<int,int>> vect1 = {{1,1},{0,1},{-1,1}, {1,0},{-1,0}, {1,-1},{0,-1},{-1,-1}};
    Surround=vect1;
}

void Board::cleanTables(){
    for (int i = 0; i < mX; ++i){
        for (int j = 0; j < mY; ++j){
            ValueMat[i][j] = 0;
            ShowedMat[i][j] = false;
            FlagedMat[i][j] = false;
        }
    }
}

void Board::show(){
    for (int i = 0; i < mX; i++){
        for(int j = 0; j < mY; j++){

            if(FlagedMat[i][j]){
                DrawRectangle(i * (screenX/mX), j* (screenY/mY),screenX/mX -1 ,screenY/mY -1,GREEN);
            }
            else if(ShowedMat[i][j] && ValueMat[i][j] != -1){
                DrawRectangle(i * (screenX/mX), j* (screenY/mY),screenX/mX -1 ,screenY/mY -1,SKYBLUE);
                if(ValueMat[i][j] != 0){
                    Vector2 sizeT = MeasureTextEx(GetFontDefault(), to_string(ValueMat[i][j]).c_str(), 20, 0);
                    Vector2 sizeC = MeasureTextEx(GetFontDefault(), to_string(ValueMat[i][j]).c_str(), 25, 0);

                    DrawText(to_string(ValueMat[i][j]).c_str(),i * (screenX/mX), j* (screenY/mY), 25 , BLACK);
                    DrawText(to_string(ValueMat[i][j]).c_str(),i * (screenX/mX), j* (screenY/mY), 20 , getColorNumber(ValueMat[i][j]));

                }
            }
            else if(ValueMat[i][j] == -1 && ShowedMat[i][j]){
               DrawRectangle(i * (screenX/mX), j* (screenY/mY), screenX/mX -1 ,screenY/mY - 1,BLACK);
            }
            else{
                DrawRectangle(i * (screenX/mX), j* (screenY/mY),screenX/mX -1 ,screenY/mY -1,WHITE);
            }
        }
    }
 
   
}


void Board::showGUI(){
       //UI:
     DrawText(to_string(nFlags).c_str(),20,0,40,BLACK);  
}

int Board::discoverPlace(int disX,int disY){
    //Grace 0 start Touch;
    if(disX < 0 || disX >= mX || disY < 0 || disY >= mY){
        return 1;
    }
    if(startTouch && ValueMat[disX][disY] == 0 || !startTouch){
        startTouch = false;
        if(!FlagedMat[disX][disY] && !ShowedMat[disX][disY]){
            ShowedMat[disX][disY] = true;
            if(ValueMat[disX][disY] == 0){
                nFound++;
                //TO BE CHANGED OR REORGANIZED
                for(int i = 0; i < 9; i++){    
                Vector2 newPos = {float(disX + Surround[i].first), float(disY+Surround[i].second)};
                if( newPos.x >= 0 && newPos.y >= 0 && newPos.x < mX && newPos.y < mY && ShowedMat[int(newPos.x)][int(newPos.y)] != true)
                    {
                    discoverPlace(int(newPos.x),int(newPos.y));
                    }
                }
                ////

            }else if(ValueMat[disX][disY] == -1){
                ShowedMat[int(disX)][int(disY)] = true;
                alive = false;
            }else{//Any other number
                nFound++;
            }
        }
    }else{
        restart();
        discoverPlace(disX,disY);
    }
    if(nFound == (mX * mY) - nMines){
        won = true;
        cout << "CONGRATULATIONS... YOU WIN"<<endl;
    }

    return 0;
}

int Board::flagPlace(int disX,int disY){
    if(disX < 0 || disX >= mX || disY < 0 || disY >= mY){
        return 1;
    }


    if(!FlagedMat[disX][disY] && !ShowedMat[disX][disY]){
    FlagedMat[disX][disY] = true;
    nFlags++;
    }else if(!ShowedMat[disX][disY]){
        FlagedMat[disX][disY] = false;
        nFlags--;
    }

    return 0;
}


int Board::setNumberBoard(int x, int y){
    
    int MinesArround = 0;
    for(int i = 0; i < 9; i++){
        Vector2 newPos = {float(x + Surround[i].first), float(y+Surround[i].second)};
        if( newPos.x >= 0 && newPos.y >= 0 && newPos.x < mX && newPos.y < mY && ValueMat[int(newPos.x)][int(newPos.y)] == -1 )
        {
            MinesArround ++;
        }
    }
    return MinesArround;
}

void Board::generateMines(){
    int i = 0;

    while (i < nMines){
       int x = GetRandomValue(0, mX-1);
       int y = GetRandomValue(0, mY-1);
       if(ValueMat[x][y]!=-1){
            ValueMat[x][y] = -1;
            i++;
       }
    }
    for (int i = 0; i < mX; i++){
        for(int j = 0; j < mY; j++){
            if(ValueMat[i][j] != -1){
            ValueMat[i][j] = setNumberBoard(i,j);
            }
        }
    }
}

void Board::restart(){
    startTouch = true;
    nFound = 0;

    alive = true;
    won = false;

    cleanTables();
    generateMines();

}

bool Board::isAlive(){
    return alive;

}

bool Board::hasWon(){
    return won;
}


void Board::interactBoard(CameraGame* c){
    if (IsKeyPressed(KEY_R)){
        restart();
    }

	if(isAlive() && !hasWon()){
		Vector2 Mpos = c->getPositionClick();
		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
			discoverPlace(Mpos.x/(screenX/mX),Mpos.y/(screenY/mY));
		}

		if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
			flagPlace(Mpos.x/(screenX/mX),Mpos.y/(screenY/mY));
		}
    }
}

Color Board::getColorNumber(int n){
    switch(n){
    case 1:
        return BLUE;
        break;
    case 2:
        return GREEN;
        break;
    case 3:
        return RED;
        break;
    case 4:
        return PURPLE;
        break;
    case 5:
        return DARKPURPLE;
        break;
    case 6:
        return SKYBLUE;
        break;
    case 7:
        return DARKPURPLE;
        break;
    case 8:
        return BLANK;
        break;
    }

    return BEIGE;
}