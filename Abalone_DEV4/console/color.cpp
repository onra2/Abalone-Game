#include "color.h"
#include <tuple>

const std::tuple<std::string,char> Color::getColorTuple(int player){
    if(player == 2){
        return Color::ansiColors().white;
    }
    return Color::ansiColors().black;
}

const std::string Color::getANSICode(int player){
    return std::get<0>(Color::getColorTuple(player));
}

char Color::getChar(int player){
    return std::get<1>(Color::getColorTuple(player));
}
