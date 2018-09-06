/**
 *  @file    Dir.h
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    30/09/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Class for directions handling in a coordinate system.
 *  It contains some redefined operators and useful method
 *  to calculate commonly used features of directions such
 *  as its module or normalization.
 */
#pragma once

#include <cmath>
#include <cassert>
#include <ostream>

using namespace std;

class Dir{
	
public:

    /**
     * Homogenous constant
     */
    static constexpr float HC = 0.0f;

    /**
     * Direction parameters
     */
    float x, y, z;

    Dir() = default;

    /**
     * Constructor for direction
     * @param x: coordinate x of direction
     * @param y: coordinate y of direction
     * @param z: coordinate z of direction
     */
    Dir(float x, float y, float z) : x(x), y(y), z(z) {}

    Dir changeDirection() const {
        return { -x, -y, -z };
    }

    /**
     * Direction plus operator
     * @param v: input direction
     * @return result of aplying plus operator to this and the input direction
     */
    Dir operator + (const Dir &v) const {
        return { x + v.x, y + v.y, z + v.z };
    }

    /**
     * Direction short plus operator
     * @param v: input direction
     */
    void operator += (const Dir &v) {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    /**
     * Direction minus operator
     * @param v: input direction
     * @return result of aplying minus operator to this and the input direction
     */
    Dir operator - (const Dir &v) const {
        return { x - v.x, y - v.y, z - v.z };
    }

    /**
     * Direction short minus operator
     * @param v: input direction
     */
    void operator -= (const Dir &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }

    /**
     * Direction product with constant operator
     * @param r: input value
     * @return this direction mutiplied by r
     */
    Dir operator * (const float r) const {
        return { x * r, y * r, z * r };
    }

    /**
     * Direction product with constant operator
     * @param r: input value
     */
    void operator *= (const float r)  {
        x *= r;
        y *= r;
        z *= r;
    }

    /**
     * Direction division with constant operator
     * @param r: input value
     * @return this direction divided by r
     */
    Dir operator / (const float r) const {
        return { x / r, y / r, z / r };
    }

    /**
     * Direction division with constant operator
     * @param r: input value
     */
    void operator /= (const float r)  {
        x /= r;
        y /= r;
        z /= r;
    }

    /**
     * Equality validation between directions
     * @param v: input direction
     * @return true if this equals input direction, false otherwise
     */
    bool operator == (const Dir &v) const {
        return (x == v.x) & (y == v.y) & (z == v.z);
    }

    /**
     * Inequality validation between directions
     * @param v: input direction
     * @return true if this is not equals input direction, false otherwise
     */
    bool operator != (const Dir &v) const {
        return !(*this == v);
    }

    /**
     * Direction module calculation
     * @return module of this direction
     */
    float module() const {
        return sqrt(x * x + y * y + z * z);
    }

    /**
     * Normalization of direction
     * @return this direction normalized
     */
    Dir normalize() const {
        float len = module();
        assert(len > 0);
        return (*this) / len;
    }

    /**
     * Dot product operation
     * @param v: input direction
     * @return result from dot product between this and input value
     */
    float dot(const Dir &v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    /**
     * Cross product operation
     * @param v: input direction
     * @return direction obtained with cross product between this and the input value
     */
    Dir cross(const Dir &v) const {
        return { y * v.z - z * v.y,
                 z * v.x - x * v.z,
                 x * v.y - y * v.x };

    }

    /**
     * Get cosine between two directions
     * @param dir input direction
     * @return cosine between this and [dir]
     */
    float getCosWith(const Dir &dir) const {
        return this->dot(dir) / (this->module() * dir.module());
    }

    /**
     * Utility to ease visualization of object Dir
     * @param os: stream to be written
     * @param v: value to output
     * @return overweritten stream with values from the input value
     */
    friend ostream& operator << (ostream &os, const Dir &v){
        os << "Dir(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }

};

#define X_AXIS Dir(1, 0, 0)
#define Y_AXIS Dir(0, 1, 0)
#define Z_AXIS Dir(0, 0, 1)






