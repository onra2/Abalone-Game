#include "position.h"


Position::Position(int x, int y){
    this->x = x;
    this->y = y;
}

int Position::getX(){
    return this->x;
}

int Position::getY(){
    return this->y;
}
