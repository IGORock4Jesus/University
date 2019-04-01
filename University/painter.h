#pragma once

#include <d3dx9.h>
#include <string>
#include "font.h"


#undef near
#undef far

void drawBox(LPDIRECT3DDEVICE9 device, const D3DXVECTOR3* size, D3DCOLOR color, const D3DXMATRIX* transform = nullptr);

void drawCamera(LPDIRECT3DDEVICE9 device, D3DXVECTOR3 position, D3DXVECTOR3 target, D3DXVECTOR3 up, float aspect, float fov, float near, float far);

void renderCamera(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 position, D3DXVECTOR2 size);

void renderDirectionLight(LPDIRECT3DDEVICE9 device, D3DXVECTOR3 direction, D3DCOLORVALUE color);


void drawText(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 position, D3DXVECTOR2 size, std::string text, D3DCOLOR color, int height = 16, LPCSTR family = "Consolas", DWORD format = DT_CENTER | DT_VCENTER);

void drawText(font *font, D3DXVECTOR2 position, D3DXVECTOR2 size, std::string text, D3DCOLOR color, DWORD format = DT_CENTER | DT_VCENTER);

void draw3DText(LPDIRECT3DDEVICE9 device, std::string text, D3DXMATRIX transform);

void renderSprite(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 position, D3DXVECTOR2 size, D3DCOLOR color);

void renderSprite(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 position, D3DXVECTOR2 size, LPDIRECT3DTEXTURE9 texture);


