#pragma once

#include "../math/math.h"

namespace objects {
    struct transform {
        math::vector3FX pos;
        math::quaternion rot;

        transform() { }
        transform(const math::vector3FX& pos) : pos(pos) { }
        transform(const math::vector3FX& pos, const math::quaternion rot) : pos(pos), rot(rot) { }

        math::vector3FX getForward() const { return rot.rotateVector(math::vector3FX::forward()); }
        math::vector3FX getUp() const { return rot.rotateVector(math::vector3FX::up()); }
        math::vector3FX getRight() const { return rot.rotateVector(math::vector3FX::right()); }

        void rotate(const math::vector3FX& axis, const float& angle);
    };
}