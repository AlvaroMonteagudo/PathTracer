/**
 *  @file    Mat.h
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    30/09/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Class that handles 4x4 matrix system.
 *  It contains useful operators.
 */

#pragma once

#include <ostream>

class Mat {

    public:

        /**
         * Matrix parameters
         */
        float   x00, x01, x02, x03,
                x10, x11, x12, x13,
                x20, x21, x22, x23,
                x30, x31, x32, x33;

        /**
         * @param x00
         * @param x01
         * @param x02
         * @param x03
         * @param x10
         * @param x11
         * @param x12
         * @param x13
         * @param x20
         * @param x21
         * @param x22
         * @param x23
         * @param x30
         * @param x31
         * @param x32
         * @param x33
         */
        Mat(const float x00, const float x01, const float x02, const float x03,
            const float x10, const float x11, const float x12, const float x13,
            const float x20, const float x21, const float x22, const float x23,
            const float x30, const float x31, const float x32, const float x33) :
                x00(x00), x01(x01), x02(x02), x03(x03),
                x10(x10), x11(x11), x12(x12), x13(x13),
                x20(x20), x21(x21), x22(x22), x23(x23),
                x30(x30), x31(x31), x32(x32), x33(x33) {

        }

        /**
         * Matrix constructor to ease transform matrix construction
         * @param xAxis: axix for coordinate x
         * @param yAxis: axis for coordinate y
         * @param zAxis: axis for coordinate z
         * @param p: point value
         */
        Mat(const Dir &xAxis, const Dir &yAxis, const Dir &zAxis, const Point &p) :
            x00(xAxis.x), x01(yAxis.x), x02(zAxis.x), x03(p.x),
            x10(xAxis.y), x11(yAxis.y), x12(zAxis.y), x13(p.y),
            x20(xAxis.z), x21(yAxis.z), x22(zAxis.z), x23(p.z),
            x30(Dir::HC), x31(Dir::HC), x32(Dir::HC), x33(Point::HC) {

        }

        /**
         * @param mat: input matrix
         * @return matrix result from the product between this and the input matrix
         */
        Mat operator * (const Mat& mat){
            float r00 = x00*mat.x00 + x01*mat.x10 + x02*mat.x20 + x03*mat.x30;
            float r01 = x00*mat.x01 + x01*mat.x11 + x02*mat.x21 + x03*mat.x31;
            float r02 = x00*mat.x02 + x01*mat.x12 + x02*mat.x22 + x03*mat.x32;
            float r03 = x00*mat.x03 + x01*mat.x13 + x02*mat.x23 + x03*mat.x33;

            float r10 = x10*mat.x00 + x11*mat.x10 + x12*mat.x20 + x13*mat.x30;
            float r11 = x10*mat.x01 + x11*mat.x11 + x12*mat.x21 + x13*mat.x31;
            float r12 = x10*mat.x02 + x11*mat.x12 + x12*mat.x22 + x13*mat.x32;
            float r13 = x10*mat.x03 + x11*mat.x13 + x12*mat.x23 + x13*mat.x33;

            float r20 = x20*mat.x00 + x21*mat.x10 + x22*mat.x20 + x23*mat.x30;
            float r21 = x20*mat.x01 + x21*mat.x11 + x22*mat.x21 + x23*mat.x31;
            float r22 = x20*mat.x02 + x21*mat.x12 + x22*mat.x22 + x23*mat.x32;
            float r23 = x20*mat.x03 + x21*mat.x13 + x22*mat.x23 + x23*mat.x33;

            float r30 = x30*mat.x00 + x31*mat.x10 + x32*mat.x20 + x33*mat.x30;
            float r31 = x30*mat.x01 + x31*mat.x11 + x32*mat.x21 + x33*mat.x31;
            float r32 = x30*mat.x02 + x31*mat.x12 + x32*mat.x22 + x33*mat.x32;
            float r33 = x30*mat.x03 + x31*mat.x13 + x32*mat.x23 + x33*mat.x33;

            return { r00, r01, r02, r03,
                     r10, r11, r12, r13,
                     r20, r21, r22, r23,
                     r30, r31, r32, r33 };

        }

        /**
         * Product operator matrix and direction
         * @param dir: input direction
         * @return direction obtained of the operation
         */
        Dir operator * (const Dir& dir){
            return { x00*dir.x + x01*dir.y + x02*dir.z + x03*Dir::HC,
                     x10*dir.x + x11*dir.y + x12*dir.z + x13*Dir::HC,
                     x20*dir.x + x21*dir.y + x22*dir.z + x23*Dir::HC };

        }

        /**
         * Prodcut operator matrix and point
         * @param dir: input point
         * @return point obtained of the operation
         */
        Point operator * (const Point& dir){
            float h = x30*dir.x + x31*dir.y + x32*dir.z + x33*Point::HC;
            return { x00*dir.x + x01*dir.y + x02*dir.z + x03*Point::HC / h,
                     x10*dir.x + x11*dir.y + x12*dir.z + x13*Point::HC / h,
                     x20*dir.x + x21*dir.y + x22*dir.z + x23*Point::HC / h };

        }

        /** UNUSED FUNCTIONS **/
        /**
         * Identity matrix
         * @return identity matrix
         */
        Mat identity(){
            return { 1, 0, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 1, 0,
                     0, 0, 0, 1 };
        }

        /**
         * Translation of matrix
         * @param d: input direction
         * @return this translated by d
         */
        Mat translation(Dir &d){
            return { 1, 0, 0, d.x,
                     0, 1, 0, d.y,
                     0, 0, 1, d.z,
                     0, 0, 0, 1 };
        }

        /**
         * Scalation of matrix
         * @param k: value to be scaled from
         * @return this scaled by k
         */
        Mat scale(float k){
            return { k, 0, 0, 0,
                     0, k, 0, 0,
                     0, 0, k, 0,
                     0, 0, 0, 1 };
        }

        /**
         * Axis x rotation
         * @param angle: value of angle
         * @return this rotated by angle in axis x
         */
        static Mat rotateX(float angle){
            return { 1, 0, 0, 0,
                     0, cosf(angle), (-1)*sinf(angle), 0,
                     0, sinf(angle), cosf(angle), 0,
                     0, 0, 0, 1 };
        }

        /**
         * Axis y rotation
         * @param angle: value of angle
         * @return this rotated by angle in axis y
         */
        static Mat rotateY(float angle){
            return { cosf(angle), 0, sinf(angle), 0,
                     0, 1, 0, 0,
                     (-1)*sinf(angle), 0, cosf(angle), 0,
                     0, 0, 0, 1 };
        }

        /**
         * Axis z rotation
         * @param angle: value of angle
         * @return this rotated by angle in axis z
         */
        static Mat rotateZ(float angle){
            return { cosf(angle), (-1)*sinf(angle), 0, 0,
                     sinf(angle), cosf(angle), 0, 0,
                     0, 0, 1, 0,
                     0, 0, 0, 1 };
        }

        /**
         * Utility to ease data visualization
         * @param os: stream to be overwritten
         * @param m: value to be printed
         * @return stream with m data value
         */
        friend std::ostream& operator << (std::ostream &os, const Mat &m) {
            os << "Mat( " << m.x00 << ", " << m.x01 << ", " << m.x02 << ", " << m.x03 << std::endl
               << m.x10 << ", " << m.x11 << ", " << m.x12 << ", " << m.x13 << std::endl
               << m.x20 << ", " << m.x21 << ", " << m.x22 << ", " << m.x23 << std::endl
               << m.x30 << ", " << m.x31 << ", " << m.x32 << ", " << m.x33 << ")";
            return os;
        }
};

