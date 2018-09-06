/**
 *  @file    Sphere.h
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    12/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Header file for sphere class
 *  Sphere definition with radius and point
 */

#pragma once

#include "Shape.h"

class Sphere : public Shape {

public:

    /**
     * Default constructor
     */
    Sphere();

    /**
     * Sphere constructor
     * @param radius of the sphere
     * @param center of the sphere
     */
    Sphere(float radius, const Point &center);

    /**
     * Intersection method
     * @param ray: input ray
     * @return distance from ray origin to intersection point if intersects, max float value otherwise
     */
    float intersect(const Ray &ray) const;

    /**
     * Get normal of the sphere at a point
     * @param intersectedPoint: point to get normal from
     * @return normal between itnersected point and sphere center
     */
    Dir getNormal(const Point &intersectedPoint) const;

    Sphere moveX(float offset) const;

    Sphere moveY(float offset) const;

    Sphere moveZ(float offset) const;

    void setRadius(float radius);
	
	    vector<Point> getPointLIghts(int samples){
        vector<Point> resul = vector<Point>(samples);
        for(int i=0;i<samples;i++){
            float dirX = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(radius*radius)));
            float dirY = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/((radius*radius)-dirX)));
            float dirZ = (radius * radius) - dirX - dirY;
            //solo en cuadrente ++
            dirX = (dirX!=0) ? sqrtf(dirX) : 0;
            dirY = (dirY!=0) ? sqrtf(dirY) : 0;
            dirZ = (dirZ!=0) ? sqrtf(dirZ) : 0;
            //cambio a todos los cuadrantes
            int randX = rand() % 2;
            int randY = rand() % 2;
            int randZ = rand() % 2;

            dirX = (randX == 1) ? dirX : -dirX;
            dirY = (randY == 1) ? dirY : -dirY;
            dirZ = (randZ == 1) ? dirZ : -dirZ;

            resul[i] = center+Dir(dirX,dirY,dirZ);
        }
        return resul;
    }

private:

    /// SPHERE PARAMETERS
    float radius, sqrd_radius;

    Point center;

};