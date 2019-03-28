#pragma once

#include "math_api.h"

struct vec2
{
	float x, y;	
};

inline vec2 operator + (const vec2& a, const vec2& b) {
	return { a.x + b.x, a.y + b.y };
}
