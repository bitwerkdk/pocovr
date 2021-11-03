#pragma once

#include <TFT_eSPI.h>
#include "transform.h"
#include "../math/math.h"

namespace objects {
    struct camera {
        math::mat4x4FX projMat = math::mat4x4FX::projection(FX_FROM_F(90), FX_FROM_F(1), FX_FROM_F(10), FX_FROM_I(TFT_WIDTH), FX_FROM_I(TFT_HEIGHT));
        transform objTransform;

        camera() { }
        camera(const math::vector3FX& pos) : objTransform(transform(pos)) { }
        camera(const math::vector3FX& pos, const math::quaternion& rot) : objTransform(transform(pos, rot)) { }
        camera(const math::fixed& fov) {
            projMat = math::mat4x4FX::projection(FX_FROM_F(fov), FX_FROM_F(1), FX_FROM_F(10), FX_FROM_I(TFT_WIDTH), FX_FROM_I(TFT_HEIGHT));
        }
        camera(const math::fixed& fov, const math::fixed& nearPlane, const math::fixed& farPlane) {
            projMat = math::mat4x4FX::projection(fov, nearPlane, farPlane, FX_FROM_I(TFT_WIDTH), FX_FROM_I(TFT_HEIGHT));
        }
        camera(const math::fixed& fov, const math::fixed& nearPlane, const math::fixed& farPlane, const math::fixed& width, const math::fixed& height) {
            projMat = math::mat4x4FX::projection(fov, nearPlane, farPlane, width, height);
        }
        camera(const math::vector3FX& pos, const math::fixed& fov) : objTransform(transform(pos)) {
            projMat = math::mat4x4FX::projection(FX_FROM_F(fov), FX_FROM_F(1), FX_FROM_F(10), FX_FROM_I(TFT_WIDTH), FX_FROM_I(TFT_HEIGHT));
        }
        camera(const math::vector3FX& pos, const math::fixed& fov, const math::fixed& nearPlane, const math::fixed& farPlane) : objTransform(transform(pos)) {
            projMat = math::mat4x4FX::projection(fov, nearPlane, farPlane, FX_FROM_I(TFT_WIDTH), FX_FROM_I(TFT_HEIGHT));
        }
        camera(const math::vector3FX& pos, const math::fixed& fov, const math::fixed& nearPlane, const math::fixed& farPlane, const math::fixed& width, const math::fixed& height) : objTransform(transform(pos)) {
            projMat = math::mat4x4FX::projection(fov, nearPlane, farPlane, width, height);
        }
        camera(const math::vector3FX& pos, const math::quaternion& rot, const math::fixed& fov) : objTransform(transform(pos, rot)) {
            projMat = math::mat4x4FX::projection(FX_FROM_F(fov), FX_FROM_F(1), FX_FROM_F(10), FX_FROM_I(TFT_WIDTH), FX_FROM_I(TFT_HEIGHT));
        }
        camera(const math::vector3FX& pos, const math::quaternion& rot, const math::fixed& fov, const math::fixed& nearPlane, const math::fixed& farPlane) : objTransform(transform(pos, rot)) {
            projMat = math::mat4x4FX::projection(fov, nearPlane, farPlane, FX_FROM_I(TFT_WIDTH), FX_FROM_I(TFT_HEIGHT));
        }
        camera(const math::vector3FX& pos, const math::quaternion& rot, const math::fixed& fov, const math::fixed& nearPlane, const math::fixed& farPlane, const math::fixed& width, const math::fixed& height) : objTransform(transform(pos, rot)) {
            projMat = math::mat4x4FX::projection(fov, nearPlane, farPlane, width, height);
        }
    };
}