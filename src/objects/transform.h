#pragma once

#include "../math/math.h"

namespace objects {
    struct transform {
        math::vector3F pos;
        math::quaternion rot;

        transform() { }
        transform(const math::vector3F& pos) : pos(pos) { }
        transform(const math::vector3F& pos, const math::quaternion rot) : pos(pos), rot(rot) { }

        math::vector3F getForward() const { return rot.rotateVector(math::vector3F::forward()); }
        math::vector3F getUp() const { return rot.rotateVector(math::vector3F::up()); }
        math::vector3F getRight() const { return rot.rotateVector(math::vector3F::right()); }

        void rotate(const math::vector3F& axis, const float& angle);
    };
}