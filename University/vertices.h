#pragma once

#include <d3dx9.h>


struct Vertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DCOLOR color;
};

#define VERTEX_SIZE (sizeof(Vertex))
#define VERTEX_FORMAT (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE)

struct TexturedVertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 texel;
};

#define TEXTUREDVERTEX_SIZE (sizeof(TexturedVertex))
#define TEXTUREDVERTEX_FORMAT (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)
