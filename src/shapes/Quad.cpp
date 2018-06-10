#include <tuple>
#include "Quad.h"

Quad::Quad(const Point &a, const Point &b, const Point &c, const Point &d)
    : Plane((b - a).cross(c - a).normalize(), a),
      a(a), b(b), c(c), d(d),
      t1(Triangle(a, b, c)),
      t2(Triangle(b, c, d)) {

    center = (a + b + c + d) / 4.0f;
}

Quad::Quad(const Point &a, const Point &b, const Point &c)
    : Plane((b - a).cross(c - a).normalize(), a),
      a(a), b(b), c(c), d(a.getTwiceDistanceWith(b.getMiddlePointWith(c))),
      t1(Triangle(a, b, c)), t2(Triangle(b, c, d)),
      center(b.getMiddlePointWith(c))  { }


float Quad::intersect(const Ray &ray) const {
    float dist = Plane::intersect(ray);
    if (dist == MAX_FLOAT) return MAX_FLOAT;

    return (t1.intersect(ray) < MAX_FLOAT) ? dist : (t2.intersect(ray) < MAX_FLOAT) ? dist : MAX_FLOAT;
}

tuple<Point, Point, Point, Point> Quad::getCorners() const {
    return make_tuple(a, b, c, d);
}

Dir Quad::getNormal(const Point &intersectedPoint) const {
    return t1.getNormal(intersectedPoint);
}

Dir Quad::getNormal() const {
    return t1.getNormal();
}

const Point &Quad::getCenter() const {
    return center;
}

Quad Quad::moveX(float offset) const {
    return { a.moveX(offset), b.moveX(offset), c.moveX(offset), d.moveX(offset) };
}

Quad Quad::moveY(float offset) const {
    return { a.moveY(offset), b.moveY(offset), c.moveY(offset), d.moveY(offset) };
}

Quad Quad::moveZ(float offset) const {
    return { a.moveZ(offset), b.moveZ(offset), c.moveZ(offset), d.moveZ(offset) };
}

void Quad::bounds(){
    for(int i=0;i<3;i++){
        Point x;
        if(i==0){
            x=a;
        } else if(i==1){
            x=b;
        } else{
            x= c;
        }
        minX = (x.x<minX) ? x.x : minX;
        minY = (x.y<minY) ? x.y : minY;
        minZ = (x.z<minZ) ? x.z : minZ;

        maxX = (x.x>maxX) ? x.x : maxX;
        maxY = (x.y>maxY) ? x.y : maxY;
        maxZ = (x.z>maxZ) ? x.z : maxZ;

   }

}

vector<Point> Quad::sampleLight2(int samples){

    this->bounds();
    vector<Point> resul = vector<Point>(samples);
    for(int i=0;i<samples;i++) {
        resul[i] = Point(minX + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxX - minX))),
              minY + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxY - minY))),
              minZ + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxZ - minZ))));
    }

    return resul;
}

