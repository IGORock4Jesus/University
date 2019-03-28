#include "painter.h"
#include "vertices.h"



void drawBox(LPDIRECT3DDEVICE9 device, const D3DXVECTOR3* size, D3DCOLOR color, const D3DXMATRIX* transform) {
	D3DXMATRIX m;
	if (transform)
		m = *transform;
	else
		D3DXMatrixIdentity(&m);
	D3DXVECTOR3 half = *size * 0.5f;
	D3DXVECTOR3 points[]{
		{-half.x, -half.y, -half.x}, // A
		{ half.x, -half.y, -half.x}, // B
		{ half.x, -half.y,  half.x}, // C
		{-half.x, -half.y,  half.x}, // D
		{-half.x,  half.y, -half.x}, // A1
		{ half.x,  half.y, -half.x}, // B1
		{ half.x,  half.y,  half.x}, // C1
		{-half.x,  half.y,  half.x}, // D1
	};
	D3DXVECTOR3 normals[]{
		{1.0f, 0.0f, 0.0f}, // right
		{-1.0f, 0.0f, 0.0f}, // left
		{0.0f, 1.0f, 0.0f}, // top
		{0.0f, -1.0f, 0.0f}, // bottom
		{0.0f, 0.0f, -1.0f}, // front
		{0.0f, 0.0f, 1.0f}, // back
	};
	Vertex vs[]{
		// bottom
		{points[0], normals[3], color},
		{points[1], normals[3], color},
		{points[2], normals[3], color},
		{points[3], normals[3], color},
		// top
		{points[4], normals[2], color},
		{points[7], normals[2], color},
		{points[6], normals[2], color},
		{points[5], normals[2], color},
		// right
		{points[5], normals[0], color},
		{points[6], normals[0], color},
		{points[2], normals[0], color},
		{points[1], normals[0], color},
		// left
		{points[7], normals[1], color},
		{points[4], normals[1], color},
		{points[0], normals[1], color},
		{points[3], normals[1], color},
		// front
		{points[4], normals[4], color},
		{points[5], normals[4], color},
		{points[1], normals[4], color},
		{points[0], normals[4], color},
		// back
		{points[6], normals[5], color},
		{points[7], normals[5], color},
		{points[3], normals[5], color},
		{points[2], normals[5], color},
	};
	USHORT is[]{
		0,1,2,0,2,3,
		4,5,6,4,6,7,
		8,9,10,8,10,11,
		12,13,14,12,14,15,
		16,17,18,16,18,19,
		20,21,22,20,22,23
	};

	device->SetFVF(VERTEX_FORMAT);
	device->SetTransform(D3DTS_WORLD, &m);
	device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 24, 12, is, D3DFMT_INDEX16, vs, VERTEX_SIZE);
}


void drawCamera(LPDIRECT3DDEVICE9 device, D3DXVECTOR3 position, D3DXVECTOR3 target, D3DXVECTOR3 up, float aspect, float fov, float near, float far) {
	D3DXMATRIX m;
	device->SetTransform(D3DTS_VIEW, D3DXMatrixLookAtLH(&m, &position, &target, &up));
	device->SetTransform(D3DTS_PROJECTION, D3DXMatrixPerspectiveFovLH(&m, fov, aspect, near, far));
}

void renderCamera(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 position, D3DXVECTOR2 size)
{
	D3DXMATRIX m;
	device->SetTransform(D3DTS_VIEW, D3DXMatrixLookAtLH(&m, &D3DXVECTOR3(position.x, position.y, 1000.0f), &D3DXVECTOR3(position.x, position.y, 0.0f), &D3DXVECTOR3(0.0f, -1.0f, 0.0f)));
	device->SetTransform(D3DTS_PROJECTION, D3DXMatrixOrthoLH(&m, size.x, size.y, 0.1f, 10000.0f));
}


void drawDirectionLight(LPDIRECT3DDEVICE9 device, D3DXVECTOR3 direction, D3DCOLORVALUE color) {
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));
	D3DXVec3Normalize(&direction, &direction);
	light.Diffuse = color;
	light.Ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	light.Direction = direction;
	light.Type = D3DLIGHT_DIRECTIONAL;
	device->SetLight(0, &light);
	device->LightEnable(0, TRUE);
}

void drawText(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 position, D3DXVECTOR2 size, std::string text, D3DCOLOR color, int height, LPCSTR family, DWORD format)
{
	LPD3DXFONT font;
	D3DXCreateFont(device, height, 0, 0, 0, 0, RUSSIAN_CHARSET, 0, 0, 0, family, &font);

	RECT rect{ position.x, position.y, position.x + size.x, position.y + size.y };
	font->DrawTextA(nullptr, text.c_str(), -1, &rect, format, color);

	font->Release();
}

void drawText(font * font, D3DXVECTOR2 position, D3DXVECTOR2 size, std::string text, D3DCOLOR color, DWORD format)
{
	RECT rect{ position.x, position.y, position.x + size.x, position.y + size.y };
	font->get()->DrawTextA(nullptr, text.c_str(), -1, &rect, format, color);
}

void draw3DText(LPDIRECT3DDEVICE9 device, std::string text, D3DXMATRIX transform) {
	auto hdc = ::CreateCompatibleDC(nullptr);
	auto font = ::CreateFont(10, 0, 0, 0, FW_NORMAL, 0, 0, 0, RUSSIAN_CHARSET, 0, 0, 0, DEFAULT_PITCH | FF_DONTCARE, "Arial");
	::SelectObject(hdc, font);
	LPD3DXMESH mesh;
	::D3DXCreateText(device, hdc, text.c_str(), 0.001f, 0.1f, &mesh, nullptr, nullptr);
	device->SetTransform(D3DTS_WORLD, &transform);
	D3DMATERIAL9 mat{ 0 };
	mat.Diffuse = { 1.0f, 0.0f, 0.0f, 1.0f };
	device->SetMaterial(&mat);

	device->SetFVF(mesh->GetFVF());
	mesh->DrawSubset(0);
	mesh->Release();
	DeleteDC(hdc);
	DeleteObject(font);
}

void renderSprite(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 position, D3DXVECTOR2 size, D3DCOLOR color)
{
	Vertex vs[]{
		{{position.x, position.y, 0.0f}, {0.0f, 0.0f, 1.0f}, color},
		{{position.x + size.x, position.y, 0.0f}, {0.0f, 0.0f, 1.0f}, color},
		{{position.x + size.x, position.y + size.y, 0.0f}, {0.0f, 0.0f, 1.0f}, color},
		{{position.x, position.y + size.y, 0.0f}, {0.0f, 0.0f, 1.0f}, color},
	};
	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	device->SetTransform(D3DTS_WORLD, &m);
	device->SetFVF(VERTEX_FORMAT);
	device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vs, VERTEX_SIZE);
}


