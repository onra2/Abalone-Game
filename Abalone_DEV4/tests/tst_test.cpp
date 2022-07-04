#include <QtTest>
#include "board.h"
#include "game.h"
#define black 1
#define white 2

class test : public QObject, Board
{
    Q_OBJECT

public:
    test();
    void Reinit(std::vector<std::vector<Marble*>> &grid);

private slots:
    void TwoMarbleSideBySideMove();
    void TwoMarblesLeftDiagonalAllMoves();
    void TwoMarblesRightDiagonalAllMoves();
    void ThreeMarblesSideBySideMove();
    void ThreeMarblesLeftDiagonalAllMoves();
    void ThreeMarblesRightDiagonalAllMoves();
    void ALotOfSingleMoves();
    void ALotOfSingleAndMultiMovesBackAndForth();
};

void test::Reinit(std::vector<std::vector<Marble*>> &grid){
    this->currentPlayer = 1;
    grid = {
        { /**/nullptr, /**/nullptr, /**/nullptr, /**/nullptr, new Marble(black), new Marble(black) , new Marble(black), new Marble(black), new Marble(black)},
        { /**/nullptr, /**/nullptr, /**/nullptr, new Marble(black), new Marble(black), new Marble(black) , new Marble(black), new Marble(black), new Marble(black)},
        { /**/nullptr, /**/nullptr, nullptr, nullptr, new Marble(black), new Marble(black) , new Marble(black), nullptr, nullptr},
        { /**/nullptr, nullptr, nullptr, nullptr, nullptr, nullptr , nullptr, nullptr, nullptr},
        { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr , nullptr, nullptr, nullptr},
        { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr , nullptr, nullptr, nullptr/**/},
        { nullptr, nullptr, new Marble(white), new Marble(white), new Marble(white), nullptr, nullptr, nullptr/**/, nullptr/**/},
        { new Marble(white), new Marble(white), new Marble(white), new Marble(white), new Marble(white), new Marble(white) , nullptr/**/, nullptr/**/, nullptr/**/},
        { new Marble(white), new Marble(white), new Marble(white), new Marble(white), new Marble(white), nullptr/**/, nullptr/**/, nullptr/**/, nullptr/**/},
    };
}

test::test()
{

}

void test::TwoMarbleSideBySideMove()
{
    this->Reinit(this->grid);
    this->currentPlayer = 2;//whitemove
    std::vector<Position> groupCoord;
    groupCoord.push_back(Position(6, 3));
    groupCoord.push_back(Position(6, 4));
    QVERIFY(this->isMovable(groupCoord, eDirection::right) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::upRight) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::upLeft) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::left) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomRight) == false);
    groupCoord.clear();
    this->currentPlayer = 1;//blackmove
    groupCoord.push_back(Position(2, 5));
    groupCoord.push_back(Position(2, 6));
    QVERIFY(this->isMovable(groupCoord, eDirection::right) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::upRight) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::upLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::left) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomLeft) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomRight) == true);
    groupCoord.clear();
    this->currentPlayer = 2;//whitemove
    groupCoord.push_back(Position(6, 3));
    groupCoord.push_back(Position(7, 2));
    QVERIFY(this->isMovable(groupCoord, eDirection::right) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::upRight) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::upLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::left) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomRight) == false);
}

void test::TwoMarblesLeftDiagonalAllMoves(){
    this->Reinit(this->grid);
    this->currentPlayer = 2;//whitemove
    std::vector<Position> groupCoord;
    groupCoord.push_back(Position(6, 4));
    groupCoord.push_back(Position(7, 3));
    QVERIFY(this->isMovable(groupCoord, eDirection::right) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::upRight) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::upLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::left) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomRight) == false);

    this->currentPlayer = 1;
    QVERIFY(this->isMovable(Position(8, 0), eDirection::right) == false);
    QVERIFY(this->isMovable(Position(8, 0), eDirection::upRight) == false);
    QVERIFY(this->isMovable(Position(8, 0), eDirection::upLeft) == false);
    QVERIFY(this->isMovable(Position(8, 0), eDirection::left) == false);
    QVERIFY(this->isMovable(Position(8, 0), eDirection::bottomLeft) == false);
    QVERIFY(this->isMovable(Position(8, 0), eDirection::bottomRight) == false);
}

void test::TwoMarblesRightDiagonalAllMoves(){
    this->Reinit(this->grid);
    this->currentPlayer = 2;//whitemove
    std::vector<Position> groupCoord;
    groupCoord.push_back(Position(6, 4));
    groupCoord.push_back(Position(7, 4));
    QVERIFY(this->isMovable(groupCoord, eDirection::right) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::upRight) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::upLeft) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::left) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomRight) == false);
}

void test::ThreeMarblesSideBySideMove(){
    this->Reinit(this->grid);
    this->currentPlayer = 2;//whitemove
    std::vector<Position> groupCoord;
    groupCoord.push_back(Position(6, 2));
    groupCoord.push_back(Position(6, 3));
    groupCoord.push_back(Position(6, 4));
    QVERIFY(this->isMovable(groupCoord, eDirection::right) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::upRight) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::upLeft) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::left) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomRight) == false);
    groupCoord.clear();
    this->currentPlayer = 1;
    groupCoord.push_back(Position(2, 4));
    groupCoord.push_back(Position(2, 5));
    groupCoord.push_back(Position(2, 6));
    QVERIFY(this->isMovable(groupCoord, eDirection::right) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::upRight) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::upLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::left) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomLeft) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomRight) == true);
    groupCoord.clear();
    groupCoord.push_back(Position(1, 4));
    groupCoord.push_back(Position(1, 5));
    groupCoord.push_back(Position(1, 6));
    QVERIFY(this->isMovable(groupCoord, eDirection::right) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::upRight) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::upLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::left) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomRight) == false);
}

void test::ThreeMarblesLeftDiagonalAllMoves(){
    this->Reinit(this->grid);
    this->currentPlayer = 2;//whitemove
    std::vector<Position> groupCoord;
    groupCoord.push_back(Position(6, 4));
    groupCoord.push_back(Position(7, 3));
    groupCoord.push_back(Position(8, 2));
    QVERIFY(this->isMovable(groupCoord, eDirection::right) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::upRight) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::upLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::left) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomRight) == false);
    groupCoord.clear();
    this->currentPlayer = 1;
    groupCoord.push_back(Position(0, 8));
    groupCoord.push_back(Position(1, 7));
    groupCoord.push_back(Position(2, 6));
    QVERIFY(this->isMovable(groupCoord, eDirection::right) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::upRight) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::upLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::left) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomLeft) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomRight) == false);
    groupCoord.clear();
    this->currentPlayer = 2;//whitemove
    groupCoord.push_back(Position(6, 2));
    groupCoord.push_back(Position(7, 1));
    groupCoord.push_back(Position(8, 0));
    QVERIFY(this->isMovable(groupCoord, eDirection::right) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::upRight) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::upLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::left) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomRight) == false);
    groupCoord.clear();
    this->currentPlayer = 1;
    groupCoord.push_back(Position(0, 4));
    groupCoord.push_back(Position(1, 3));
    QVERIFY(this->isMovable(groupCoord, eDirection::right) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::upRight) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::upLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::left) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomLeft) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomRight) == false);
}

void test::ThreeMarblesRightDiagonalAllMoves(){
    this->Reinit(this->grid);
    this->currentPlayer = 2;//whitemove
    std::vector<Position> groupCoord;
    groupCoord.push_back(Position(6, 4));
    groupCoord.push_back(Position(7, 4));
    groupCoord.push_back(Position(8, 4));
    QVERIFY(this->isMovable(groupCoord, eDirection::right) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::upRight) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::upLeft) == true);
    QVERIFY(this->isMovable(groupCoord, eDirection::left) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomRight) == false);
    groupCoord.clear();
    this->currentPlayer = 1;
    groupCoord.push_back(Position(0, 4));
    groupCoord.push_back(Position(1, 4));
    groupCoord.push_back(Position(2, 4));
    QVERIFY(this->isMovable(groupCoord, eDirection::right) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::upRight) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::upLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::left) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomLeft) == false);
    QVERIFY(this->isMovable(groupCoord, eDirection::bottomRight) == true);
}

void test::ALotOfSingleMoves(){
    this->Reinit(this->grid);
    auto pos = Position(1, 6);
    auto dir = eDirection::bottomLeft;
    QVERIFY(this->isMovable(pos, dir) == true);
    this->move(pos, dir);
    pos = Position(4, 3);
    dir = eDirection::bottomRight;
    QVERIFY(this->isMovable(pos, dir) == false);
    this->move(pos, dir);
    pos = Position(8, 0);
    dir = eDirection::upRight;
    QVERIFY(this->isMovable(pos, dir) == true);
    this->move(pos, dir);
    pos = Position(1, 4);
    dir = eDirection::bottomRight;
    QVERIFY(this->isMovable(pos, dir) == true);
    this->move(pos, dir);
    pos = Position(4, 4);
    dir = eDirection::bottomLeft;
    QVERIFY(this->isMovable(pos, dir) == false);
    this->move(pos, dir);
    pos = Position(7, 5);
    dir = eDirection::left;
    QVERIFY(this->isMovable(pos, dir) == false);
    this->move(pos, dir);
    pos = Position(7, 1);
    dir = eDirection::upRight;
    QVERIFY(this->isMovable(pos, dir) == true);
    this->move(pos, dir);
    pos = Position(1, 7);
    dir = eDirection::right;
    QVERIFY(this->isMovable(pos, dir) == true);
    this->move(pos, dir);
    pos = Position(6, 2);
    dir = eDirection::upRight;
    QVERIFY(this->isMovable(pos, dir) == true);
    this->move(pos, dir);
    pos = Position(2, 4);
    dir = eDirection::bottomRight;
    QVERIFY(this->isMovable(pos, dir) == true);
    this->move(pos, dir);
    pos = Position(3, 5);
    dir = eDirection::bottomLeft;
    QVERIFY(this->isMovable(pos, dir) == false);
    this->move(pos, dir);
    pos = Position(6, 4);
    dir = eDirection::right;
    QVERIFY(this->isMovable(pos, dir) == true);
    this->move(pos, dir);
    pos = Position(6, 3);
    dir = eDirection::right;
    QVERIFY(this->isMovable(pos, dir) == false);//can't move same color twice in a row
    this->move(pos, dir);
    pos = Position(1, 3);
    dir = eDirection::bottomLeft;
    QVERIFY(this->isMovable(pos, dir) == true);
    this->move(pos, dir);
}

void test::ALotOfSingleAndMultiMovesBackAndForth(){
    this->Reinit(this->grid);

    auto pos = Position(1, 6);
    auto pos2 = Position(0, 0);
    auto dir = eDirection::bottomLeft;
    QVERIFY(this->isMovable(pos, dir) == true);
    this->move(pos, dir);

/////////////
    std::vector<Position> groupCoord;
    pos = Position(6, 3);
    pos2 = Position(7, 3);
    groupCoord.push_back(pos);
    groupCoord.push_back(pos2);
    dir = eDirection::upLeft;
    QVERIFY(this->isMovable(groupCoord, dir) == true);
    this->move(groupCoord.front(), groupCoord.back(), dir);
    groupCoord.clear();

    this->currentPlayer = 2;
    pos = Position(5, 3);
    pos2 = Position(6, 3);
    groupCoord.push_back(pos);
    groupCoord.push_back(pos2);
    dir = eDirection::bottomRight;
    QVERIFY(this->isMovable(groupCoord, dir) == true);
    this->move(groupCoord.front(), groupCoord.back(), dir);
    groupCoord.clear();

/////////////
    this->currentPlayer = 2;
    pos = Position(6, 3);
    pos2 = Position(7, 3);
    auto pos3 = Position(8, 3);
    groupCoord.push_back(pos);
    groupCoord.push_back(pos2);
    groupCoord.push_back(pos3);
    dir = eDirection::upLeft;
    QVERIFY(this->isMovable(groupCoord, dir) == true);
    this->move(groupCoord.front(), groupCoord.at(2), dir);
    groupCoord.clear();

    this->currentPlayer = 2;
    pos = Position(5, 3);
    pos2 = Position(6, 3);
    pos3 = Position(7, 3);
    groupCoord.push_back(pos);
    groupCoord.push_back(pos2);
    groupCoord.push_back(pos3);
    dir = eDirection::bottomRight;
    QVERIFY(this->isMovable(groupCoord, dir) == true);
    this->move(groupCoord.front(), groupCoord.at(2), dir);
    groupCoord.clear();

/////////////
    this->currentPlayer = 2;
    pos = Position(6, 4);
    pos2 = Position(7, 3);
    pos3 = Position(8, 2);
    groupCoord.push_back(pos);
    groupCoord.push_back(pos2);
    groupCoord.push_back(pos3);
    dir = eDirection::upRight;
    QVERIFY(this->isMovable(groupCoord, dir) == true);
    this->move(groupCoord.front(), groupCoord.at(2), dir);
    groupCoord.clear();

    this->currentPlayer = 2;
    pos = Position(5, 5);
    pos2 = Position(6, 4);
    pos3 = Position(7, 3);
    groupCoord.push_back(pos);
    groupCoord.push_back(pos2);
    groupCoord.push_back(pos3);
    dir = eDirection::bottomLeft;
    QVERIFY(this->isMovable(groupCoord, dir) == true);
    this->move(groupCoord.front(), groupCoord.at(2), dir);
    groupCoord.clear();
/////////////
    this->currentPlayer = 2;
    pos = Position(6, 3);
    pos2 = Position(7, 2);
    groupCoord.push_back(pos);
    groupCoord.push_back(pos2);
    dir = eDirection::upRight;
    QVERIFY(this->isMovable(groupCoord, dir) == true);
    this->move(groupCoord.front(), groupCoord.back(), dir);
    groupCoord.clear();

    this->currentPlayer = 2;
    pos = Position(5, 4);
    pos2 = Position(6, 3);
    groupCoord.push_back(pos);
    groupCoord.push_back(pos2);
    dir = eDirection::bottomLeft;
    QVERIFY(this->isMovable(groupCoord, dir) == true);
    this->move(groupCoord.front(), groupCoord.back(), dir);
    groupCoord.clear();
/////////////

    this->currentPlayer = 2;
    pos = Position(6, 3);
    pos2 = Position(7, 2);
    groupCoord.push_back(pos);
    groupCoord.push_back(pos2);
    dir = eDirection::upRight;
    QVERIFY(this->isMovable(groupCoord, dir) == true);
    this->move(groupCoord.front(), groupCoord.back(), dir);
    groupCoord.clear();

    this->currentPlayer = 2;
    pos = Position(5, 4);
    pos2 = Position(6, 3);
    groupCoord.push_back(pos);
    groupCoord.push_back(pos2);
    this->move(groupCoord.front(), groupCoord.back(), dir);
    groupCoord.clear();

    this->currentPlayer = 2;
    pos = Position(4, 5);
    pos2 = Position(5, 4);
    groupCoord.push_back(pos);
    groupCoord.push_back(pos2);
    dir = eDirection::left;
    QVERIFY(this->isMovable(groupCoord, dir) == true);
    this->move(groupCoord.front(), groupCoord.back(), dir);
    groupCoord.clear();
//////////////
    this->currentPlayer = 2;
    pos = Position(4, 4);
    pos2 = Position(5, 3);
    pos3 = Position(6, 2);
    groupCoord.push_back(pos);
    groupCoord.push_back(pos2);
    groupCoord.push_back(pos3);
    dir = eDirection::right;
    QVERIFY(this->isMovable(groupCoord, dir) == true);
    this->move(groupCoord.front(), groupCoord.back(), dir);
    groupCoord.clear();
//////////////
    pos = Position(0, 8);
    dir = eDirection::bottomLeft;
    QVERIFY(this->isMovable(pos, dir) == true);
    this->move(pos, dir);

    this->currentPlayer = 1;
    pos = Position(1, 7);
    dir = eDirection::bottomLeft;
    QVERIFY(this->isMovable(pos, dir) == true);
    this->move(pos, dir);
//////////////
    this->currentPlayer = 2;
    pos = Position(4, 5);
    pos2 = Position(5, 4);
    pos3 = Position(6, 3);
    groupCoord.push_back(pos);
    groupCoord.push_back(pos2);
    groupCoord.push_back(pos3);
    dir = eDirection::left;
    QVERIFY(this->isMovable(groupCoord, dir) == false);
    this->move(groupCoord.front(), groupCoord.back(), dir);
    groupCoord.clear();
//////////////
    this->currentPlayer = 2;
    pos = Position(4, 5);
    dir = eDirection::bottomLeft;
    QVERIFY(this->isMovable(pos, dir) == true);
    this->move(pos, dir);
//////////////
    this->currentPlayer = 2;
    pos = Position(4, 5);
    pos2 = Position(4, 6);
    groupCoord.push_back(pos);
    groupCoord.push_back(pos2);
    dir = eDirection::upLeft;
    QVERIFY(this->isMovable(groupCoord, dir) == false);
    this->move(groupCoord.front(), groupCoord.back(), dir);
    groupCoord.clear();
}

QTEST_APPLESS_MAIN(test)

//#include "tst_test.moc"
