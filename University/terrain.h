#pragma once

#include <d3dx9.h>
#include "component.h"


// тип объекта занятого территорией
enum class TerrainBusy {
	free, // свободно
	building, // здание
	forest, // лес
};

// простое игровое поле
struct Terrain : Component
{
	// 
	TerrainBusy busyness[100][100]{ TerrainBusy::free };
};


void renderTerrain(LPDIRECT3DDEVICE9 device, const Terrain& terrain);
