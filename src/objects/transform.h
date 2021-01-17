#pragma once

#include "../math/math.h"

namespace objects {
    struct transform {
    private:
        math::vector3F forward = math::vector3F(0, 0, FX_FROM_F(1));
        math::vector3F up = math::vector3F(0, FX_FROM_F(1), 0);
        math::vector3F right = math::vector3F(FX_FROM_F(1), 0, 0);
    public:
        math::vector3F pos = math::vector3F(0, 0, 0);

        transform() { }
        transform(const math::vector3F& pos) : pos(pos) { }
        transform(const math::vector3F& pos, const math::vector3F& forward, const math::vector3F& up) : pos(pos) {
            this->forward = forward.normalized();
            this->up = (up - this->forward * math::vector3F::dot(up, this->forward)).normalized();
            this->right = math::vector3F::cross(this->up, this->forward);
        }

        math::vector3F getForward() const { return forward; }
        math::vector3F getUp() const { return up; }
        math::vector3F getRight() const { return right; }
        void setForward(const math::vector3F& newForward);
        void setUp(const math::vector3F& newUp);
        void setRight(const math::vector3F& newRight);

        void rotateX(const math::fixed& angle);
        void rotateY(const math::fixed& angle);
        void rotateZ(const math::fixed& angle);
    };
}