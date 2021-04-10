#pragma once

#define RGB565(r,g,b) (unsigned short)((unsigned short)(r << 11) + (unsigned short)((unsigned short)(g << 10) >> 5) + (unsigned short)((unsigned short)(b << 11) >> 11))

namespace objects { struct scene; struct transform; struct camera; }
namespace math { typedef long fixed; }

namespace gfx {
    extern objects::transform headsetTransform;
    extern math::fixed ipd;
    extern objects::camera leftCamera;
    extern objects::camera rightCamera;

    void initialize();
    void renderScene(const objects::scene& scene);
}