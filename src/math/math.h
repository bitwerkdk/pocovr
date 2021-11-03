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
    struct vector2;
    struct vector3;
    struct vector4;

    struct vector2FX;
    struct vector3FX;
    struct vector4FX;

    struct vector2I;
    struct vector3I;
    struct vector4I;
    #pragma region f

    struct vector2 {
        float x = 0, y = 0;

        float magnitude() const;
        vector2 normalized() const;

        inline vector2() { }
        inline vector2(const float& x, const float& y) : x(x), y(y) { }

        inline vector2 operator +(const vector2& second) const { return vector2(x + second.x, y + second.y); }
        inline void operator +=(const vector2& second) { x += second.x; y += second.y; }
        inline vector2 operator -(const vector2& second) const { return vector2(x - second.x, y - second.y); }
        inline void operator -=(const vector2& second) { x -= second.x; y -= second.y; }
        inline vector2 operator *(const float& second) const { return vector2(x * second, y * second); }
        inline void operator *=(const float& second) { x *= second; y *= second; }
        inline vector2 operator /(const float& second) const { return vector2(x / second, y / second); }
        inline void operator /=(const float& second) { x /= second; y /= second; }

        operator vector3() const;
        operator vector4() const;
        operator vector2FX() const;
        operator vector3FX() const;
        operator vector4FX() const;
        operator vector2I() const;
        operator vector3I() const;
        operator vector4I() const;
    };

    struct vector3 {
        float x = 0, y = 0, z = 0;

        float magnitude() const;
        vector3 normalized() const;

        inline vector3() { }
        inline vector3(const float& x, const float& y, const float& z) : x(x), y(y), z(z) { }

        static vector3 forward() { return vector3(0, 0, 1); }
        static vector3 up() { return vector3(0, 1, 0); }
        static vector3 right() { return vector3(1, 0, 0); }

        inline vector3 operator +(const vector3& second) const { return vector3(x + second.x, y + second.y, z + second.z); }
        inline void operator +=(const vector3& second) { x += second.x; y += second.y; z += second.z; }
        inline vector3 operator -(const vector3& second) const { return vector3(x - second.x, y - second.y, z - second.z); }
        inline void operator -=(const vector3& second) { x -= second.x; y -= second.y; z -= second.z; }
        inline vector3 operator *(const float& second) const { return vector3(x * second, y * second, z * second); }
        inline void operator *=(const float& second) { x *= second; y *= second; z *= second; }
        inline vector3 operator /(const float& second) const { return vector3(x / second, y / second, z / second); }
        inline void operator /=(const float& second) { x /= second; y /= second; z /= second; }

        static float dot(const vector3& a, const vector3& b);
        static vector3 cross(const vector3& a, const vector3& b);
        
        operator vector2() const;
        operator vector4() const;
        operator vector2FX() const;
        operator vector3FX() const;
        operator vector4FX() const;
        operator vector2I() const;
        operator vector3I() const;
        operator vector4I() const;
    };

    struct vector4 {
        float x = 0, y = 0, z = 0, w = 1;

        inline vector4() { }
        inline vector4(const float& x, const float& y, const float& z, const float& w) : x(x), y(y), z(z), w(w) { }

        inline vector4 operator +(const vector4& second) const { return vector4(x + second.x, y + second.y, z + second.z, w + second.w); }
        inline void operator +=(const vector4& second) { x += second.x; y += second.y; z += second.z; w += second.w; }
        inline vector4 operator -(const vector4& second) const { return vector4(x - second.x, y - second.y, z - second.z, w - second.w); }
        inline void operator -=(const vector4& second) { x -= second.x; y -= second.y; z -= second.z; w -= second.w; }
        inline vector4 operator *(const float& second) const { return vector4(x * second, y * second, z * second, w * second); }
        inline void operator *=(const float& second) { x *= second; y *= second; z *= second; w *= second; }
        inline vector4 operator /(const float& second) const { return vector4(x / second, y / second, z / second, w / second); }
        inline void operator /=(const float& second) { x /= second; y /= second; z /= second; w /= second; }

        operator vector2() const;
        operator vector3() const;
        operator vector2FX() const;
        operator vector3FX() const;
        operator vector4FX() const;
        operator vector2I() const;
        operator vector3I() const;
        operator vector4I() const;
    };
    #pragma endregion

    #pragma region fx
    struct vector2FX;
    struct vector3FX;
    struct vector4FX;

    struct vector2FX {
        fixed x = 0, y = 0;

        fixed magnitude() const;
        vector2FX normalized() const;

        inline vector2FX() { }
        inline vector2FX(const fixed& x, const fixed& y) : x(x), y(y) { }

        inline vector2FX operator +(const vector2FX& second) const { return vector2FX(FX_ADD(x, second.x), FX_ADD(y, second.y)); }
        inline void operator +=(const vector2FX& second) { x = FX_ADD(x, second.x); y = FX_ADD(y, second.y); }
        inline vector2FX operator -(const vector2FX& second) const { return vector2FX(FX_SUB(x, second.x), FX_SUB(y, second.y)); }
        inline void operator -=(const vector2FX& second) { x = FX_SUB(x, second.x); y = FX_SUB(y, second.y); }
        inline vector2FX operator *(const fixed& second) const { return vector2FX(FX_MUL(x, second), FX_MUL(y, second)); }
        inline void operator *=(const fixed& second) { x = FX_MUL(x, second); y = FX_MUL(y, second); }
        inline vector2FX operator /(const fixed& second) const { return vector2FX(FX_DIV(x, second), FX_DIV(y, second)); }
        inline void operator /=(const fixed& second) { x = FX_DIV(x, second); y = FX_DIV(y, second); }

        operator vector3FX() const;
        operator vector4FX() const;
        operator vector2() const;
        operator vector3() const;
        operator vector4() const;
        operator vector2I() const;
        operator vector3I() const;
        operator vector4I() const;
    };

    struct vector3FX {
        fixed x = 0, y = 0, z = 0;

        fixed magnitude() const;
        vector3FX normalized() const;

        inline vector3FX() { }
        inline vector3FX(const fixed& x, const fixed& y, const fixed& z) : x(x), y(y), z(z) { }

        static vector3FX forward() { return vector3FX(0, 0, FX_FROM_F(1)); }
        static vector3FX up() { return vector3FX(0, FX_FROM_F(1), 0); }
        static vector3FX right() { return vector3FX(FX_FROM_F(1), 0, 0); }

        inline vector3FX operator +(const vector3FX& second) const { return vector3FX(FX_ADD(x, second.x), FX_ADD(y, second.y), FX_ADD(z, second.z)); }
        inline void operator +=(const vector3FX& second) { x = FX_ADD(x, second.x); y = FX_ADD(y, second.y); z = FX_ADD(z, second.z); }
        inline vector3FX operator -(const vector3FX& second) const { return vector3FX(FX_SUB(x, second.x), FX_SUB(y, second.y), FX_SUB(z, second.z)); }
        inline void operator -=(const vector3FX& second) { x = FX_SUB(x, second.x); y = FX_SUB(y, second.y); z = FX_SUB(z, second.z); }
        inline vector3FX operator *(const fixed& second) const { return vector3FX(FX_MUL(x, second), FX_MUL(y, second), FX_MUL(z, second)); }
        inline void operator *=(const fixed& second) { x = FX_MUL(x, second); y = FX_MUL(y, second); z = FX_MUL(z, second); }
        inline vector3FX operator /(const fixed& second) const { return vector3FX(FX_DIV(x, second), FX_DIV(y, second), FX_DIV(z, second)); }
        inline void operator /=(const fixed& second) { x = FX_DIV(x, second); y = FX_DIV(y, second); z = FX_DIV(z, second); }

        static fixed dot(const vector3FX& a, const vector3FX& b);
        static vector3FX cross(const vector3FX& a, const vector3FX& b);
        
        operator vector2FX() const;
        operator vector4FX() const;
        operator vector2() const;
        operator vector3() const;
        operator vector4() const;
        operator vector2I() const;
        operator vector3I() const;
        operator vector4I() const;
    };

    struct vector4FX {
        fixed x = 0, y = 0, z = 0, w = FX_FROM_I(1);

        inline vector4FX() { }
        inline vector4FX(const fixed& x, const fixed& y, const fixed& z, const fixed& w) : x(x), y(y), z(z), w(w) { }

        inline vector4FX operator +(const vector4FX& second) const { return vector4FX(FX_ADD(x, second.x), FX_ADD(y, second.y), FX_ADD(z, second.z), FX_ADD(w, second.w)); }
        inline void operator +=(const vector4FX& second) { x = FX_ADD(x, second.x); y = FX_ADD(y, second.y); z = FX_ADD(z, second.z); w = FX_ADD(w, second.w); }
        inline vector4FX operator -(const vector4FX& second) const { return vector4FX(FX_SUB(x, second.x), FX_SUB(y, second.y), FX_SUB(z, second.z), FX_SUB(w, second.w)); }
        inline void operator -=(const vector4FX& second) { x = FX_SUB(x, second.x); y = FX_SUB(y, second.y); z = FX_SUB(z, second.z); w = FX_SUB(w, second.w); }
        inline vector4FX operator *(const fixed& second) const { return vector4FX(FX_MUL(x, second), FX_MUL(y, second), FX_MUL(z, second), FX_MUL(w, second)); }
        inline void operator *=(const fixed& second) { x = FX_MUL(x, second); y = FX_MUL(y, second); z = FX_MUL(z, second); w = FX_MUL(w, second); }
        inline vector4FX operator /(const fixed& second) const { return vector4FX(FX_DIV(x, second), FX_DIV(y, second), FX_DIV(z, second), FX_DIV(w, second)); }
        inline void operator /=(const fixed& second) { x = FX_DIV(x, second); y = FX_DIV(y, second); z = FX_DIV(z, second); w = FX_DIV(w, second); }

        operator vector2FX() const;
        operator vector3FX() const;
        operator vector2() const;
        operator vector3() const;
        operator vector4() const;
        operator vector2I() const;
        operator vector3I() const;
        operator vector4I() const;
    };
    #pragma endregion

    #pragma region i
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
        
        operator vector3I() const;
        operator vector4I() const;
        operator vector2() const;
        operator vector3() const;
        operator vector4() const;
        operator vector2FX() const;
        operator vector3FX() const;
        operator vector4FX() const;
    };
    
    struct vector3I {
        int x = 0, y = 0, z = 0;

        inline vector3I() { }
        inline vector3I(const int& x, const int& y, const int& z) : x(x), y(y), z(z) { }

        inline vector3I operator +(const vector3I& second) const { return vector3I(x + second.x, y + second.y, z + second.z); }
        inline void operator +=(const vector3I& second) { x += second.x; y += second.y; z += second.z; }
        inline vector3I operator -(const vector3I& second) const { return vector3I(x - second.x, y - second.y, z - second.z); }
        inline void operator -=(const vector3I& second) { x -= second.x; y -= second.y; z -= second.z; }
        inline vector3I operator *(const int& second) const { return vector3I(x * second, y * second, z * second); }
        inline void operator *=(const int& second) { x *= second; y *= second; z *= second; }
        inline vector3I operator /(const int& second) const { return vector3I(x / second, y / second, z / second); }
        inline void operator /=(const int& second) { x /= second; y /= second; z /= second; }
        
        operator vector2I() const;
        operator vector4I() const;
        operator vector2() const;
        operator vector3() const;
        operator vector4() const;
        operator vector2FX() const;
        operator vector3FX() const;
        operator vector4FX() const;
    };
    
    struct vector4I {
        int x = 0, y = 0, z = 0, w = 0;

        inline vector4I() { }
        inline vector4I(const int& x, const int& y, const int& z, const int& w) : x(x), y(y), z(z), w(w) { }

        inline vector4I operator +(const vector4I& second) const { return vector4I(x + second.x, y + second.y, z + second.z, w + second.w); }
        inline void operator +=(const vector4I& second) { x += second.x; y += second.y; z += second.z; w += second.w; }
        inline vector4I operator -(const vector4I& second) const { return vector4I(x - second.x, y - second.y, z - second.z, w - second.w); }
        inline void operator -=(const vector4I& second) { x -= second.x; y -= second.y; z -= second.z; w -= second.w; }
        inline vector4I operator *(const int& second) const { return vector4I(x * second, y * second, z * second, w * second); }
        inline void operator *=(const int& second) { x *= second; y *= second; z *= second; w *= second; }
        inline vector4I operator /(const int& second) const { return vector4I(x / second, y / second, z / second, w / second); }
        inline void operator /=(const int& second) { x /= second; y /= second; z /= second; w /= second; }
        
        operator vector2I() const;
        operator vector3I() const;
        operator vector2() const;
        operator vector3() const;
        operator vector4() const;
        operator vector2FX() const;
        operator vector3FX() const;
        operator vector4FX() const;
    };
    #pragma endregion
    #pragma endregion

    #pragma region matrix
    #pragma region f
    struct mat4x4 {
        float m[4][4] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };

        mat4x4() { }
        mat4x4(const float& p00, const float& p10, const float& p20, const float& p30,
               const float& p01, const float& p11, const float& p21, const float& p31,
               const float& p02, const float& p12, const float& p22, const float& p32,
               const float& p03, const float& p13, const float& p23, const float& p33);

        vector4 operator *(const vector4& second) const;

        static mat4x4 xRotation(const float& angle);
        static mat4x4 yRotation(const float& angle);
        static mat4x4 zRotation(const float& angle);
        static mat4x4 projection(const float& fov, const float& nearPlane, const float& farPlane, const float& width, const float& height);
        static mat4x4 transformation(const vector3& pos, const vector3& forward, const vector3& up);
        static mat4x4 inverseTransformation(const vector3& pos, const vector3& forward, const vector3& up);
    };
    #pragma endregion

    #pragma region fx
    struct mat4x4FX {
        fixed m[4][4] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };

        mat4x4FX() { }
        mat4x4FX(const fixed& p00, const fixed& p10, const fixed& p20, const fixed& p30,
               const fixed& p01, const fixed& p11, const fixed& p21, const fixed& p31,
               const fixed& p02, const fixed& p12, const fixed& p22, const fixed& p32,
               const fixed& p03, const fixed& p13, const fixed& p23, const fixed& p33);

        vector4FX operator *(const vector4FX& second) const;

        static mat4x4FX xRotation(const fixed& angle);
        static mat4x4FX yRotation(const fixed& angle);
        static mat4x4FX zRotation(const fixed& angle);
        static mat4x4FX projection(const fixed& fov, const fixed& nearPlane, const fixed& farPlane, const fixed& width, const fixed& height);
        static mat4x4FX transformation(const vector3FX& pos, const vector3FX& forward, const vector3FX& up);
        static mat4x4FX inverseTransformation(const vector3FX& pos, const vector3FX& forward, const vector3FX& up);
    };
    #pragma endregion
    #pragma endregion

    #pragma region quaternion
    struct quaternion {
        float w = 1, x = 0, y = 0, z = 0;

        void normalize();

        inline quaternion() { }
        inline quaternion(const float& w, const float& x,  const float& y,  const float& z) : w(w), x(x), y(y), z(z) { }
        quaternion(const float& angle, vector3FX axis);

        vector3FX rotateVector(const vector3FX& vector) const;
        inline quaternion inverse() const { return quaternion(w, -x, -y, -z); }
        inline vector3FX xyz() const { return vector3FX(FX_FROM_F(x), FX_FROM_F(y), FX_FROM_F(z)); }

        quaternion operator *(const quaternion& second) const;
        void operator *=(const quaternion& second) { *this = *this * second; }
    };
    #pragma endregion

    bool lineLineIntersectionPossible(const vector2FX& a1, const vector2FX& a2, const vector2FX& b1, const vector2FX& b2);

    vector2FX lineLineIntersection(const vector2FX& a1, const vector2FX& a2, const vector2FX& b1, const vector2FX& b2); 
}