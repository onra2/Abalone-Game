/*!
 * \file Score.h
 *
 * \brief score class definition
 */
#ifndef SCORE_H
#define SCORE_H

#include <array>
#include "iObservable.h"
#include <list>

/*!
 * \brief Store the players score
 */
class Score : public iObservable
{
private:

    /*!
     * \brief The observers list
     */
    std::list<iObserver *> observers;

public:
    /*!
     * \brief Containing the score of each players
    */
    std::array<int, 2> score = {0, 0};

    /*!
     * \brief Constructor
    */
    Score();

    /*!
     * \brief Returns the current score of a player by number
     *
     * \param player the player number to check
     *
    */
    int getScore(int player);

    /*!
     * \brief add a point to the player by number
     *
     * \param player the player number to check
     *
    */
    void addPoint(int player);

    /*!
     * \brief Returns the player with the highscore
    */
    int * getPlayerHighestScore();

    /*!
     * \brief Add a observer on Score
     * \param observer the observer to add
     */
    virtual void addObserver(iObserver * observer);

    /*!
     * \brief Remove a observer on Score
     * \param observer the observer to remove
     */
    virtual void removeObserver(iObserver * observer);

    /*!
     * \brief Notify all observer
     */
    virtual void notify(std::string name, void * object);
};

#endif // SCORE_H
