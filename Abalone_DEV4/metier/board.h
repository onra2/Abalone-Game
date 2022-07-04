/*!
 * \file board.h
 *
 * \brief board class definition
 *
 */
#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <array>
#include "config.h"
#include "marble.h"
#include "position.h"
#include "score.h"
#include "direction.h"
#include "iObservable.h"
#include <list>
#include <tuple>
#include <string>

/*!
 * \brief This class contains Marbles position, the scores players and function to move the Marbles
 */
class Board : public iObservable {
  private:
    /*!
     * \brief Size of the board.
    */
    const int SIZE;

    /*!
     * \brief The initial positions of all marbles on the board
     */
    const std::array<std::tuple<Position, int>, 28> initalPosition = {
        std::make_tuple(Position(0, 4), 1),
        std::make_tuple(Position(0, 5), 1),
        std::make_tuple(Position(0, 6), 1),
        std::make_tuple(Position(0, 7), 1),
        std::make_tuple(Position(0, 8), 1),
        std::make_tuple(Position(1, 3), 1),
        std::make_tuple(Position(1, 4), 1),
        std::make_tuple(Position(1, 5), 1),
        std::make_tuple(Position(1, 6), 1),
        std::make_tuple(Position(1, 7), 1),
        std::make_tuple(Position(1, 8), 1),
        std::make_tuple(Position(2, 4), 1),
        std::make_tuple(Position(2, 5), 1),
        std::make_tuple(Position(2, 6), 1),

        std::make_tuple(Position(6, 2), 2),
        std::make_tuple(Position(6, 3), 2),
        std::make_tuple(Position(6, 4), 2),
        std::make_tuple(Position(7, 0), 2),
        std::make_tuple(Position(7, 1), 2),
        std::make_tuple(Position(7, 2), 2),
        std::make_tuple(Position(7, 3), 2),
        std::make_tuple(Position(7, 4), 2),
        std::make_tuple(Position(7, 5), 2),
        std::make_tuple(Position(8, 0), 2),
        std::make_tuple(Position(8, 1), 2),
        std::make_tuple(Position(8, 2), 2),
        std::make_tuple(Position(8, 3), 2),
        std::make_tuple(Position(8, 4), 2)
    };

    /*!
     * \brief A multidimensional array that contains the player number position instead of marbels
     */
    std::array<std::array<int, BoardSize>, BoardSize> * playersBoard;

    /*!
     * \brief The players scores
    */
    Score score;

    /*!
     * \brief Checks if a coord is in bounds
     *
     * Returns true if the coord is inside the array and inside the board
     *
     * \param coord the coord that needs checking
     *
    */
    bool isInBounds(Position coord);

    /*!
     * \brief The observers list
     */
    std::list<iObserver *> observers;

    /*!
     * \brief changes who's turn it is
     */
    void nextPlayer();

  protected:
    /*!
     * \brief The marbles Array of the board
    */
    std::vector<std::vector<Marble *>> grid;

    /*!
     * \brief Initalize a new board
    */
    void init();

    /*!
     * \brief Id of the current player who's turn it is.
    */
    int currentPlayer;

    /*!
     * \brief The amount of players that play the game
    */
    int playersAmount;

    /*!
     * \brief Checks if a move is legal for a marbel
     *
     * Check if the selected marbel can move on the direction before the real move
     *
     * \param coordinate the marbel point to check
     * \param direction the direction to move on the grid
     *
    */
    bool isMovable(Position coord, eDirection direction);

    /*!
     * \brief Checks if a move is legal for a marbels group
     *
     * Check if the marbels group can move on the direction before the real move
     *
     * \param firstCoordinate the first marbel point in the group to check the move
     * \param lastCoordinate the last marbel point in the group to check the move
     * \param direction the direction to move on the grid
     *
    */
    bool isMovable(std::vector<Position> groupCoord,
                   eDirection direction);

    /*!
     * \brief Returns an array of marble color
     *
     * transform the Marbels grid in a 2D array of ANSI color for the console view
     *
    */
    std::array<std::array<int, BoardSize>, BoardSize> * getPlayersBoard();

    /*!
     * \brief Moves a marble selected by a point to another point
     *
     * \param coordinate the marbel point to move
     * \param direction the direction to move on the grid
     *
    */
    void move(Position coord, eDirection direction);

    /*!
     * \brief Moves a group of marbles selected by two point to another point
     *
     * \param firstCoordinate the first marbel point in the group to move
     * \param lastCoordinate the last marbel point in the group to move
     * \param direction the direction to move on the grid
     *
    */
    void move(Position firstCoordinate, Position lastCoordinate,
              eDirection direction);

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
    int getScorePlayer(int player);

    /*!
     * \brief Returns the player with the highscore
    */
    int * getPlayerHighestScore();
  public:
    /*!
     * \brief constructor
     *
     * Initialize the grid with the constant SIZE and the score for each player
     *
    */
    Board();

    /*!
    * \brief Deconstructor of the Board, used to deallocate all marmbles.
    */
    ~Board();

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

#endif // BOARD_H
