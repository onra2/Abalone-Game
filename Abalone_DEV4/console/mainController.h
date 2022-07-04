#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include "game.h"
#include "textview.h"

/*!
 * \brief Object for main controller
 */
class MainController
{
private:
    /*!
     * \brief Object for the whole game logic
     */
    Game * game;
    /*!
     * \brief Object for the whole console logic
     */
    TextView * textView;

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
