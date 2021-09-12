#include "transform.h"

namespace objects {
    void transform::rotate(const math::vector3F& axis, const float& angle) {
        math::quaternion rotation(angle, axis);
        rot = rotation * rot;
    }
}