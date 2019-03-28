#pragma once

#include <d3dx9.h>
#include <wrl/client.h>
#include <memory>
#include <string>


class font
{
	Microsoft::WRL::ComPtr<ID3DXFont> dxfont;

public:
	font(LPDIRECT3DDEVICE9 device, int height, std::string name);
	font(const font&) = delete;
	font(font&&) = delete;
	void operator = (const font&) = delete;
	~font();

	LPD3DXFONT get() const throw() { return dxfont.Get(); }
};
