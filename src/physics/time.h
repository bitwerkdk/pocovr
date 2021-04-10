#pragma once

namespace math { typedef long fixed; }

namespace physics {
    extern math::fixed lastUpdateTime;
    extern math::fixed deltaTime;
    extern math::fixed deltaTimeSec;

    void updateTime();
}