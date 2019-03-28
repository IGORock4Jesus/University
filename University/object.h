#pragma once

#include <string>
#include <memory>
#include <list>
#include "component.h"
#include <d3d9.h>
#include <rect.h>


struct Object
{
	std::string name;
	Object *parent{ nullptr };
	std::list<Object*> childs;	

	rect renderRect{ {0.0f, 0.0f}, {1.0f, 1.0f} };

	std::list<std::shared_ptr<Component>> components;
};



void renderObject(LPDIRECT3DDEVICE9 device, rect *viewport, std::shared_ptr<Object> object);