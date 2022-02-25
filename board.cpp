#include "board.h"

Board::Board(){
    //Non parameters inicialitzation => 20<-x, 20<-y

    int rows = 20; int cols = 20;
    (*this).mX = mX;
    (*this).mY = mY;
    startTouch = true;
    alive = true;
    won = false;

    nFound = 0;
    ValueMat = new int*[rows];
    ShowedMat = new bool*[rows];
    FlagedMat = new bool*[rows];
    for (int i = 0; i < rows; ++i){
        ValueMat[i] = new int[cols];
        ShowedMat[i] = new bool[cols];
        FlagedMat[i] = new bool[cols];
    }
     vector<pair<int,int>> vect1 = {{1,1},{0,1},{-1,1}, {1,0},{-1,0}, {1,-1},{0,-1},{-1,-1}};
     Surround=vect1;
}


Board::Board(int mX, int mY,int screenX, int screenY, int nMines){

    int rows = mX; int cols = mY;
    (*this).mX = mX;
    (*this).mY = mY;
    (*this).screenX = screenX;
    (*this).screenY = screenY;
    (*this).nMines = nMines;
    startTouch = true;
    alive = true;
    won = false;

    nFound = 0;

    ValueMat = new int*[rows];
    ShowedMat = new bool*[rows];
    FlagedMat = new bool*[rows];
    for (int i = 0; i < rows; ++i){
        ValueMat[i] = new int[cols];
        ShowedMat[i] = new bool[cols];
        FlagedMat[i] = new bool[cols];
        for (int j = 0; j < cols; ++j){
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
                DrawText(to_string(ValueMat[i][j]).c_str(),i * (screenX/mX) + (screenX/mX/2), j* (screenY/mY), (screenX/mX) * 0.75f , BLACK);
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


void Board::discoverPlace(int disX,int disY){

    //Grace 0 start Touch;
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
    cout << nFound<<endl;
    if(nFound == (mX * mY) - nMines){
        won = true;
        cout << "CONGRATULATIONS... YOU WIN"<<endl;
    }
}

void Board::flagPlace(int disX,int disY){
    if(!FlagedMat[disX][disY]){
    FlagedMat[disX][disY] = true;
    }else{
        FlagedMat[disX][disY] = false;
    }
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
