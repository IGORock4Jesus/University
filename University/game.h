#pragma once

#include <d3dx9.h>
//#include "trivial.h"


void updateGame(float time);
void renderGame(LPDIRECT3DDEVICE9 device, int width, int height);

void gameKeyDown(BYTE key);
void gameKeyUp(BYTE key);
void gameKeyPress(BYTE key);

void gameMouseDown(BYTE key);
void gameMouseUp(BYTE key);
void gameMousePress(BYTE key);
void gameMouseMove(D3DXVECTOR2 relative);
void gameMouseWheel(int wheel);
