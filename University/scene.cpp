#include "scene.h"
#include <list>
#include <memory>


std::list<std::shared_ptr<Object>> objects;


void addObject(std::shared_ptr<Object> object)
{
	objects.push_back(object);
}

void removeObject(std::shared_ptr<Object> object)
{
	objects.remove(object);
}

void renderScene(LPDIRECT3DDEVICE9 device, rect *viewport)
{
	for (auto&& o : objects) {
		renderObject(device, viewport, o);
	}
}
