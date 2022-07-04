/*!
 * \file Direction.h
 *
 * \brief direction enum definition
 */
#ifndef DIRECTION_H
#define DIRECTION_H
#include <array>

/*!
 * \brief the direction for the Marbles move
*/
enum eDirection{
    upLeft, upRight, left, right, bottomLeft, bottomRight
};

class Direction
{
private:

    /*!
     * \brief An array to easily convert letters in x coord
     */
    constexpr static std::array<char,9> charsCoord {'I','H','G','F','E','D','C','B','A'};

public:
    /*!
     * \brief The delta x and y struct for the eDirection
     */
    struct delta{
        const short x;
        const short y;
    };

    /*!
      * \brief containe the delta values for each eDirection
    */
    constexpr static std::array<const struct delta,6> deltaValues = {
        delta{-1, 0}, //upLeft
        delta{-1,1}, //upRight
        delta{0,-1}, //left
        delta{0,1}, //right
        delta{1,-1}, //bottomLeft
        delta{1,0} //bottomRight
    };

    /*!
     * \brief return the delta from the selected eDirection
     * \param the selected eDirection
     * \return the delta from the eDirection
     */
    const static struct delta getDelta(eDirection eDir);

    /*!
     * \brief converts the user entry strings into a Direction
    */
    static eDirection fromString(std::array<std::string, 3> directionString);

    /*!
     * \brief Get the char index from lettres coordinate
     * \param c The char to get index
     * \return the index of the char
     */
    static short chartToShort(char c);
};



#endif // DIRECTION_H
