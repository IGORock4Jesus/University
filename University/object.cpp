#include "object.h"
#include "painter.h"
#include "irenderable.h"



void renderObject(LPDIRECT3DDEVICE9 device, rect *viewport, std::shared_ptr<Object> object)
{
	// проверяем входит ли он во фрустум
	if (!containsRect(viewport, &object->renderRect))
		return;

	for (auto&& c : object->components) {
		if (typeid(*c) == typeid(IRenderable)) {
			((IRenderable*)c.get())->Render(device);
		}
	}
}
