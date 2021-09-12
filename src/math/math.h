#pragma once

namespace math {
    #pragma region fixed
    typedef long fixed;
    #define FX_PRECISION 8

    #define FX_ADD(a,b) (math::fixed)((math::fixed)(a) + (math::fixed)(b))
    #define FX_SUB(a,b) (math::fixed)((math::fixed)(a) - (math::fixed)(b))
    #define FX_MUL(a,b) (math::fixed)(((math::fixed)(a) * (math::fixed)(b)) >> FX_PRECISION)
    #define FX_DIV(a,b) (math::fixed)(((math::fixed)(a) << FX_PRECISION) / (math::fixed)(b))

    fixed fxPowUint(const fixed& base, const unsigned int& exponent);
    fixed fxSqrt(const fixed& x);
    fixed fxSin(const fixed& x);
    fixed fxCos(const fixed& x);
    fixed fxTan(const fixed& x);

    #define FX_FROM_I(x) ((math::fixed)(x) << FX_PRECISION)
    #define FX_TO_I(x) (((math::fixed)(x)) >> FX_PRECISION)
    #define FX_FROM_F(x) (math::fixed)((float)(x) * math::fxPowUint(2, FX_PRECISION))
    #define FX_TO_F(x) ((float)(x) / math::fxPowUint(2, FX_PRECISION))

    #define FX_DEG_TO_RAD(x) FX_MUL((math::fixed)(x), FX_FROM_F(0.0174533))
    #define FX_RAD_TO_DEG(x) FX_MUL((math::fixed)(x), FX_FROM_F(57.2957795))

    fixed fxMin(const fixed& a, const fixed& b);
    fixed fxMax(const fixed& a, const fixed& b);
    fixed fxClamp(const fixed& value, const fixed& min, const fixed& max);
    fixed fxLerp(const fixed& a, const fixed& b, const fixed& t);
    #pragma endregion

    #pragma region vector
    struct vector2F;
    struct vector3F;
    struct vector4F;

    struct vector2F {
        fixed x = 0, y = 0;

        fixed magnitude() const;
        vector2F normalized() const;

        inline vector2F() { }
        inline vector2F(const fixed& x, const fixed& y) : x(x), y(y) { }

        inline vector2F operator +(const vector2F& second) const { return vector2F(FX_ADD(x, second.x), FX_ADD(y, second.y)); }
        inline void operator +=(const vector2F& second) { x = FX_ADD(x, second.x); y = FX_ADD(y, second.y); }
        inline vector2F operator -(const vector2F& second) const { return vector2F(FX_SUB(x, second.x), FX_SUB(y, second.y)); }
        inline void operator -=(const vector2F& second) { x = FX_SUB(x, second.x); y = FX_SUB(y, second.y); }
        inline vector2F operator *(const fixed& second) const { return vector2F(FX_MUL(x, second), FX_MUL(y, second)); }
        inline void operator *=(const fixed& second) { x = FX_MUL(x, second); y = FX_MUL(y, second); }
        inline vector2F operator /(const fixed& second) const { return vector2F(FX_DIV(x, second), FX_DIV(y, second)); }
        inline void operator /=(const fixed& second) { x = FX_DIV(x, second); y = FX_DIV(y, second); }

        operator vector3F() const;
        operator vector4F() const;
    };

    struct vector2I {
        int x = 0, y = 0;

        inline vector2I() { }
        inline vector2I(const int& x, const int& y) : x(x), y(y) { }

        inline vector2I operator +(const vector2I& second) const { return vector2I(x + second.x, y + second.y); }
        inline void operator +=(const vector2I& second) { x += second.x; y += second.y; }
        inline vector2I operator -(const vector2I& second) const { return vector2I(x - second.x, y - second.y); }
        inline void operator -=(const vector2I& second) { x -= second.x; y -= second.y; }
        inline vector2I operator *(const int& second) const { return vector2I(x * second, y * second); }
        inline void operator *=(const int& second) { x *= second; y *= second; }
        inline vector2I operator /(const int& second) const { return vector2I(x / second, y / second); }
        inline void operator /=(const int& second) { x /= second; y /= second; }
    };

    struct vector3F {
        fixed x = 0, y = 0, z = 0;

        fixed magnitude() const;
        vector3F normalized() const;

        inline vector3F() { }
        inline vector3F(const fixed& x, const fixed& y, const fixed& z) : x(x), y(y), z(z) { }

        static vector3F forward() { return vector3F(0, 0, FX_FROM_F(1)); }
        static vector3F up() { return vector3F(0, FX_FROM_F(1), 0); }
        static vector3F right() { return vector3F(FX_FROM_F(1), 0, 0); }

        inline vector3F operator +(const vector3F& second) const { return vector3F(FX_ADD(x, second.x), FX_ADD(y, second.y), FX_ADD(z, second.z)); }
        inline void operator +=(const vector3F& second) { x = FX_ADD(x, second.x); y = FX_ADD(y, second.y); z = FX_ADD(z, second.z); }
        inline vector3F operator -(const vector3F& second) const { return vector3F(FX_SUB(x, second.x), FX_SUB(y, second.y), FX_SUB(z, second.z)); }
        inline void operator -=(const vector3F& second) { x = FX_SUB(x, second.x); y = FX_SUB(y, second.y); z = FX_SUB(z, second.z); }
        inline vector3F operator *(const fixed& second) const { return vector3F(FX_MUL(x, second), FX_MUL(y, second), FX_MUL(z, second)); }
        inline void operator *=(const fixed& second) { x = FX_MUL(x, second); y = FX_MUL(y, second); z = FX_MUL(z, second); }
        inline vector3F operator /(const fixed& second) const { return vector3F(FX_DIV(x, second), FX_DIV(y, second), FX_DIV(z, second)); }
        inline void operator /=(const fixed& second) { x = FX_DIV(x, second); y = FX_DIV(y, second); z = FX_DIV(z, second); }

        static fixed dot(const vector3F& a, const vector3F& b);
        static vector3F cross(const vector3F& a, const vector3F& b);
        
        operator vector2F() const;
        operator vector4F() const;
    };

    struct vector4F {
        fixed x = 0, y = 0, z = 0, w = FX_FROM_I(1);

        inline vector4F() { }
        inline vector4F(const fixed& x, const fixed& y, const fixed& z, const fixed& w) : x(x), y(y), z(z), w(w) { }

        inline vector4F operator +(const vector4F& second) const { return vector4F(FX_ADD(x, second.x), FX_ADD(y, second.y), FX_ADD(z, second.z), FX_ADD(w, second.w)); }
        inline void operator +=(const vector4F& second) { x = FX_ADD(x, second.x); y = FX_ADD(y, second.y); z = FX_ADD(z, second.z); w = FX_ADD(w, second.w); }
        inline vector4F operator -(const vector4F& second) const { return vector4F(FX_SUB(x, second.x), FX_SUB(y, second.y), FX_SUB(z, second.z), FX_SUB(w, second.w)); }
        inline void operator -=(const vector4F& second) { x = FX_SUB(x, second.x); y = FX_SUB(y, second.y); z = FX_SUB(z, second.z); w = FX_SUB(w, second.w); }
        inline vector4F operator *(const fixed& second) const { return vector4F(FX_MUL(x, second), FX_MUL(y, second), FX_MUL(z, second), FX_MUL(w, second)); }
        inline void operator *=(const fixed& second) { x = FX_MUL(x, second); y = FX_MUL(y, second); z = FX_MUL(z, second); w = FX_MUL(w, second); }
        inline vector4F operator /(const fixed& second) const { return vector4F(FX_DIV(x, second), FX_DIV(y, second), FX_DIV(z, second), FX_DIV(w, second)); }
        inline void operator /=(const fixed& second) { x = FX_DIV(x, second); y = FX_DIV(y, second); z = FX_DIV(z, second); w = FX_DIV(w, second); }

        operator vector2F() const;
        operator vector3F() const;
    };
    #pragma endregion

    #pragma region matrix
    struct mat4x4 {
        fixed m[4][4] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };

        mat4x4() { }
        mat4x4(const fixed& p00, const fixed& p10, const fixed& p20, const fixed& p30,
               const fixed& p01, const fixed& p11, const fixed& p21, const fixed& p31,
               const fixed& p02, const fixed& p12, const fixed& p22, const fixed& p32,
               const fixed& p03, const fixed& p13, const fixed& p23, const fixed& p33);

        vector4F operator *(const vector4F& second) const;

        static mat4x4 xRotation(const fixed& angle);
        static mat4x4 yRotation(const fixed& angle);
        static mat4x4 zRotation(const fixed& angle);
        static mat4x4 projection(const fixed& fov, const fixed& nearPlane, const fixed& farPlane, const fixed& width, const fixed& height);
        static mat4x4 transformation(const vector3F& pos, const vector3F& forward, const vector3F& up);
        static mat4x4 inverseTransformation(const vector3F& pos, const vector3F& forward, const vector3F& up);
    };
    #pragma endregion

    #pragma region quaternions
    struct quaternion {
        float w = 1, x = 0, y = 0, z = 0;

        void normalize();

        inline quaternion() { }
        inline quaternion(const float& w, const float& x,  const float& y,  const float& z) : w(w), x(x), y(y), z(z) { }
        quaternion(const float& angle, vector3F axis);

        vector3F rotateVector(const vector3F& vector) const;
        inline quaternion inverse() const { return quaternion(w, -x, -y, -z); }
        inline vector3F xyz() const { return vector3F(FX_FROM_F(x), FX_FROM_F(y), FX_FROM_F(z)); }

        quaternion operator *(const quaternion& second) const;
        void operator *=(const quaternion& second) { *this = *this * second; }
    };
    #pragma endregion

    bool lineLineIntersectionPossible(const vector2F& a1, const vector2F& a2, const vector2F& b1, const vector2F& b2);

    vector2F lineLineIntersection(const vector2F& a1, const vector2F& a2, const vector2F& b1, const vector2F& b2);
}