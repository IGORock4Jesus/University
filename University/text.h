#pragma once

#include <string>
#include <Windows.h>

#include "component.h"


struct Text : Component
{
	std::string text;
	RECT rect;
};

