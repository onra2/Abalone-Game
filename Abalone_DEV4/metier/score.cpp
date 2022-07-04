#include "score.h"
#include <algorithm>
#include <vector>
#include <iterator>
#include "iObserver.h"

Score::Score(){
    this->score.fill(0);
}

int Score::getScore(int player){
    --player;
    return this->score.at(player);
}

void Score::addPoint(int player){
    --player;
    this->score.at(player) += 1;
    this->notify("Score", &this->score);
}

int * Score::getPlayerHighestScore(){
    auto resultRaw = std::max_element(this->score.begin(),this->score.end());
    int * result = (int*)malloc(sizeof(int));
    *result = std::distance(this->score.begin(), resultRaw) + 1;
    return result;
}

void Score::addObserver(iObserver * observer){
    observers.push_back(observer);
}

void Score::removeObserver(iObserver * observer){
    observers.remove(observer);
}

void Score::notify(std::string name, void * object){
    for(iObserver * o : observers){
        o->update(name, object);
    }
}
