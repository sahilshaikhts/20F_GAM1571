#pragma once
namespace  fw {
	class vec2
	{
	public:
		float x, y;

		vec2() :x(0), y(0) {}
		vec2(float aX, float aY) { Set(aX, aY); }

		void Set(float aX, float aY) { x = aX; y = aY; }
		

		void operator+=(const vec2& o) { x += o.x; y += o.y; }
		void operator-=(const vec2& o) { x -= o.x; y -= o.y; }
		void operator/=(const vec2& o) { x /= o.x; y /= o.y; }
		void operator*=(const vec2& o) { x *= o.x; y *= o.y; }

		vec2 operator*(const float o) { return vec2(x * o, y * o); }
		vec2 operator/(const float o) { return vec2(x / o, y / o); }
		vec2 operator+(const vec2 o) { return vec2(x + o.x, y + o.y); }
		vec2 operator-(const vec2 o) { return vec2(x - o.x, y - o.y); }

		float Magnitude() { return sqrt((x * x) + (y * y)); }
		float GetDistance(vec2 other) { vec2 diff(other.x - x, other.y - y); return diff.Magnitude(); }
		float DotProduct(vec2 other) { return(x * other.x + y * other.y); }
		vec2 GetNormalized() { return vec2(x / Magnitude(), y / Magnitude()); }
		vec2 Normalize() { float magn = Magnitude(); x =magn; y = magn; }
	
	};

	class vec4
	{
	public:
		union {
			float x;
			float r;
		};

		union {
			float y;
			float g;
		};
		union {
			float z;
			float b;
		};
		union {
			float w;
			float a;
		};


		vec4() :x(0), y(0),z(0),w(0) {}
		vec4(float aX, float aY, float aZ, float aW) { Set(aX, aY,aZ,aW); }

		static const vec4 White() { return vec4(1.0f, 1.0f, 1.0f, 1.0f); }
		static const vec4 Black() { return vec4(0.0f, 0.0f, 0.0f, 1.0f); }
		static const vec4 Red() { return vec4(1.0f, 0.0f, 0.0f, 1.0f); }
		static const vec4 Green() { return vec4(0.0f, 1.0f, 0.0f, 1.0f); }
		static const vec4 Blue() { return vec4(0.0f, 0.0f, 1.0f, 1.0f); }
		static const vec4 DarkGreen() { return vec4(.2f, .6f, .25f, 1); }
		
		void Set(float aX, float aY, float aZ, float aW) { x = aX; y = aY; z = aZ; w = aW; }

	};

}
