#pragma once

#include "../math/math.h"
#include "../vector/Vector.h"

namespace objects {
    struct tri
    {
        math::vector3F p[3];
    };

    struct mesh
    {
        Vector<tri> tris;
    };
}