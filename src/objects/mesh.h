#pragma once

#include "../math/math.h"
#include "../vector/Vector.h"

namespace objects {
    struct tri
    {
        math::vector3F p[3];

        tri(math::vector3F p0, math::vector3F p1, math::vector3F p2) : p({ p0, p1, p2 }) { }
    };

    struct mesh
    {
        Vector<tri> tris;
        math::vector3F pos = math::vector3F(0, 0, FX_FROM_F(3));
        math::vector3F forward = math::vector3F(0, 0, FX_FROM_F(1)), up = math::vector3F(0, FX_FROM_F(1), 0);
    };
}