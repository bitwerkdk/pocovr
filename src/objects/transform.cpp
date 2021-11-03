#include "transform.h"
#include "Arduino.h"

namespace objects {
    void transform::rotate(const math::vector3FX& axis, const float& angle) {
        math::quaternion rotation(angle, axis);
        rot = rotation * rot;
    }
}