#pragma once

#include "../math/math.h"
#include "../objects/camera.h"
#include "../objects/mesh.h"

namespace objects {
    struct light
    {
        math::vector3FX dir = math::vector3FX(0, FX_FROM_F(-1), 0);
        math::fixed intensity = 1;

        light() { }
        light(const math::vector3FX& dir, const math::fixed& intensity) : dir(dir.normalized()), intensity(intensity) { }
    };

    struct scene
    {
        vector<light> lights;

        vector<objects::mesh*> meshes;

        scene() { }
        scene(const int& maxLights, const int& maxObjects) : lights(utils::makeVector<light>(maxLights)), meshes(utils::makeVector<objects::mesh*>(maxObjects)) {}
    };
}