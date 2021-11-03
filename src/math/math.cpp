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
    #pragma region f
    float vector2::magnitude() const {
        return sqrt(x * x + y * y);
    }
    vector2 vector2::normalized() const {
        return *this / magnitude();
    }

    vector2::operator vector3() const { return vector3(x, y, 0); }
    vector2::operator vector4() const { return vector4(x, y, 0, 1); }
    vector2::operator vector2FX() const { return vector2FX(FX_FROM_F(x), FX_FROM_F(y)); }
    vector2::operator vector3FX() const { return vector3FX(FX_FROM_F(x), FX_FROM_F(y), 0); }
    vector2::operator vector4FX() const { return vector4FX(FX_FROM_F(x), FX_FROM_F(y), 0, FX_FROM_I(1)); }
    vector2::operator vector2I() const { return vector2I(x, y); }
    vector2::operator vector3I() const { return vector3I(x, y, 0); }
    vector2::operator vector4I() const { return vector4I(x, y, 0, 1); }

    float vector3::magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }
    vector3 vector3::normalized() const {
        return *this / magnitude();
    }
    float vector3::dot(const vector3& a, const vector3& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
    vector3 vector3::cross(const vector3& a, const vector3& b) {
        return vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
    }
    
    vector3::operator vector2() const { return vector2(x, y); }
    vector3::operator vector4() const { return vector4(x, y, z, 1); }
    vector3::operator vector2FX() const { return vector2FX(FX_FROM_F(x), FX_FROM_F(y)); }
    vector3::operator vector3FX() const { return vector3FX(FX_FROM_F(x), FX_FROM_F(y), FX_FROM_F(z)); }
    vector3::operator vector4FX() const { return vector4FX(FX_FROM_F(x), FX_FROM_F(y), FX_FROM_F(z), FX_FROM_I(1)); }
    vector3::operator vector2I() const { return vector2I(x, y); }
    vector3::operator vector3I() const { return vector3I(x, y, z); }
    vector3::operator vector4I() const { return vector4I(x, y, z, 1); }

    vector4::operator vector2() const { return vector2(x, y); }
    vector4::operator vector3() const { return vector3(x, y, z); }
    vector4::operator vector2FX() const { return vector2FX(FX_FROM_F(x), FX_FROM_F(y)); }
    vector4::operator vector3FX() const { return vector3FX(FX_FROM_F(x), FX_FROM_F(y), FX_FROM_F(z)); }
    vector4::operator vector4FX() const { return vector4FX(FX_FROM_F(x), FX_FROM_F(y), FX_FROM_F(z), FX_FROM_F(w)); }
    vector4::operator vector2I() const { return vector2I(x, y); }
    vector4::operator vector3I() const { return vector3I(x, y, z); }
    vector4::operator vector4I() const { return vector4I(x, y, z, w); }
    #pragma endregion

    #pragma region fx
    fixed vector2FX::magnitude() const {
        return fxSqrt(FX_ADD(FX_MUL(x, x), FX_MUL(y, y)));
    }
    vector2FX vector2FX::normalized() const {
        return *this / magnitude();
    }

    vector2FX::operator vector3FX() const { return vector3FX(x, y, 0); }
    vector2FX::operator vector4FX() const { return vector4FX(x, y, 0, FX_FROM_I(1)); }
    vector2FX::operator vector2() const { return vector2(FX_TO_F(x), FX_TO_F(y)); }
    vector2FX::operator vector3() const { return vector3(FX_TO_F(x), FX_TO_F(y), 0); }
    vector2FX::operator vector4() const { return vector4(FX_TO_F(x), FX_TO_F(y), 0, 1); }
    vector2FX::operator vector2I() const { return vector2I(FX_TO_I(x), FX_TO_I(y)); }
    vector2FX::operator vector3I() const { return vector3I(FX_TO_I(x), FX_TO_I(y), 0); }
    vector2FX::operator vector4I() const { return vector4I(FX_TO_I(x), FX_TO_I(y), 0, 1); }

    fixed vector3FX::magnitude() const {
        return fxSqrt(FX_ADD(FX_ADD(FX_MUL(x, x), FX_MUL(y, y)), FX_MUL(z, z)));
    }
    vector3FX vector3FX::normalized() const {
        return *this / magnitude();
    }
    fixed vector3FX::dot(const vector3FX& a, const vector3FX& b) {
        return FX_ADD(FX_ADD(FX_MUL(a.x, b.x), FX_MUL(a.y, b.y)), FX_MUL(a.z, b.z));
    }
    vector3FX vector3FX::cross(const vector3FX& a, const vector3FX& b) {
        return vector3FX(FX_SUB(FX_MUL(a.y, b.z), FX_MUL(a.z, b.y)), FX_SUB(FX_MUL(a.z, b.x), FX_MUL(a.x, b.z)), FX_SUB(FX_MUL(a.x, b.y), FX_MUL(a.y, b.x)));
    }
    
    vector3FX::operator vector2FX() const { return vector2FX(x, y); }
    vector3FX::operator vector4FX() const { return vector4FX(x, y, z, FX_FROM_I(1)); }
    vector3FX::operator vector2() const { return vector2(FX_TO_F(x), FX_TO_F(y)); }
    vector3FX::operator vector3() const { return vector3(FX_TO_F(x), FX_TO_F(y), FX_TO_F(z)); }
    vector3FX::operator vector4() const { return vector4(FX_TO_F(x), FX_TO_F(y), FX_TO_F(z), 1); }
    vector3FX::operator vector2I() const { return vector2I(FX_TO_I(x), FX_TO_I(y)); }
    vector3FX::operator vector3I() const { return vector3I(FX_TO_I(x), FX_TO_I(y), FX_TO_I(z)); }
    vector3FX::operator vector4I() const { return vector4I(FX_TO_I(x), FX_TO_I(y), FX_TO_I(z), 1); }

    vector4FX::operator vector2FX() const { return vector2FX(x, y); }
    vector4FX::operator vector3FX() const { return vector3FX(x, y, z); }
    vector4FX::operator vector2() const { return vector2(FX_TO_F(x), FX_TO_F(y)); }
    vector4FX::operator vector3() const { return vector3(FX_TO_F(x), FX_TO_F(y), FX_TO_F(z)); }
    vector4FX::operator vector4() const { return vector4(FX_TO_F(x), FX_TO_F(y), FX_TO_F(z), FX_TO_F(w)); }
    vector4FX::operator vector2I() const { return vector2I(FX_TO_I(x), FX_TO_I(y)); }
    vector4FX::operator vector3I() const { return vector3I(FX_TO_I(x), FX_TO_I(y), FX_TO_I(z)); }
    vector4FX::operator vector4I() const { return vector4I(FX_TO_I(x), FX_TO_I(y), FX_TO_I(z), FX_TO_I(w)); }
    #pragma endregion

    #pragma region i
    vector2I::operator vector3I() const { return vector3I(x, y, 0); }
    vector2I::operator vector4I() const { return vector4I(x, y, 0, 1); }
    vector2I::operator vector2() const { return vector2(x, y); }
    vector2I::operator vector3() const { return vector3(x, y, 0); }
    vector2I::operator vector4() const { return vector4(x, y, 0, 1); }
    vector2I::operator vector2FX() const { return vector2FX(FX_FROM_I(x), FX_FROM_I(y)); }
    vector2I::operator vector3FX() const { return vector3FX(FX_FROM_I(x), FX_FROM_I(y), 0); }
    vector2I::operator vector4FX() const { return vector4FX(FX_FROM_I(x), FX_FROM_I(y), 0, FX_FROM_I(1)); }
    
    vector3I::operator vector2I() const { return vector2I(x, y); }
    vector3I::operator vector4I() const { return vector4I(x, y, z, 1); }
    vector3I::operator vector2() const { return vector2(x, y); }
    vector3I::operator vector3() const { return vector3(x, y, z); }
    vector3I::operator vector4() const { return vector4(x, y, z, 1); }
    vector3I::operator vector2FX() const { return vector2FX(FX_FROM_I(x), FX_FROM_I(y)); }
    vector3I::operator vector3FX() const { return vector3FX(FX_FROM_I(x), FX_FROM_I(y), FX_FROM_I(z)); }
    vector3I::operator vector4FX() const { return vector4FX(FX_FROM_I(x), FX_FROM_I(y), FX_FROM_I(z), FX_FROM_I(1)); }
    
    vector4I::operator vector2I() const { return vector2I(x, y); }
    vector4I::operator vector3I() const { return vector3I(x, y, z); }
    vector4I::operator vector2() const { return vector2(x, y); }
    vector4I::operator vector3() const { return vector3(x, y, z); }
    vector4I::operator vector4() const { return vector4(x, y, z, w); }
    vector4I::operator vector2FX() const { return vector2FX(FX_FROM_I(x), FX_FROM_I(y)); }
    vector4I::operator vector3FX() const { return vector3FX(FX_FROM_I(x), FX_FROM_I(y), FX_FROM_I(z)); }
    vector4I::operator vector4FX() const { return vector4FX(FX_FROM_I(x), FX_FROM_I(y), FX_FROM_I(z), FX_FROM_I(w)); }
    #pragma endregion
    #pragma endregion

    #pragma region matrix
    #pragma region f
    mat4x4::mat4x4(const float& p00, const float& p10, const float& p20, const float& p30,
               const float& p01, const float& p11, const float& p21, const float& p31,
               const float& p02, const float& p12, const float& p22, const float& p32,
               const float& p03, const float& p13, const float& p23, const float& p33)
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
    
    vector4 mat4x4::operator *(const vector4& second) const
    {
        vector4 result;
        result.x = m[0][0] * second.x + m[0][1] * second.y + m[0][2] * second.z + m[0][3] * second.w;
        result.y = m[1][0] * second.x + m[1][1] * second.y + m[1][2] * second.z + m[1][3] * second.w;
        result.z = m[2][0] * second.x + m[2][1] * second.y + m[2][2] * second.z + m[2][3] * second.w;
        result.w = m[3][0] * second.x + m[3][1] * second.y + m[3][2] * second.z + m[3][3] * second.w;
        return result;
    }

    mat4x4 mat4x4::xRotation(const float& angleDeg) {
        float angleRad = angleDeg * DEG_TO_RAD;
        return mat4x4(1, 0, 0, 0,
                      0, cos(angleRad), sin(angleRad), 0,
                      0, -sin(angleRad), cos(angleRad), 0,
                      0, 0, 0, 1);
    }
    mat4x4 mat4x4::yRotation(const float& angleDeg) {
        float angleRad = angleDeg * DEG_TO_RAD;
        return mat4x4(cos(angleRad), 0, -sin(angleRad), 0,
                      0, 1, 0, 0,
                      sin(angleRad), 0, cos(angleRad), 0,
                      0, 0, 0, 1);
    }
    mat4x4 mat4x4::zRotation(const float& angleDeg) {
        float angleRad = angleDeg * DEG_TO_RAD;
        return mat4x4(cos(angleRad), sin(angleRad), 0, 0,
                      -sin(angleRad), cos(angleRad), 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1);
    }
    mat4x4 mat4x4::projection(const float& fovDeg, const float& nearPlane, const float& farPlane, const float& width, const float& height) {
        float fovRad = fovDeg * DEG_TO_RAD;
        float f = 1 / tan(fovRad / 2);
        float q = farPlane / (farPlane - nearPlane);
        return mat4x4(height / width * f, 0, 0, 0,
                      0, f, 0, 0,
                      0, 0, q, 1,
                      0, 0, -nearPlane * q, 0);
    }
    mat4x4 mat4x4::transformation(const vector3& pos, const vector3& forward, const vector3& up) {
        vector3 right = vector3::cross(up, forward);
        return mat4x4(right.x, right.y, right.z, 0,
                      up.x, up.y, up.z, 0,
                      forward.x, forward.y, forward.z, 0,
                      pos.x, pos.y, pos.z, 1);
    }
    mat4x4 mat4x4::inverseTransformation(const vector3& pos, const vector3& forward, const vector3& up) {
        vector3 right = vector3::cross(up, forward);
        return mat4x4(right.x, up.x, forward.x, 0,
                      right.y, up.y, forward.y, 0,
                      right.z, up.z, forward.z, 0,
                      -vector3::dot(pos, right), -vector3::dot(pos, up), -vector3::dot(pos, forward), 1);
    }
    #pragma endregion

    #pragma region fx
    mat4x4FX::mat4x4FX(const fixed& p00, const fixed& p10, const fixed& p20, const fixed& p30,
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
    
    vector4FX mat4x4FX::operator *(const vector4FX& second) const
    {
        vector4FX result;
        result.x = FX_ADD(FX_ADD(FX_MUL(m[0][0], second.x), FX_MUL(m[0][1], second.y)), FX_ADD(FX_MUL(m[0][2], second.z), FX_MUL(m[0][3], second.w)));
        result.y = FX_ADD(FX_ADD(FX_MUL(m[1][0], second.x), FX_MUL(m[1][1], second.y)), FX_ADD(FX_MUL(m[1][2], second.z), FX_MUL(m[1][3], second.w)));
        result.z = FX_ADD(FX_ADD(FX_MUL(m[2][0], second.x), FX_MUL(m[2][1], second.y)), FX_ADD(FX_MUL(m[2][2], second.z), FX_MUL(m[2][3], second.w)));
        result.w = FX_ADD(FX_ADD(FX_MUL(m[3][0], second.x), FX_MUL(m[3][1], second.y)), FX_ADD(FX_MUL(m[3][2], second.z), FX_MUL(m[3][3], second.w)));
        return result;
    }

    mat4x4FX mat4x4FX::xRotation(const fixed& angleDeg) {
        fixed angleRad = FX_DEG_TO_RAD(angleDeg);
        return mat4x4FX(FX_FROM_I(1), 0, 0, 0,
                      0, fxCos(angleRad), fxSin(angleRad), 0,
                      0, -fxSin(angleRad), fxCos(angleRad), 0,
                      0, 0, 0, FX_FROM_I(1));
    }
    mat4x4FX mat4x4FX::yRotation(const fixed& angleDeg) {
        fixed angleRad = FX_DEG_TO_RAD(angleDeg);
        return mat4x4FX(fxCos(angleRad), 0, -fxSin(angleRad), 0,
                      0, FX_FROM_I(1), 0, 0,
                      fxSin(angleRad), 0, fxCos(angleRad), 0,
                      0, 0, 0, FX_FROM_I(1));
    }
    mat4x4FX mat4x4FX::zRotation(const fixed& angleDeg) {
        fixed angleRad = FX_DEG_TO_RAD(angleDeg);
        return mat4x4FX(fxCos(angleRad), fxSin(angleRad), 0, 0,
                      -fxSin(angleRad), fxCos(angleRad), 0, 0,
                      0, 0, FX_FROM_I(1), 0,
                      0, 0, 0, FX_FROM_I(1));
    }
    mat4x4FX mat4x4FX::projection(const fixed& fovDeg, const fixed& nearPlane, const fixed& farPlane, const fixed& width, const fixed& height) {
        fixed fovRad = FX_DEG_TO_RAD(fovDeg);
        fixed f = FX_DIV(FX_FROM_I(1), fxTan(fovRad >> 1));
        fixed q = FX_DIV(farPlane, FX_SUB(farPlane, nearPlane));
        return mat4x4FX(FX_MUL(FX_DIV(height, width), f), 0, 0, 0,
                      0, f, 0, 0,
                      0, 0, q, FX_FROM_I(1),
                      0, 0, FX_MUL(-nearPlane, q), 0);
    }
    mat4x4FX mat4x4FX::transformation(const vector3FX& pos, const vector3FX& forward, const vector3FX& up) {
        vector3FX right = vector3FX::cross(up, forward);
        return mat4x4FX(right.x, right.y, right.z, 0,
                      up.x, up.y, up.z, 0,
                      forward.x, forward.y, forward.z, 0,
                      pos.x, pos.y, pos.z, FX_FROM_I(1));
    }
    mat4x4FX mat4x4FX::inverseTransformation(const vector3FX& pos, const vector3FX& forward, const vector3FX& up) {
        vector3FX right = vector3FX::cross(up, forward);
        return mat4x4FX(right.x, up.x, forward.x, 0,
                      right.y, up.y, forward.y, 0,
                      right.z, up.z, forward.z, 0,
                      -vector3FX::dot(pos, right), -vector3FX::dot(pos, up), -vector3FX::dot(pos, forward), FX_FROM_I(1));
    }
    #pragma endregion
    #pragma endregion

    #pragma region quaternion
    void quaternion::normalize() {
        float magnitude = sqrt(w*w + x*x + y*y + z*z);
        float multiplier = 1 / magnitude;
        w *= multiplier;
        x *= multiplier;
        y *= multiplier;
        z *= multiplier;
    }
    
    quaternion::quaternion(const float& angle, vector3FX axis) {
        w = cos(angle * DEG_TO_RAD / 2);

        axis = axis.normalized();
        float vMultiplier = sin(angle * DEG_TO_RAD / 2);
        x = FX_TO_F(axis.x) * vMultiplier;
        y = FX_TO_F(axis.y) * vMultiplier;
        z = FX_TO_F(axis.z) * vMultiplier;
    }

    vector3FX quaternion::rotateVector(const vector3FX& vector) const {
        quaternion vectorQ(0, FX_TO_F(vector.x), FX_TO_F(vector.y), FX_TO_F(vector.z));
        vectorQ = *this * vectorQ * this->inverse();
        return vectorQ.xyz();
    }
    
    quaternion quaternion::operator *(const quaternion& second) const {
        vector3 vFirst(x, y, z), vSecond(second.x, second.y, second.z);
        quaternion result;

        result.w = second.w * w - vector3::dot(vSecond, vFirst);

        vector3 vResult = vFirst * second.w + vSecond * w + vector3::cross(vFirst, vSecond);
        result.x = vResult.x;
        result.y = vResult.y;
        result.z = vResult.z;

        result.normalize();
        return result;
    }
    #pragma endregion

    bool lineLineIntersectionPossible(const vector2FX& a1, const vector2FX& a2, const vector2FX& b1, const vector2FX& b2) {
        return FX_MUL((a1.x - a2.x), (b1.y - b2.y)) - FX_MUL((a1.y - a2.y), (b1.x - b2.x)) != 0;
    }

    vector2FX lineLineIntersection(const vector2FX& a1, const vector2FX& a2, const vector2FX& b1, const vector2FX& b2) {
        fixed denominator = FX_MUL((a1.x - a2.x), (b1.y - b2.y)) - FX_MUL((a1.y - a2.y), (b1.x - b2.x));
        
        // Check if an intersection exists
        if(denominator == 0) {
            return vector2FX();
        }

        // Calculate result
        vector2FX result;
        result.x = FX_MUL(FX_MUL(a1.x, a2.y) - FX_MUL(a1.y, a2.x), b1.x - b2.x) - FX_MUL(FX_MUL(b1.x, b2.y) - FX_MUL(b1.y, b2.x), a1.x - a2.x);
        result.x = FX_DIV(result.x, denominator);
        result.y = FX_MUL(FX_MUL(a1.x, a2.y) - FX_MUL(a1.y, a2.x), b1.y - b2.y) - FX_MUL(FX_MUL(b1.x, b2.y) - FX_MUL(b1.y, b2.x), a1.y - a2.y);
        result.y = FX_DIV(result.y, denominator);
        return result;
    }
}