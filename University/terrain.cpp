#include "terrain.h"
#include "painter.h"
#include "resource_manager.h"


void renderTerrain(LPDIRECT3DDEVICE9 device, const Terrain & terrain)
{
	auto texture = getTexture("ground");

	for (size_t y = 0; y < TILE_COUNT; y++)
	{
		for (size_t x = 0; x < TILE_COUNT; x++)
		{
			renderSprite(device, { x * terrain.tileSize, y * terrain.tileSize }, { terrain.tileSize, terrain.tileSize }, texture);
		}
	}
}
