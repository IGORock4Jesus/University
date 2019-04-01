#pragma once

#include <d3dx9.h>
#include "component.h"


// тип объекта занятого территорией
enum class TerrainBusy {
	free, // свободно
	building, // здание
	forest, // лес
};

constexpr size_t TILE_COUNT = 2;

// простое игровое поле
struct Terrain : Component
{
	// 
	TerrainBusy busyness[TILE_COUNT][TILE_COUNT]{ TerrainBusy::free };
	float tileSize{ 100.0f };
};


void renderTerrain(LPDIRECT3DDEVICE9 device, const Terrain& terrain);
