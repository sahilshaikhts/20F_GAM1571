#pragma once

namespace fw {

    class vec2
    {
    public:
        float x;
        float y;

        vec2() { x = 0; y = 0; }
        vec2(float nx, float ny) { x = nx; y = ny; }

        //OPERATOR OVELOADING
        
            vec2 operator+=(const vec2 & o) { x += o.x; y += o.y; return *this; }
            vec2 operator-=(const vec2 & o) { x -= o.x; y -= o.y; return *this; }
            vec2 operator/=(const vec2 & o) { x /= o.x; y /= o.y; return *this; }
            vec2 operator*=(const vec2 & o) { x *= o.x; y *= o.y; return *this; }

            vec2 operator+=(const float o) { x += o; y += o; return *this; }
            vec2 operator-=(const float o) { x -= o; y -= o; return *this; }
            vec2 operator/=(const float o) { x /= o; y /= o; return *this; }
            vec2 operator*=(const float o) { x *= o; y *= o; return *this; }

            vec2 operator*(const vec2 & o) { return vec2(x * o.x, y * o.x); }
            vec2 operator/(const vec2 & o) { return vec2(x / o.x, y / o.x); }
            vec2 operator+(const vec2 & o) { return vec2(x + o.x, y + o.y); }
            vec2 operator-(const vec2 & o) { return vec2(x - o.x, y - o.y); }

            vec2 operator*(const float o) { return vec2(x * o, y * o); }
            vec2 operator/(const float o) { return vec2(x / o, y / o); }
            vec2 operator+(const float o) { return vec2(x + o, y + o); }
            vec2 operator-(const float o) { return vec2(x - o, y - o); }
    


        float Magnitude() { return sqrt((x * x) + (y * y)); }
        float GetDistance(vec2 other) { vec2 diff(other.x - x, other.y - y); return diff.Magnitude(); }
        float DotProduct(vec2 other) { return(x * other.x + y * other.y); }
        vec2 GetNormalized() { return vec2(x / Magnitude(), y / Magnitude()); }
        vec2 Normalize() { x /= Magnitude(); y /= Magnitude(); }


    
    };

    class vec4
    {
    public:
        vec4() { x = 0; y = 0; z = 0; w = 0; }
        vec4(float nx, float ny, float nz, float nw) { x = nx; y = ny; z = nz; w = nw; }

        static const vec4 Red() { return vec4(1.0f, 0.0f, 0.0f, 1.0f); }
        static const vec4 Green() { return vec4(0.0f, 1.0f, 0.0f, 1.0f); }
        static const vec4 Blue() { return vec4(0.0f, 0.0f, 1.0f, 1.0f); }
        static const vec4 DarkBlue() { return vec4(0.0f, 0.0f, 0.3f, 1.0f); }
        static const vec4 White() { return vec4(1.0f, 1.0f, 1.0f, 1.0f); }
        static const vec4 Black() { return vec4(0.0f, 0.0f, 0.0f, 1.0f); }

    public:
        union
        {
            float x;
            float r;
        };
        union
        {
            float y;
            float g;
        };
        union
        {
            float z;
            float b;
        };
        union
        {
            float w;
            float a;
        };
    };

} // namespace fw
