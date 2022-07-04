#ifndef TEXTVIEW_H
#define TEXTVIEW_H
#include <iostream>
#include <tuple>
#include <string>
#include "config.h"
#include "iObserver.h"
#include "iObservable.h"
#include <list>

class TextView : public iObserver, iObservable
{
private:

    bool isWin32;
    /*!
     * \brief The observers list
     */
    std::list<iObserver *> observers;

    /*!
     * \brief prints the letters on the side for the board
     */
    void printSideBarOpen(int lineIndex);

    /*!
     * \brief prints the numbers on the side of the board
     */
    void printSideBarClosed(int i);

public:
    /*!
     * \brief Constructor
     */
    TextView();

    /*!
     * \brief Displays the board using a multidimensional arrays of player number
     */
    void displayBoard(std::array<std::array<int, BoardSize>, BoardSize> marbles);

    /*!
     * \brief Asks a move and returns a tuple x y ABA-PRO
     */
    void askMove();

    /*!
     * \brief Displays the final Winner
     */
    void displayWinner(int * player);

    /*!
     * \brief Display a generic message
     * \param message the message to display
     */
    void displayMessage(std::string message);

    /*!
     * \brief Displays the players score
     */
    void displayHeader(std::array<int, 2> scores);

    virtual void update(std::string name, void *);

    /*!
     * \brief Add a observer on Board
     * \param observer the observer to add
     */
    virtual void addObserver(iObserver * observer);

    /*!
     * \brief Remove a observer on Board
     * \param observer the observer to remove
     */
    virtual void removeObserver(iObserver * observer);

    /*!
     * \brief Notify all observer
     */
    virtual void notify(std::string name, void * object);
};

#endif // TEXTVIEW_H
