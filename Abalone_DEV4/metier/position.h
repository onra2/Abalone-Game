/*!
 * \file Point.h
 *
 * \brief Point class definition
 */
#ifndef POSITION_H
#define POSITION_H

/*!
 * \brief store the x and y coordinates
 */
class Position{
private:
    /*!
     * \brief The x and y coordinates
    */
    int x, y;
public:
    /*!
     * \brief Constructor
    */
    Position(int x, int y);

    /*!
     * \brief Get X coordinate
    */
    int getX();

    /*!
     * \brief Get Y coordinate
    */
    int getY();
};

#endif // POINT_H
