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

    fixed fxMin(const fixed& a, const fixed& b) {
        return a < b ? a : b;
    }
    fixed fxMax(const fixed& a, const fixed& b) {
        return a > b ? a : b;
    }
    fixed fxClamp(const fixed& value, const fixed& min, const fixed& max) {
        return fxMin(fxMax(value, min), max);
    }
    fixed fxLerp(const fixed& a, const fixed& b, const fixed& t) {
        return FX_ADD(a, FX_MUL(FX_SUB(b, a), t));
    }
    #pragma endregion

    #pragma region vector
    fixed vector2F::magnitude() const {
        return fxSqrt(FX_ADD(FX_MUL(x, x), FX_MUL(y, y)));
    }
    vector2F vector2F::normalized() const {
        return *this / magnitude();
    }

    vector2F::operator vector3F() const { return vector3F(x, y, 0); }
    vector2F::operator vector4F() const { return vector4F(x, y, 0, FX_FROM_I(1)); }

    fixed vector3F::magnitude() const {
        return fxSqrt(FX_ADD(FX_ADD(FX_MUL(x, x), FX_MUL(y, y)), FX_MUL(z, z)));
    }
    vector3F vector3F::normalized() const {
        return *this / magnitude();
    }
    fixed vector3F::dot(const vector3F& a, const vector3F& b) {
        return FX_ADD(FX_ADD(FX_MUL(a.x, b.x), FX_MUL(a.y, b.y)), FX_MUL(a.z, b.z));
    }
    vector3F vector3F::cross(const vector3F& a, const vector3F& b) {
        return vector3F(FX_SUB(FX_MUL(a.y, b.z), FX_MUL(a.z, b.y)), FX_SUB(FX_MUL(a.z, b.x), FX_MUL(a.x, b.z)), FX_SUB(FX_MUL(a.x, b.y), FX_MUL(a.y, b.x)));
    }
        
    vector3F::operator vector2F() const { return vector2F(x, y); }
    vector3F::operator vector4F() const { return vector4F(x, y, z, FX_FROM_I(1)); }

    vector4F::operator vector2F() const { return vector2F(x, y); }
    vector4F::operator vector3F() const { return vector3F(x, y, z); }
    #pragma endregion

    #pragma region matrix
    mat4x4::mat4x4(const fixed& p00, const fixed& p10, const fixed& p20, const fixed& p30,
               const fixed& p01, const fixed& p11, const fixed& p21, const fixed& p31,
               const fixed& p02, const fixed& p12, const fixed& p22, const fixed& p32,
               const fixed& p03, const fixed& p13, const fixed& p23, const fixed& p33)
    {
        m[0][0] = p00;
        m[1][0] = p10;
        m[2][0] = p20;
        m[3][0] = p30;
        m[0][1] = p01;
        m[1][1] = p11;
        m[2][1] = p21;
        m[3][1] = p31;
        m[0][2] = p02;
        m[1][2] = p12;
        m[2][2] = p22;
        m[3][2] = p32;
        m[0][3] = p03;
        m[1][3] = p13;
        m[2][3] = p23;
        m[3][3] = p33;
    }
    
    vector4F mat4x4::operator *(const vector4F& second) const
    {
        vector4F result;
        result.x = FX_ADD(FX_ADD(FX_MUL(m[0][0], second.x), FX_MUL(m[0][1], second.y)), FX_ADD(FX_MUL(m[0][2], second.z), FX_MUL(m[0][3], second.w)));
        result.y = FX_ADD(FX_ADD(FX_MUL(m[1][0], second.x), FX_MUL(m[1][1], second.y)), FX_ADD(FX_MUL(m[1][2], second.z), FX_MUL(m[1][3], second.w)));
        result.z = FX_ADD(FX_ADD(FX_MUL(m[2][0], second.x), FX_MUL(m[2][1], second.y)), FX_ADD(FX_MUL(m[2][2], second.z), FX_MUL(m[2][3], second.w)));
        result.w = FX_ADD(FX_ADD(FX_MUL(m[3][0], second.x), FX_MUL(m[3][1], second.y)), FX_ADD(FX_MUL(m[3][2], second.z), FX_MUL(m[3][3], second.w)));
        return result;
    }

    mat4x4 mat4x4::xRotation(const fixed& angleDeg) {
        fixed angleRad = FX_DEG_TO_RAD(angleDeg);
        return mat4x4(FX_FROM_I(1), 0, 0, 0,
                      0, fxCos(angleRad), fxSin(angleRad), 0,
                      0, -fxSin(angleRad), fxCos(angleRad), 0,
                      0, 0, 0, FX_FROM_I(1));
    }
    mat4x4 mat4x4::yRotation(const fixed& angleDeg) {
        fixed angleRad = FX_DEG_TO_RAD(angleDeg);
        return mat4x4(fxCos(angleRad), 0, -fxSin(angleRad), 0,
                      0, FX_FROM_I(1), 0, 0,
                      fxSin(angleRad), 0, fxCos(angleRad), 0,
                      0, 0, 0, FX_FROM_I(1));
    }
    mat4x4 mat4x4::zRotation(const fixed& angleDeg) {
        fixed angleRad = FX_DEG_TO_RAD(angleDeg);
        return mat4x4(fxCos(angleRad), fxSin(angleRad), 0, 0,
                      -fxSin(angleRad), fxCos(angleRad), 0, 0,
                      0, 0, FX_FROM_I(1), 0,
                      0, 0, 0, FX_FROM_I(1));
    }
    mat4x4 mat4x4::projection(const fixed& fovDeg, const fixed& nearPlane, const fixed& farPlane, const fixed& width, const fixed& height) {
        fixed fovRad = FX_DEG_TO_RAD(fovDeg);
        fixed f = FX_DIV(FX_FROM_I(1), fxTan(fovRad >> 1));
        fixed q = FX_DIV(farPlane, FX_SUB(farPlane, nearPlane));
        return mat4x4(FX_MUL(FX_DIV(height, width), f), 0, 0, 0,
                      0, f, 0, 0,
                      0, 0, q, FX_FROM_I(1),
                      0, 0, FX_MUL(-nearPlane, q), 0);
    }
    mat4x4 mat4x4::transformation(const vector3F& pos, const vector3F& forward, const vector3F& up) {
        vector3F right = vector3F::cross(up, forward);
        return mat4x4(right.x, right.y, right.z, 0,
                      up.x, up.y, up.z, 0,
                      forward.x, forward.y, forward.z, 0,
                      pos.x, pos.y, pos.z, FX_FROM_I(1));
    }
    mat4x4 mat4x4::inverseTransformation(const vector3F& pos, const vector3F& forward, const vector3F& up) {
        vector3F right = vector3F::cross(up, forward);
        return mat4x4(right.x, up.x, forward.x, 0,
                      right.y, up.y, forward.y, 0,
                      right.z, up.z, forward.z, 0,
                      -vector3F::dot(pos, right), -vector3F::dot(pos, up), -vector3F::dot(pos, forward), FX_FROM_I(1));
    }
    #pragma endregion

    bool lineLineIntersectionPossible(const vector2F& a1, const vector2F& a2, const vector2F& b1, const vector2F& b2) {
        return FX_MUL((a1.x - a2.x), (b1.y - b2.y)) - FX_MUL((a1.y - a2.y), (b1.x - b2.x)) != 0;
    }

    vector2F lineLineIntersection(const vector2F& a1, const vector2F& a2, const vector2F& b1, const vector2F& b2) {
        fixed denominator = FX_MUL((a1.x - a2.x), (b1.y - b2.y)) - FX_MUL((a1.y - a2.y), (b1.x - b2.x));
        
        // Check if an intersection exists
        if(denominator == 0) {
            return vector2F();
        }

        // Calculate result
        vector2F result;
        result.x = FX_MUL(FX_MUL(a1.x, a2.y) - FX_MUL(a1.y, a2.x), b1.x - b2.x) - FX_MUL(FX_MUL(b1.x, b2.y) - FX_MUL(b1.y, b2.x), a1.x - a2.x);
        result.x = FX_DIV(result.x, denominator);
        result.y = FX_MUL(FX_MUL(a1.x, a2.y) - FX_MUL(a1.y, a2.x), b1.y - b2.y) - FX_MUL(FX_MUL(b1.x, b2.y) - FX_MUL(b1.y, b2.x), a1.y - a2.y);
        result.y = FX_DIV(result.y, denominator);
        return result;
    }
}