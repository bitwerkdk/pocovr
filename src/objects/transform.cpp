#include "transform.h"

namespace objects {
    void transform::setForward(const math::vector3F& newForward) {
        forward = newForward.normalized();
        up = (up - forward * math::vector3F::dot(up, forward)).normalized();
        right = math::vector3F::cross(up, forward);
    }
    void transform::setUp(const math::vector3F& newUp) {
        up = newUp.normalized();
        forward = (forward - up * math::vector3F::dot(forward, up)).normalized();
        right = math::vector3F::cross(up, forward);
    }
    void transform::setRight(const math::vector3F& newRight) {
        right = newRight.normalized();
        up = (up - right * math::vector3F::dot(up, right)).normalized();
        forward = math::vector3F::cross(right, up);
    }

    void transform::rotateX(const math::fixed& angle) {
        math::mat4x4 rotMat = math::mat4x4::xRotation(angle);
        math::vector4F tempVec4;
        tempVec4 = rotMat * math::vector4F(forward.x, forward.y, forward.z, FX_FROM_I(1));
        forward = math::vector3F(tempVec4.x, tempVec4.y, tempVec4.z).normalized();
        tempVec4 = rotMat * math::vector4F(up.x, up.y, up.z, FX_FROM_I(1));
        up = math::vector3F(tempVec4.x, tempVec4.y, tempVec4.z).normalized();
        right = math::vector3F::cross(up, forward);
    }
    void transform::rotateY(const math::fixed& angle) {
        math::mat4x4 rotMat = math::mat4x4::yRotation(angle);
        math::vector4F tempVec4;
        tempVec4 = rotMat * math::vector4F(forward.x, forward.y, forward.z, FX_FROM_I(1));
        forward = math::vector3F(tempVec4.x, tempVec4.y, tempVec4.z).normalized();
        tempVec4 = rotMat * math::vector4F(up.x, up.y, up.z, FX_FROM_I(1));
        up = math::vector3F(tempVec4.x, tempVec4.y, tempVec4.z).normalized();
        right = math::vector3F::cross(up, forward);
    }
    void transform::rotateZ(const math::fixed& angle) {
        math::mat4x4 rotMat = math::mat4x4::zRotation(angle);
        math::vector4F tempVec4;
        tempVec4 = rotMat * math::vector4F(forward.x, forward.y, forward.z, FX_FROM_I(1));
        forward = math::vector3F(tempVec4.x, tempVec4.y, tempVec4.z).normalized();
        tempVec4 = rotMat * math::vector4F(up.x, up.y, up.z, FX_FROM_I(1));
        up = math::vector3F(tempVec4.x, tempVec4.y, tempVec4.z).normalized();
        right = math::vector3F::cross(up, forward);
    }
}