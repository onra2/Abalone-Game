/*!
 * \file Color.h
 *
 * \brief color class definition
 */
#ifndef COLOR_H
#define COLOR_H
#include <iostream>
#include <string>
#include <array>
#include <tuple>

/*!
 * \brief Available colors of players marbles
*/
class Color{
    /*!
     * \brief the ansi color code
     */
    struct ansiColors{
        const std::tuple<std::string,char> black = std::make_tuple("\033[30;m",'B');
        const std::tuple<std::string,char> white = std::make_tuple("\033[37;m",'W');
    };

public:
    /*!
     * \brief Get the color of the player
     *
     *  \param player id
     */
    const static std::tuple<std::string,char> getColorTuple(int player);

    /*!
     * \brief Get the Ansi color code with the enum color
     *
     *  \param color The enum color to get the ANSI color code
     */
    const static std::string getANSICode(int player);

    /*!
     * \brief Get the displaying char with the enum color
     *
     *  \param color The enum color to get the displaying char
     */
    static char getChar(int player);
};

#endif // COLOR_H
