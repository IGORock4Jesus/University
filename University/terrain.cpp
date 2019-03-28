#include "terrain.h"
#include "painter.h"

void renderTerrain(LPDIRECT3DDEVICE9 device, const Terrain & terrain)
{
	renderSprite(device, { 0.0f, 0.0f }, { 100.0f, 100.0f }, 0xff229900);
}
