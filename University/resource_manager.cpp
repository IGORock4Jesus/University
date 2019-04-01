#include "resource_manager.h"
#include <map>
#include <d3dx9.h>


static std::map<std::string, LPDIRECT3DTEXTURE9> textures;


LPDIRECT3DTEXTURE9 loadTexture(LPDIRECT3DDEVICE9 device, std::string name, std::string filename) {
	LPDIRECT3DTEXTURE9 texture;
	if (SUCCEEDED(D3DXCreateTextureFromFile(device, filename.c_str(), &texture))) {
		textures.insert({ name, texture });
		return texture;
	}
	return nullptr;
}

void releaseTexture(std::string name) {
	if (textures.count(name) > 0) {
		auto t = textures[name];
		t->Release();
		textures.erase(name);
	}
}

LPDIRECT3DTEXTURE9 getTexture(std::string name) {
	return textures[name];
}




