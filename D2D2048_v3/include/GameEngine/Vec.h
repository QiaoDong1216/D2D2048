#pragma once
#include <iostream>
#define PI 3.14159265

#define TO_SHU_COLORF(r, g, b, a) shu::color4f(r/255.,g/255.,b/255.,a/255.)
#define TO_D2D1_COLORF(r, g, b, a) D2D1::ColorF(r/255.,g/255.,b/255.,a/255.)

namespace shu
{
	// ��ά����
	class vec2f
	{
	public:
		float x, y;
		vec2f() : x(0.0f), y(0.0f) {}
		vec2f(float x, float y) : x(x), y(y) {}
		~vec2f() {}

		friend std::ostream& operator << (std::ostream& io, const vec2f& o) { std::cout << "x: " << o.x << " y: " << o.y; return io; }
		vec2f& operator >> (vec2f& o) { o.x = x; o.y = y; return o; }

		vec2f operator + (const vec2f& o) const { return vec2f(x + o.x, y + o.y); }
		vec2f operator - (const vec2f& o) const { return vec2f(x - o.x, y - o.y); }
		vec2f operator * (const vec2f& o) const { return vec2f(x * o.x, y * o.y); }
		vec2f operator / (const vec2f& o) const { return vec2f(x / o.x, y / o.y); }

		//vec2f& operator = (const vec2f& o) { x = o.x; y = o.y; return *this; }

		friend vec2f operator / (float o, const vec2f& t) { return vec2f(o / t.x, o / t.y); }
		friend vec2f operator / (const vec2f& o, float t) { return vec2f(o.x / t, o.y / t); }

		friend vec2f operator * (float o, const vec2f& t) { return vec2f(o * t.x, o * t.y); }
		friend vec2f operator * (const vec2f& o, float t) { return vec2f(o.x * t, o.y * t); }

		vec2f& operator += (const vec2f& o) { x += o.x; y += o.y; return *this; }
		vec2f& operator -= (const vec2f& o) { x -= o.x; y -= o.y; return *this; }
		vec2f& operator *= (const vec2f& o) { x *= o.x; y *= o.y; return *this; }
		vec2f& operator /= (const vec2f& o) { x /= o.x; y /= o.y; return *this; }

		vec2f operator + () const { return vec2f(-x, -y); }
		vec2f operator - () const { return vec2f(-x, -y); }

		bool operator == (const vec2f& o) const { return ((x == o.x) && (y == o.y)); }
		bool operator != (const vec2f& o) const { return ((x != o.x) || (y != o.y)); }

		vec2f norm() { float len = 1 / std::sqrt(x * x + y * y); return vec2f(len * x, len * y); }
		float len() { return std::sqrt(x * x + y * y); }
	};

	static float ator(float angle) { return float(PI / 180 * angle); }
	static float rtoa(float radian) { return float(180 / PI * radian); }

	class vec2i
	{
	public:
		int x, y;
		vec2i() : x(0), y(0) {}
		vec2i(int x, int y) : x(x), y(y) {}
		~vec2i() {}

		friend std::ostream& operator << (std::ostream& io, const vec2i& o) { std::cout << "x: " << o.x << " y: " << o.y; return io; }
		vec2i& operator >> (vec2i& o) { o.x = x; o.y = y; return o; }

		vec2i operator + (const vec2i& o) const { return vec2i(x + o.x, y + o.y); }
		vec2i operator - (const vec2i& o) const { return vec2i(x - o.x, y - o.y); }
		vec2i operator * (const vec2i& o) const { return vec2i(x * o.x, y * o.y); }
		vec2i operator / (const vec2i& o) const { return vec2i(x / o.x, y / o.y); }

		vec2i& operator += (const vec2i& o) { x += o.x; y += o.y; return *this; }
		vec2i& operator -= (const vec2i& o) { x -= o.x; y -= o.y; return *this; }
		vec2i& operator *= (const vec2i& o) { x *= o.x; y *= o.y; return *this; }
		vec2i& operator /= (const vec2i& o) { x /= o.x; y /= o.y; return *this; }

		vec2i operator + () const { return vec2i(-x, -y); }
		vec2i operator - () const { return vec2i(-x, -y); }

		bool operator == (const vec2i& o) const { return ((x == o.x) && (y == o.y)); }
		bool operator != (const vec2i& o) const { return ((x != o.x) || (y != o.y)); }
	};

	// ��ɫ
	class color3f
	{
	public:
		color3f() : r(0.0f), g(0.0f), b(0.0f) {}
		color3f(float r, float g, float b) : r(r), g(g), b(b) {}
		~color3f() {}
		float r, g, b;
	};

	class color4f
	{
	public:
		color4f() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
		color4f(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {}
		color4f(const color3f& col, float a) : r(col.r), g(col.g), b(col.b), a(a) {}
		color4f(const color3f& col) : r(col.r), g(col.g), b(col.b), a(1.0f) {}
		~color4f() {}
		float r, g, b, a;
	};

	namespace Color
	{
		const color3f Red(1.0f, 0.0f, 0.0f),
			Green(0.0f, 1.0f, 0.0f),
			Blue(0.0f, 0.0f, 1.0f),
			White(1.0f, 1.0f, 1.0f),
			Yellow(1.0f, 1.0f, 0.0f),
			Black(0.0f, 0.0f, 0.0f),
			Orange(1.0f, 0.49f, 0.0f),
			Little_Black(0.94f, 0.94f, 0.94f)
			
			
			;


	}

}