/**
 *  @file    Point.h
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    30/09/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Class for point handling in a coordinate system.
 *  It contains some redefined operators.
 */

#pragma once

#include <ostream>
#include "Dir.h"
#include <iostream>

using namespace std;

class Point {

public:

    /**
     * Homogenous constant
     */
    static constexpr float HC = 1.0f;

    /**
     * Point parameters
     */
    float x, y, z;

    Point() = default;;

    /**
     * Constructor for point
     * @param x
     * @param y
     * @param z
     */
    Point(float x, float y, float z) : x(x), y(y), z(z) {};

    /**
     * Minus operator
     * @param p: input point
     * @return direction between this and input value
     */
    Dir operator - (const Point &p) const {
        return { x - p.x, y - p.y, z - p.z };
    }

    /**
     * Plus operator
     * @param dir: input direction
     * @return point result from adding dir to this
     */
    Point operator + (const Dir &dir) const {
        return { x + dir.x, y + dir.y, z + dir.z };
    }

    /**
     * Plus operator
     * @param point: input point
     * @return point result from adding dir to this
     */
    Point operator + (const Point &point) const {
        return { x + point.x, y + point.y, z + point.z };
    }

    /**
     * Minus operator
     * @param dir: input direction
     * @return point result from substraction dir to this
     */
    Point operator - (const Dir &dir) const {
        return { x - dir.x, y - dir.y, z - dir.z };
    }

    /**
     * Div operator
     * @param num: divisor
     * @return point result from dividing this point by float num
     */
    Point operator / (const float num) const {
        return { x / num, y / num, z / num };
    }

    /**
     * Div operator
     * @param num: divisor
     * @return point result from dividing this point by float num
     */
    void operator /= (const float num) {
        x /= num;
        y /= num;
        z /= num;
    }

    /**
     * Product with point and float
     * @param f input float
     * @return this point * f
     */
    Point operator * (const float f){
        return {x * f, y * f, z * f};
    }

    /**
     * Gets the point that is at the same distance of this and a input point along the direction that joins both
     * @param p input point
     * @return point that is located half way from this to [p]
     */
    Point getMiddlePointWith(const Point &p) const {
        return { (x + p.x) / 2.0f, (y + p.y) / 2.0f, (z + p.z) / 2.0f };
    }

    /**
     * Get the point at is twice the distance with other passed as parameter
     * @param p input point
     * @return point at double distance from this than [p]
     */
    Point getTwiceDistanceWith(const Point &p) const {
        return  *this + (p - *this) * 2.0f ;
    }


    /** MOVING COORDINATES METHODS **/

    Point moveX(float offset) const {
        return { x + offset, y, z };
    }

    Point moveY(float offset) const {
        return { x , y + offset, z };
    }

    Point moveZ(float offset) const {
        return { x, y, z + offset };
    }


    /** HIGHER AND LOWER OPERATORS **/

    bool operator <= (const Point &point) const {
        return (x - point.x <= 0.00001) &&
               (y - point.y <= 0.00001) &&
               (z - point.z <= 0.00001);
    }

    bool operator >= (const Point &point) const {
        return (point.x - x <= 0.00001) &&
               (point.y - y <= 0.00001) &&
               (point.z - z <= 0.00001);
    }

    /**
     * Stream to be overwritten
     * @param os: stream input
     * @param p: value to be printes
     * @return stream with p data printed
     */
    friend ostream& operator << (ostream &os, const Point &p){
        os << "Point(" << p.x << " , " << p.y << " , " << p.z << ")";
        return os;
    }
};