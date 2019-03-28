#include "font.h"



font::font(LPDIRECT3DDEVICE9 device, int height, std::string name)
{
	D3DXCreateFont(device, height, 0, 0, 0, 0, RUSSIAN_CHARSET, 0, 0, 0, name.c_str(), &dxfont);
}


font::~font()
{
}
