#pragma once

#include "vec2.h"


struct rect
{
	vec2 position, size;
};


bool MATH_API containsRect(rect *container, rect *contained);