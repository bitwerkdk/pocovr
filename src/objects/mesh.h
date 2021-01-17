#pragma once

#include "transform.h"
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
        transform objTransform;

        mesh() { }
        mesh(const math::vector3F& pos) : objTransform(transform(pos)) { }
        mesh(const math::vector3F& pos, const math::vector3F& forward, const math::vector3F& up) : objTransform(transform(pos, forward, up)) { }
    };
}