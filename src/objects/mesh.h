#pragma once

#include "transform.h"
#include "../math/math.h"
#include "../utils/utils.h"
#include "../vector/vector.h"

namespace objects {
    struct tri
    {
        math::vector3F p[3];

        tri(const math::vector3F& p0, const math::vector3F& p1, const math::vector3F& p2) : p({ p0, p1, p2 }) { }
    };
    
    struct screenTri
    {
        math::vector2F p[3];
        math::fixed brightness;

        screenTri(const math::vector2F& p0, const math::vector2F& p1, const math::vector2F& p2, const math::fixed& brightness) : p({ p0, p1, p2 }), brightness(brightness) { }
    };

    struct mesh
    {
        vector<tri> tris = utils::makeVector<tri>(100);
        transform objTransform;

        mesh() { }
        mesh(const unsigned int& maxTris) : tris(utils::makeVector<tri>(maxTris)) { }
        mesh(const math::vector3F& pos) : objTransform(transform(pos)) { }
        mesh(const math::vector3F& pos, const unsigned int& maxTris) : tris(utils::makeVector<tri>(maxTris)), objTransform(transform(pos)) { }
        mesh(const math::vector3F& pos, const math::vector3F& forward, const math::vector3F& up) : objTransform(transform(pos, forward, up)) { }
        mesh(const math::vector3F& pos, const math::vector3F& forward, const math::vector3F& up, const unsigned int& maxTris) : tris(utils::makeVector<tri>(maxTris)), objTransform(transform(pos, forward, up)) { }
    };
}