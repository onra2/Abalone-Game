#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include "game.h"
#include "mainwindow.h"

class MainController
{
private:
    /*!
     * \brief Object for the whole game logic
     */
    Game * game;
    /*!
     * \brief Object for the whole window logic
     */
    MainWindow * mainWindow;

public:
    /*!
     * \brief A constructor
     */
    MainController();

    /*!
     * \brief Get the color of the player
     *
     *  \param player id
     */
    void start();
};

#endif // MAINCONTROLLER_H
