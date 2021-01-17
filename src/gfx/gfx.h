#pragma once

#define RGB565(r,g,b) (unsigned short)((unsigned short)(r << 11) + (unsigned short)((unsigned short)(g << 10) >> 5) + (unsigned short)((unsigned short)(b << 11) >> 11))

namespace gfx {
    void setup();
    void loop();
}