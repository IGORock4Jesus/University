#pragma once

#include <d3dx9.h>
#include "component.h"


// ��� ������� �������� �����������
enum class TerrainBusy {
	free, // ��������
	building, // ������
	forest, // ���
};

// ������� ������� ����
struct Terrain : Component
{
	// 
	TerrainBusy busyness[100][100]{ TerrainBusy::free };
};


void renderTerrain(LPDIRECT3DDEVICE9 device, const Terrain& terrain);
