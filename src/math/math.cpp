#include "math.h"

#include <Arduino.h>

namespace math {
    #pragma region fixed
    fixed fxPowUint(const fixed& base, const unsigned int& exponent) {
        fixed result = FX_FROM_I(1);
        for (int i = 0; i < exponent; i++) {
            result = FX_MUL(result, result);
        }
        return result;
    }
    fixed fxSqrt(const fixed& x) {
        return FX_FROM_F(sqrt(FX_TO_F(x)));
    }
    fixed fxSin(const fixed& x) {
        return FX_FROM_F(sin(FX_TO_F(x)));
    }
    fixed fxCos(const fixed& x) {
        return FX_FROM_F(cos(FX_TO_F(x)));
    }
    fixed fxTan(const fixed& x) {
        return FX_FROM_F(tan(FX_TO_F(x)));
    }
    #pragma endregion

    #pragma region vector
    fixed vector2F::magnitude() const {
        return fxSqrt(FX_ADD(FX_MUL(x, x), FX_MUL(y, y)));
    }
    vector2F vector2F::normalized() const {
        return *this / magnitude();
    }

    fixed vector3F::magnitude() const {
        return fxSqrt(FX_ADD(FX_ADD(FX_MUL(x, x), FX_MUL(y, y)), FX_MUL(z, z)));
    }
    vector3F vector3F::normalized() const {
        return *this / magnitude();
    }
    static fixed dot(const vector3F& a, const vector3F& b) {
        return FX_ADD(FX_ADD(FX_MUL(a.x, b.x), FX_MUL(a.x, b.x)), FX_MUL(a.x, b.x));
    }
    static vector3F cross(const vector3F& a, const vector3F& b) {
        return vector3F(FX_SUB(FX_MUL(a.y, b.z), FX_MUL(a.z, b.y)), FX_SUB(FX_MUL(a.z, b.x), FX_MUL(a.x, b.z)), FX_SUB(FX_MUL(a.x, b.y), FX_MUL(a.y, b.x)));
    }
    #pragma endregion

    #pragma region matrix
    vector4F mat4x4::operator *(const vector4F& second) const
    {
        vector4F result;
        result.x = FX_ADD(FX_ADD(FX_MUL(m[0][0], second.x), FX_MUL(m[0][1], second.y)), FX_ADD(FX_MUL(m[0][2], second.z), FX_MUL(m[0][3], second.w)));
        result.y = FX_ADD(FX_ADD(FX_MUL(m[1][0], second.x), FX_MUL(m[1][1], second.y)), FX_ADD(FX_MUL(m[1][2], second.z), FX_MUL(m[1][3], second.w)));
        result.z = FX_ADD(FX_ADD(FX_MUL(m[2][0], second.x), FX_MUL(m[2][1], second.y)), FX_ADD(FX_MUL(m[2][2], second.z), FX_MUL(m[2][3], second.w)));
        result.w = FX_ADD(FX_ADD(FX_MUL(m[3][0], second.x), FX_MUL(m[3][1], second.y)), FX_ADD(FX_MUL(m[3][2], second.z), FX_MUL(m[3][3], second.w)));
        return result;
    }

    mat4x4 mat4x4::XRotation(const fixed& angle) {
        return mat4x4(1, 0, 0, 0,
                      0, fxCos(angle), -fxSin(angle), 0,
                      0, fxSin(angle), fxCos(angle), 0,
                      0, 0, 0, 1);
    }
    mat4x4 mat4x4::YRotation(const fixed& angle) {
        return mat4x4(fxCos(angle), 0, fxSin(angle), 0,
                      0, 0, 0, 0,
                      -fxSin(angle), 0, fxCos(angle), 0,
                      0, 0, 0, 1);
    }
    mat4x4 mat4x4::ZRotation(const fixed& angle) {
        return mat4x4(fxCos(angle), -fxSin(angle), 0, 0,
                      fxSin(angle), fxCos(angle), 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1);
    }
    mat4x4 mat4x4::Projection(const fixed& fov, const fixed& nearPlane, const fixed& farPlane, const fixed& width, const fixed& height) {
        fixed f = FX_DIV(FX_FROM_I(1), fxTan(fov >> 1));
        fixed q = FX_DIV(farPlane, FX_SUB(farPlane, nearPlane));
        return mat4x4(FX_MUL(FX_DIV(height, width), f), 0, 0, 0,
                      0, f, 0, 0,
                      0, 0, q, 1,
                      0, 0, FX_MUL(-nearPlane, q), 0);
    }
    mat4x4 mat4x4::Transformation(const vector3F& pos, const vector3F& forward, const vector3F& up) {
        vector3F right = vector3F::cross(forward, up);
        return mat4x4(forward.x, forward.y, forward.z, 0,
                      right.x, right.y, right.z, 0,
                      up.x, up.y, up.z, 0,
                      pos.x, pos.y, pos.z, 1);
    }
    mat4x4 mat4x4::InverseTransformation(const vector3F& pos, const vector3F& forward, const vector3F& up) {
        vector3F right = vector3F::cross(forward, up);
        return mat4x4(forward.x, right.x, up.x, 0,
                      forward.y, right.y, up.y, 0,
                      forward.z, right.z, up.z, 0,
                      -vector3F::dot(pos, forward), -vector3F::dot(pos, right), -vector3F::dot(pos, up), 1);
    }
    #pragma endregion
}