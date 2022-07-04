#include "game.h"
#include <iomanip>
#include <exception>
#include <array>
#include <string>

Game::Game() : Board()
{ }

void Game::start() {
    this->init();
}

Game::~Game() {

}

void Game::playTurn(std::array<std::string, 3> * playerMove){
    try {
        short x1 = Direction::chartToShort(playerMove->at(0).at(0));
        short y1 = std::stoi(playerMove->at(0).substr(1,1),nullptr) - 1;

        short x2 = Direction::chartToShort(playerMove->at(1).at(0));
        short y2 = std::stoi(playerMove->at(1).substr(1,1),nullptr) - 1;

        auto dirToGo = Direction::fromString(*playerMove);

        if(playerMove->at(2).empty()){
            this->MoveMarbles(x1, y1, dirToGo);
        } else {
            // mandatory for the move
            if(x1>x2){
                short tempx = x2;
                short tempy = y2;
                x2 = x1;
                y2 = y1;
                x1 = tempx;
                y1 = tempy;
            }
            this->MoveMarbles(x1, y1, x2, y2, dirToGo);
        }

    }  catch (std::exception * e) {
        this->notify("error",e);
    }

    delete playerMove;
}

void Game::MoveMarbles(int x, int y, eDirection direction) {
    this->move(Position(x, y), direction);
}

void Game::MoveMarbles(int x1, int y1, int x2, int y2,
                       eDirection dir) {
    this->move(Position(x1, y1), Position(x2, y2), dir);
}

bool Game::isWon() {
    return this->Board::isWon();
}

std::array<std::array<int, BoardSize>, BoardSize> * Game::getPlayersBoard() {
    return this->Board::getPlayersBoard();
}

int Game::getScore(int player) {
    return this->getScorePlayer(player);
}

int * Game::getPlayerHighestScore() {
    return this->Board::getPlayerHighestScore();
}

void Game::addObserver(iObserver * observer) {
    Game::Board::addObserver(observer);
}

void Game::removeObserver(iObserver * observer) {
    Game::Board::removeObserver(observer);
}

void Game::update(std::string name, void * object){
    if(name == "ABAPROMove"){
        this->playTurn(static_cast<std::array<std::string, 3> *>(object));
    }else{
        throw new std::exception();
    }

}
