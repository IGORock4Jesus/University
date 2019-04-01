#pragma once

#include <d3dx9.h>
#include "component.h"


// ��� ������� �������� �����������
enum class TerrainBusy {
	free, // ��������
	building, // ������
	forest, // ���
};

constexpr size_t TILE_COUNT = 2;

// ������� ������� ����
struct Terrain : Component
{
	// 
	TerrainBusy busyness[TILE_COUNT][TILE_COUNT]{ TerrainBusy::free };
	float tileSize{ 100.0f };
};


void renderTerrain(LPDIRECT3DDEVICE9 device, const Terrain& terrain);
