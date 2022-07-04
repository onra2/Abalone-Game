/*!
 * \file marble.h
 *
 * \brief marble class definition
 *
 */
#ifndef MARBLE_H
#define MARBLE_H

/*!
 * \brief The marble class contains the color and the status of a marble
 */
class Marble
{
private:
    /*!
     * \brief The color of the marble
    */
    int myPlayer;

public:


    /*!
     * \brief Constructor
     *
     * \param player the owner player number
    */
    Marble(int player);

    /*!
     * \brief get the owner player number
     * \return
     */
    int getPlayer();
};

#endif // MARBLE_H
