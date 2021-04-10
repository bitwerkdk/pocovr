#include "time.h"

#include "Arduino.h"
#include "../math/math.h"

namespace physics {
    math::fixed lastUpdateTime;
    math::fixed deltaTime;
    math::fixed deltaTimeSec;

    void updateTime() {
        math::fixed ms = FX_FROM_I(millis());
        deltaTime = ms - lastUpdateTime;
        deltaTimeSec = deltaTime / 1000;
        lastUpdateTime = ms;
    }
}