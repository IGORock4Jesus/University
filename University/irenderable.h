#pragma once

#include <d3d9.h>


__interface IRenderable
{
	void Render(LPDIRECT3DDEVICE9 device);
};
