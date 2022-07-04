#include "direction.h"
#include <string>

const struct Direction::delta Direction::getDelta(eDirection eDir){
    return deltaValues[eDir];
}

eDirection Direction::fromString(std::array<std::string, 3> directionString)
{
    try {
        short x1 = chartToShort(directionString.at(0).at(0));
        short y1 = std::stoi(directionString.at(0).substr(1,1),nullptr) - 1;
        short x2, y2;

        if(directionString.at(2).empty()){
            x2 = chartToShort(directionString.at(1).at(0));
            y2 = std::stoi(directionString.at(1).substr(1,1),nullptr) - 1;
        }else{
            x2 = chartToShort(directionString.at(2).at(0));
            y2 = std::stoi(directionString.at(2).substr(1,1),nullptr) - 1;
        }

        const short deltaX (x2-x1);
        const short deltaY (y2-y1);

        //
        size_t index = 0;
        while(index < deltaValues.size()){
            if(deltaValues.at(index).x == deltaX &&
                    deltaValues.at(index).y == deltaY){
                return static_cast<eDirection>(index);
            }
            ++index;
        }

    }  catch (std::exception * e) {
        throw new std::invalid_argument("invalid coordinate");
    }

    throw new std::invalid_argument("invalid coordinate");
}

short Direction::chartToShort(char c){

    short index = 0;

    while(index < static_cast<short>(charsCoord.size())){
        if(charsCoord.at(index) == c){
            return index;
        }
        ++index;
    }

    throw new std::invalid_argument("this char is not a valid coordinate: " + std::string(1,c));

}
