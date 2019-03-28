#pragma once

#include <memory>
#include <d3d9.h>
#include <rect.h>
//#include "trivial.h"
#include "object.h"

void addObject(std::shared_ptr<Object> object);
void removeObject(std::shared_ptr<Object> object);
void renderScene(LPDIRECT3DDEVICE9 device, rect *viewport);
