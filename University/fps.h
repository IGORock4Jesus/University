#pragma once

#include <d3d9.h>

void updateFPS(float time);


void renderFPS(LPDIRECT3DDEVICE9 device, int width, int height);


void enableFPS(bool state);

void toggleFPS();