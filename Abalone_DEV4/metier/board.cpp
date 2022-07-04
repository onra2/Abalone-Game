#include "board.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include "iObserver.h"
#include <string>

Board::Board() :
    SIZE {BoardSize},
    score {Score()},
    currentPlayer (1),
    playersAmount (2) {
    this->playersBoard = new
    std::array<std::array<int, BoardSize>, BoardSize>;
}

Board::~Board() {
    for ( int i = 0; i < this->SIZE; i++ ) {
        for ( int j = 0; j < this->SIZE; j++ ) {
            if (this->grid.at(i).at(j) != nullptr) {
                delete this->grid.at(i).at(j);
            }
        }
    }
}

void Board::init() {

    this->grid = std::vector<std::vector<Marble *>>(this->SIZE);

    std::fill(this->grid.begin(), this->grid.end(),
              std::vector<Marble *>(this->SIZE));
    for (int i(0); i < this->SIZE; ++i) {
        std::fill(this->grid.at(i).begin(), this->grid.at(i).end(), nullptr);
    }

    int x, y;
    int player;
    for (std::tuple<Position, int> pc : initalPosition) {
        x = std::get<0>(pc).getX();
        y = std::get<0>(pc).getY();
        player = std::get<1>(pc);
        this->grid.at(x).at(y) = new Marble(player);
    }

    this->notify("currentPlayer", &currentPlayer);
    this->notify("Board", getPlayersBoard());

}

void Board::nextPlayer() {
    this->currentPlayer = ((this->currentPlayer + 1) >
                           this->playersAmount) ? 1 : this->currentPlayer + 1;
    this->notify("currentPlayer", &currentPlayer);
}

std::array<std::array<int, BoardSize>, BoardSize> *
Board::getPlayersBoard() {
    for ( int i = 0; i < this->SIZE; i++ ) {
        for ( int j = 0; j < this->SIZE; j++ ) {
            if (this->grid.at(i).at(j) != nullptr) {
                playersBoard->at(i).at(j) = this->grid.at(i).at(j)->getPlayer();
            }
            else {
                playersBoard->at(i).at(j) = -1;
            }
        }
    }
    return playersBoard;
}

bool Board::isInBounds(Position coord) {
    if (coord.getX() >= BoardSize || coord.getY() >= BoardSize) {
        return false;
    }
    int shift = 4;
    int lowerShift = 0;
    int toCheckX = coord.getX();
    int toCheckY = coord.getY();
    for ( int i = 0; i < BoardSize; i++ ) {
        int p = 0;
        for ( int j = 0; j < BoardSize; j++ ) {
            bool toCheck = i == toCheckX && j == toCheckY;
            if (lowerShift > 0 && (j + lowerShift) == BoardSize + p) {
                ++p;
                //invalide
                //important de mettre ici le if pour ++p
                if (toCheck) {
                    return false;
                }
            }
            else if (j < shift && toCheck) {
                //invalide
                return false;
            }
            else if (toCheck) {
                //valide
                return true;
            }
        }
        shift--;
        if (shift < 0) {
            lowerShift++;
        }
    }

    return false;
}

bool Board::isMovable(Position coord, eDirection direction) {
    if (!this->isInBounds(coord) ||
            //the coord has to be in bounds to be able to move
            this->grid.at(coord.getX()).at(coord.getY()) == nullptr ||
            //there has to be a marble to move
            this->grid.at(coord.getX()).at(coord.getY())->getPlayer() !=
            this->currentPlayer) { //player can only move his color
        return false;
    }

    //checks if the player only moves max 3 marbles of his and doesnt move more ennemy marbles
    auto delta = Direction::getDelta(direction);
    int myOwnMarbles = 0;//conteur de mes marble encontré
    int EnemyMarbles = 0;
    bool EnemySandwichedBetweenMyMarbles = false;

    int prochainX = coord.getX();
    int prochainY = coord.getY();
    auto prochain = this->grid.at(prochainX).at(prochainY);
    bool continu = true;

    while (prochain != nullptr && continu) {
        if (this->grid.at(prochainX).at(prochainY)->getPlayer() ==
                this->currentPlayer) {
            myOwnMarbles++;
            if (EnemyMarbles > 0) {
                EnemySandwichedBetweenMyMarbles = true;
            }
        }
        else {
            EnemyMarbles++;
        }
        prochainX += delta.x;
        prochainY += delta.y;
        if (prochainY > BoardSize || prochainX > BoardSize ||
                !this->isInBounds(Position(prochainX, prochainY))) {
            continu = false;
        }
        else {
            prochain = this->grid.at(prochainX).at(prochainY);
        }
    }

    if (myOwnMarbles > 3 || myOwnMarbles <= EnemyMarbles ||
            EnemySandwichedBetweenMyMarbles) {
        return false;
    }

    return true;
}

bool Board::isMovable(std::vector<Position> groupCoord,
                      eDirection direction) {
    if (groupCoord.empty()) {
        return false;
    }

    auto delta = Direction::getDelta(direction);
    int marbleCount = groupCoord.size();

    bool descendDroit = false;
    bool descendGauche = false;
    bool groupOnSameLign = false;
    int x1 = 0;
    int y1 = 0;
    int lastx = 0;
    int lasty = 0;

    if (marbleCount == 2) {
        descendDroit = groupCoord.at(0).getY() == groupCoord.at(1).getY();
        descendGauche = groupCoord.at(0).getY() == groupCoord.at(1).getY() + 1;
        groupOnSameLign = groupCoord.at(0).getX() == groupCoord.at(1).getX() && groupCoord.at(0).getY() < groupCoord.at(1).getY();

        x1 = groupCoord.at(0).getX();
        lastx = groupCoord.at(1).getX();
        y1 = groupCoord.at(0).getY();
        lasty = groupCoord.at(1).getY();
    }
    if (marbleCount == 3) {
        descendDroit = groupCoord.at(0).getY() == groupCoord.at(2).getY();
        descendGauche = groupCoord.at(0).getY() == groupCoord.at(2).getY() + 2;
        groupOnSameLign = groupCoord.at(0).getX() == groupCoord.at(2).getX() && groupCoord.at(0).getY() < groupCoord.at(2).getY();

        x1 = groupCoord.at(0).getX();
        lastx = groupCoord.at(2).getX();
        y1 = groupCoord.at(0).getY();
        lasty = groupCoord.at(2).getY();
    }
    bool result = std::all_of(groupCoord.begin(),
    groupCoord.end(), [ = ](Position coord) {
        if (!this->isInBounds(coord) ||
                coord.getX() + delta.x >= BoardSize ||
                coord.getY() + delta.y >= BoardSize ||
                this->grid.at(coord.getX()).at(coord.getY()) == nullptr ||
                this->grid.at(coord.getX()).at(coord.getY())->getPlayer() !=
                this->currentPlayer) {
            return false;
        }

        if (descendDroit) {
            if (direction == eDirection::upLeft) {
                if (!this->isInBounds(Position(x1 + delta.x, y1 + delta.y)) ||
                        this->grid.at(x1 + delta.x).at(y1 + delta.y) != nullptr) {
                    return false;
                }
                return true;
            }
            if (direction == eDirection::bottomRight) {
                if (!this->isInBounds(Position(lastx + delta.x, lasty + delta.y)) ||
                        this->grid.at(lastx + delta.x).at(lasty + delta.y) != nullptr) {
                    return false;
                }
                return true;
            }
            if (!this->isInBounds(Position(coord.getX() + delta.x,
                                           coord.getY() + delta.y)) ||
                    this->grid.at(coord.getX() + delta.x).at(coord.getY() + delta.y) !=
                    nullptr) {
                return false;
            }
            return true;
        }
        if (descendGauche) {
            if (direction == eDirection::upRight) {
                if (!this->isInBounds(Position(x1 + delta.x, y1 + delta.y)) ||
                        this->grid.at(x1 + delta.x).at(y1 + delta.y) != nullptr) {
                    return false;
                }
                return true;
            }
            if (direction == eDirection::bottomLeft) {
                if (!this->isInBounds(Position(lastx + delta.x, lasty + delta.y)) ||
                        this->grid.at(lastx + delta.x).at(lasty + delta.y) != nullptr) {
                    return false;
                }
                return true;
            }
            if (!this->isInBounds(Position(coord.getX() + delta.x,
                                           coord.getY() + delta.y)) ||
                    this->grid.at(coord.getX() + delta.x).at(coord.getY() + delta.y) !=
                    nullptr) {
                return false;
            }
            return true;
        }
        if (groupOnSameLign) {
            if (direction == eDirection::right) {
                if (!this->isInBounds(Position(lastx + delta.x, lasty + delta.y)) ||
                        this->grid.at(lastx + delta.x).at(lasty + delta.y) != nullptr) {
                    return false;
                }
                return true;
            }
            if (direction == eDirection::left) {
                if (!this->isInBounds(Position(x1 + delta.x, y1 + delta.y)) ||
                        this->grid.at(x1 + delta.x).at(y1 + delta.y) != nullptr) {
                    return false;
                }
                return true;
            }
            if (!this->isInBounds(Position(coord.getX() + delta.x,
                                           coord.getY() + delta.y)) ||
                    this->grid.at(coord.getX() + delta.x).at(coord.getY() + delta.y) !=
                    nullptr) {
                return false;
            }
            return true;
        }
        if (!this->isInBounds(Position(coord.getX() + delta.x,
                                       coord.getY() + delta.y)) ||
                this->grid.at(coord.getX() + delta.x).at(coord.getY() + delta.y) !=
                nullptr) {
            return false;
        }
        return true;
    });
    return result;
}

void Board::move(Position coord, const eDirection direction) {
    if (this->isMovable(coord, direction)) {
        auto delta = Direction::getDelta(direction);
        if (coord.getX() + delta.x <= BoardSize &&
                coord.getY() + delta.y <= BoardSize) {
            std::vector<std::tuple<Marble *, Position>> MarblesInDaWay;

            int prochainX = coord.getX();
            int prochainY = coord.getY();
            auto prochain = this->grid.at(prochainX).at(prochainY);
            bool continu = true;

            //puts all encountered marbles in a list
            while (prochain != nullptr && continu) {
                MarblesInDaWay.push_back(std::make_tuple(prochain, Position(prochainX,
                                         prochainY)));
                prochainX += delta.x;
                prochainY += delta.y;
                if (prochainY > BoardSize || prochainX > BoardSize ||
                        !this->isInBounds(Position(prochainX, prochainY))) {
                    continu = false;
                }
                else {
                    prochain = this->grid.at(prochainX).at(prochainY);
                }
            }

            //for each marble, move it (start with the last one in the list to not overwrite other marbles)
            std::for_each(MarblesInDaWay.rbegin(),
            MarblesInDaWay.rend(), [ = ](std::tuple<Marble *, Position> info) {
                Marble * newMarble = std::get<0>(info);
                Position posOfMarbleToMove = std::get<1>(info);
                //If not isInBounds: setFallen and put at nullptr, moving is unnessesary since its fallen and doesnt exist anymore
                if (this->isInBounds(Position(posOfMarbleToMove.getX() + delta.x, posOfMarbleToMove.getY() + delta.y))) {
                    this->grid.at(posOfMarbleToMove.getX()).at(posOfMarbleToMove.getY()) = nullptr;//remove marble from current tile
                    this->grid.at(posOfMarbleToMove.getX() + delta.x).at(posOfMarbleToMove.getY() + delta.y) = newMarble;//move the marble to the new tile
                }
                else {
                    if (this->grid.at(posOfMarbleToMove.getX()).at(posOfMarbleToMove.getY())->getPlayer() != currentPlayer) {
                        this->score.addPoint(currentPlayer);
                    }
                    this->grid.at(posOfMarbleToMove.getX()).at(posOfMarbleToMove.getY()) = nullptr;
                }
            });
            this->nextPlayer();
        }
    }

    this->notify("Board", getPlayersBoard());
    if (this->isWon()) {
        this->notify("displayWinner", this->getPlayerHighestScore());
    }
}

void Board::move(Position firstCoordinate, Position lastCoordinate, eDirection direction) {
    std::vector<Position> groupCoord;
    bool groupOnSameLign = firstCoordinate.getX() == lastCoordinate.getX()
                           && firstCoordinate.getY() < lastCoordinate.getY();
    bool descendDroit = false, descendGauche = false;
    if (groupOnSameLign) {
        int diff = (lastCoordinate.getY() + 1) - (firstCoordinate.getY() + 1);
        if (diff == 1) {
            //groupe de 2 billes
            groupCoord.push_back(firstCoordinate);
            groupCoord.push_back(lastCoordinate);
            descendDroit = firstCoordinate.getY() == lastCoordinate.getY();
            descendGauche = firstCoordinate.getY() == lastCoordinate.getY() + 1;
        }
        else if (diff == 2) {
            //groupe de 3 billes
            groupCoord.push_back(firstCoordinate);
            groupCoord.push_back(Position(firstCoordinate.getX(),
                                          firstCoordinate.getY() + 1));
            groupCoord.push_back(lastCoordinate);
            descendDroit = firstCoordinate.getY() == lastCoordinate.getY();
            descendGauche = firstCoordinate.getY() == lastCoordinate.getY() + 2;
        }
    }
    else {
        int diff = (lastCoordinate.getX() + 1) - (firstCoordinate.getX() + 1);
        if (diff == 1 && firstCoordinate.getY() >= lastCoordinate.getY()) {
            //groupe de 2 billes
            groupCoord.push_back(firstCoordinate);
            groupCoord.push_back(lastCoordinate);
            descendDroit = firstCoordinate.getY() == lastCoordinate.getY();
            descendGauche = firstCoordinate.getY() == lastCoordinate.getY() + 1;
        }
        else if (diff == 2) {
            //groupe de 3 billes
            descendDroit = firstCoordinate.getY() == lastCoordinate.getY();
            descendGauche = firstCoordinate.getY() == lastCoordinate.getY() + 2;
            if (descendDroit) {
                groupCoord.push_back(firstCoordinate);
                groupCoord.push_back(Position(firstCoordinate.getX() + 1,
                                              firstCoordinate.getY()));
                groupCoord.push_back(lastCoordinate);
            }
            else if (descendGauche) {
                groupCoord.push_back(firstCoordinate);
                groupCoord.push_back(Position(firstCoordinate.getX() + 1,
                                              firstCoordinate.getY() - 1));
                groupCoord.push_back(lastCoordinate);
            }
        }
    }

    if (this->isMovable(groupCoord, direction)) {
        bool reverse = false;

        auto delta = Direction::getDelta(direction);
        if (descendDroit) {
            if (direction == eDirection::upLeft) {
                reverse = false;
            }
            else if (direction == eDirection::bottomRight) {
                reverse = true;
            }
            else {
                reverse = false;
            }
        }
        if (descendGauche) {
            if (direction == eDirection::upRight) {
                reverse = false;
            }
            else if (direction == eDirection::bottomLeft) {
                reverse = true;
            }
            else {
                reverse = false;
            }
        }
        if (groupOnSameLign) {
            if (direction == eDirection::right) {
                reverse = true;
            }
            else if (direction == eDirection::left) {
                reverse = false;
            }
            else {
                reverse = false;
            }
        }

        if (!reverse) {
            std::for_each(groupCoord.begin(),
            groupCoord.end(), [ = ](Position coord) {
                if (this->isInBounds(Position(coord.getX() + delta.x,
                                              coord.getY() + delta.y))) {
                    auto newMarble = this->grid.at(coord.getX()).at(coord.getY());
                    this->grid.at(coord.getX()).at(coord.getY()) =
                        nullptr;//remove marble from current tile
                    this->grid.at(coord.getX() + delta.x).at(coord.getY() + delta.y) =
                        newMarble;//move the marble to the new tile
                }
                else {
                    if (this->grid.at(coord.getX()).at(coord.getY())->getPlayer() !=
                            currentPlayer) {
                        this->score.addPoint(currentPlayer);
                    }

                    this->grid.at(coord.getX()).at(coord.getY()) = nullptr;
                }
            });
        }
        else {
            std::for_each(groupCoord.rbegin(),
            groupCoord.rend(), [ = ](Position coord) {
                if (this->isInBounds(Position(coord.getX() + delta.x,
                                              coord.getY() + delta.y))) {
                    auto newMarble = this->grid[coord.getX()][coord.getY()];
                    this->grid.at(coord.getX()).at(coord.getY()) =
                        nullptr;//remove marble from current tile
                    this->grid.at(coord.getX() + delta.x).at(coord.getY() + delta.y) =
                        newMarble;//move the marble to the new tile
                }
                else {
                    if (this->grid.at(coord.getX()).at(coord.getY())->getPlayer() !=
                            currentPlayer) {
                        this->score.addPoint(currentPlayer);
                    }
                    this->grid.at(coord.getX()).at(coord.getY()) = nullptr;
                }
            });
        }
        this->nextPlayer();
    }

    this->notify("Board", getPlayersBoard());
    if (this->isWon()) {
        this->notify("displayWinner", this->getPlayerHighestScore());
    }
}

bool Board::isWon() {
    auto highestPlayer = this->score.getPlayerHighestScore();
    auto scoreHighestPlayer = this->score.getScore(*highestPlayer);
    return scoreHighestPlayer >= 6;
}

int Board::getScorePlayer(const int player) {
    return this->score.getScore(player);
}

int * Board::getPlayerHighestScore() {
    return this->score.getPlayerHighestScore();
}

void Board::addObserver(iObserver * observer) {
    observers.push_back(observer);
    this->score.addObserver(observer);
}

void Board::removeObserver(iObserver * observer) {
    observers.remove(observer);
    this->score.removeObserver(observer);
}

void Board::notify(std::string name, void * object) {
    for (iObserver * o : observers) {
        o->update(name, object);
    }
}
