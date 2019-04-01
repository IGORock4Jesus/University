#pragma once

#include <string>
#include <d3d9.h>


LPDIRECT3DTEXTURE9 loadTexture(LPDIRECT3DDEVICE9 device, std::string name, std::string filename);
void releaseTexture(std::string);

LPDIRECT3DTEXTURE9 getTexture(std::string name);

