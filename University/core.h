#pragma once

#include <Windows.h>
#include <d3dx9.h>

#define debug(x) {OutputDebugString(x);OutputDebugString("\n");}

bool coreInitialize(HINSTANCE hinstance);
void coreRelease();
bool coreRun();
D3DXVECTOR2 getWindowSize();
void closeGame();
LPDIRECT3DDEVICE9 getRenderDevice();