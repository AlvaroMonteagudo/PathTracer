#pragma once

#include <Dir.h>
#include "Triangle.h"

class MeshTriangle : public Triangle {

public:

    MeshTriangle(const Point &a, const Point &b, const Point &c, const Dir &normalA, const Dir &normalB,
                 const Dir &normalC);

    Dir getNormal(const Point &intersectedPoint) const;

private:

    Dir normalA, normalB, normalC;

};
