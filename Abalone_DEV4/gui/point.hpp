#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <utility>
#include <cmath>
#include <vector>

/**
 * An alias for a pair of elements of the same type. The point (1,1) can be 
 * built as <code>point<double> p {1,-1}</code>.
 * @brief An alias for a pair of elements of the same type.
 */
template<class T>
using point = std::pair<T,T>;

/**
 * An alias for point<double>.
 * @brief An alias for point<double>
 */
using point2d = point<double>;

/*
 * An alias for std::make_pair<T,T>, to create points.
 * @brief An alias for std::make_pair<T,T>, to create points.
 * @param t1 the first coordinate of the point to build
 * @param t2 the second coordinate of the point to build
 * @return the point (t1, t2)
 */
template<class T>
auto make_point(T&& t1, T&& t2)
{
    return std::make_pair<T,T>(std::forward<T>(t1), std::forward<T>(t2));
}

/**
 * Returns true if two given points coincide up to a precision, returns 
 * false otherwise.
 * <p>
 * More precisely, (x1, y1) == (x2, y2) up to a precision E
 * iff |x1 - x2| < E and |y1 - y2| < E
 * @param p1 a first point to check equality
 * @param p2 a second point to check equality
 * @return true if two given points coincide up to a precision
 */
template<class T>
bool coincide(const point<T>& p1, const point<T>& p2, T precision = 10E-9L)
{
    return std::abs(p1.first - p2.first) < precision 
        && std::abs(p1.second - p2.second) < precision;   
}

/**
 * Returns the euclidian distance between two points p1 and p2.
 * @brief Returns the euclidian distance between two points p1 and p2.
 * @param p1 a first point
 * @param p2 a second point
 * @return the euclidian distance between two points p1 and p2.
 */
template<class R = double, class T>
R dist(const point<T>& p1, const point<T>& p2)
{
    return std::hypot(p1.first - p2.first, p1.second - p2.second);
}

/*
 * Returns the Manhattan distance between two points p1 and p2.
 * @brief Returns the Manhattan distance between two points p1 and p2.
 * @param p1 a first point
 * @param p2 a second point
 * @return the Manhattan distance between two points p1 and p2.
 */
template<class R = double, class T>
R manhattan(const point<T>& p1, const point<T>& p2)
{
    return std::abs(p1.first - p2.first) + std::abs(p1.second - p2.second);
}

/**
 * Converts the given point (specified in cartesian coordinates) to 
 * a point expressed in polar coordinates.
 * <p>
 * Note that the argument (in radians) of the returned polar point will 
 * always lie in [-pi, pi]
 * @brief Converts the given point to polar coordinates
 * @param p the point to convert to polar coordinates
 * @return the polar expression of p
 */ 
template<class T>
point<T> polar(const point<T>& p)
{
    return make_point(std::hypot(p.first, p.second), std::atan2(p.second, p.first));
}

/**
 * Converts the given point (specified in polar coordinates) to 
 * a point expressed in cartesian coordinates.
 * @brief Converts the given point to cartesian coordinates
 * @param p the point to convert to cartesian coordinates
 * @return the cartesian expression of p
 */
template<class T>
point<T> cartesian(const point<T>& p)
{
    return make_point(p.first * std::cos(p.second), p.first * std::sin(p.second));
}

/*
 * Translates the polar point (mod, arg) by the cartesian vector (p.first, p.second).
 * <p>
 * The result is expressed in cartesian coordinates.
 * @brief Translates a polar point by a cartesian vector
 * @param p the point expressing the translation vector
 * @param mod the modulus of the polar point to translate
 * @param arg the argument of the polar point to translate
 * @return the result of the translation, expressed in cartesian coordinates
 */
template<class T>
point<T> polar_translate(const point<T>& p, const T& mod, const T& arg)
{
    auto vec = cartesian(make_point(mod, arg));
    return make_point(p.first + vec.first, p.second + vec.second);
}

/**
 * Creates an orbit of n points symetrically spread around some coordinate,
 * starting from an optional angle shift.
 * <p>
 * For instance, <code>orbit({1,1}, 6, 2., (3.141592654 / 4));</code> creates 
 * 6 points around the coordinate (1,1), spreaded symetrically as a regular 
 * hexagon, the first point starting at an amplitude of pi/4.
 * <p>
 * The created points are all expressed in cartesian coordinates
 * @param p the point to orbit around
 * @param n the number of points in the orbit
 * @param radius the radius of the orbit
 * @param arg_shit the starting angle of the first orbiting point, 
 * specified in radians
 * @return a std::vector of n orbiting points
 */
template<class T>
auto orbit(const point<T>& p, unsigned n, T radius, T arg_shift = 0)
{
    static constexpr T PI = atan(1) * 4;
    
    T angle = 2 * PI / n;    
    std::vector<point<T>> points(n);
    for(unsigned i = 0; i < n; i++)
        points[i] = polar_translate(p, radius, arg_shift + i * angle);
    return points;
}

#endif
