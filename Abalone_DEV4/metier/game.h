/*!
 * \file game.h
 *
 * \brief game facede class definition
 */
#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "score.h"
#include "direction.h"
#include "iObserver.h"

/*!
 * \brief The game class is the Facade to accede the publics function of the Board class
 */
class Game : Board, public iObserver
{

public:
    /*!
     * \brief Constructor
     *
     * Initalize a new board for the first time and init the game
     *
    */
    Game();

    /*!
     * \brief Deconstructor
     */
    ~Game();

    /*!
     * \brief Start the game
    */
    void start();

    /*!
     * \brief Returns an array of marble color
     *
     * transform the Marbels grid in a 2D array of ANSI color for the console view
     *
    */
    std::array<std::array<int, BoardSize>, BoardSize> * getPlayersBoard();

    /*!
     * \brief plays the turn
     *
     *  \param playerMove the move the player chose to perform
     */
    void playTurn(std::array<std::string, 3> * playerMove);

    /*!
     * \brief Moves a marble selected by a point to another point
     *
     * \param x the x marbel coordinate to move
     * \param y the y marbel coordinate to move
     * \param direction the direction to move on the grid
     *
    */
    void MoveMarbles(int x, int y, eDirection direction);

    /*!
     * \brief Moves a group of marbles selected by two point to another point
     *
     * \param x1 the first x marbel coordinate to move
     * \param y1 the first y marbel coordinate to move
     * \param x2 the last x marbel coordinate to move
     * \param y2 the last y marbel coordinate to move
     * \param direction the direction to move on the grid
     *
    */
    //void MoveMarbles(int x1, int y1, int x2, int y2, std::string direction);
    void MoveMarbles(int x1, int y1, int x2, int y2, eDirection dir);

    /*!
     * \brief Checks if a player has won
    */
    bool isWon();

    /*!
     * \brief Returns the current score of a player by ID
     *
     * \param player the player id to check
     *
    */
    int getScore(int player);

    /*!
     * \brief Returns the player with the highestscore
    */
    int * getPlayerHighestScore();

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
     * \brief Updates the observers
     * \param name which option should the update perform
     * \param Anything related to the name option
     */
    virtual void update(std::string name, void *);
};

#endif // GAME_H
