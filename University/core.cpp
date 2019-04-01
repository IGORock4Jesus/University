#include <dinput.h>

#include "core.h"
#include "painter.h"
#include "scene.h"
#include "game.h"


HWND hwnd;
LPDIRECT3D9 direct3d;
LPDIRECT3DDEVICE9 device3d;
constexpr int width = 800, height = 600;
LPCSTR className = "UNIVERSITY WINDOW";
LPDIRECTINPUT8 directInput;
LPDIRECTINPUTDEVICE8 keyboard, mouse;
char keyState[256];
DIMOUSESTATE mouseState;



LRESULT CALLBACK wndProc(HWND h, UINT m, WPARAM w, LPARAM l) {
	switch (m)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(h, m, w, l);
	}
}
bool createWindow(HINSTANCE hinstance) {
	WNDCLASS wc{ 0 };
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hInstance = hinstance;
	wc.lpfnWndProc = wndProc;
	wc.lpszClassName = className;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	if (!RegisterClass(&wc)) {
		debug("RegisterClass - failed");
		return false;
	}
	hwnd = CreateWindow(className, className, WS_POPUPWINDOW, 0, 0, width, height, HWND_DESKTOP, nullptr, hinstance, nullptr);
	ShowWindow(hwnd, SW_NORMAL);
	UpdateWindow(hwnd);
	return true;
}
void releaseWindow() {
	if (hwnd) {
		DestroyWindow(hwnd);
	}
}

bool createRenderer() {
	if (!(direct3d = Direct3DCreate9(D3D_SDK_VERSION)))
		return false;
	D3DPRESENT_PARAMETERS pp{ 0 };
	pp.AutoDepthStencilFormat = D3DFMT_D24S8;
	pp.BackBufferCount = 1;
	pp.BackBufferFormat = D3DFMT_X8R8G8B8;
	pp.BackBufferHeight = height;
	pp.BackBufferWidth = width;
	pp.EnableAutoDepthStencil = TRUE;
	pp.hDeviceWindow = hwnd;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.Windowed = TRUE;

	if (FAILED(direct3d->CreateDevice(0, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &pp, &device3d)))
		return false;

	device3d->SetRenderState(D3DRS_LIGHTING, FALSE);

	return true;
}
void releaseRenderer() {
	if (device3d) {
		device3d->Release();
		device3d = nullptr;
	}
	if (direct3d) {
		direct3d->Release();
		direct3d = nullptr;
	}
}

bool createInput(HINSTANCE hinstance) {
	if (FAILED(DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&directInput, nullptr)))
		return false;
	if (FAILED(directInput->CreateDevice(GUID_SysKeyboard, &keyboard, nullptr)))return false;
	if (FAILED(directInput->CreateDevice(GUID_SysMouse, &mouse, nullptr)))return false;

	if (FAILED(keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))return false;
	if (FAILED(mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))return false;

	if (FAILED(keyboard->SetDataFormat(&c_dfDIKeyboard))) return false;
	if (FAILED(mouse->SetDataFormat(&c_dfDIMouse))) return false;
	
	if (FAILED(keyboard->Acquire())) return false;
	if (FAILED(mouse->Acquire())) return false;

	return true;
}
void releaseInput() {
	if (keyboard) {
		keyboard->Unacquire();
		keyboard->Release();
		keyboard = nullptr;
	}
	if (mouse) {
		mouse->Unacquire();
		mouse->Release();
		mouse = nullptr;
	}
	if (directInput) {
		directInput->Release();
		directInput = nullptr;
	}
}
bool coreInitialize(HINSTANCE hinstance) {
	if (!createWindow(hinstance))
		return false;
	if (!createRenderer())
		return false;
	if (!createInput(hinstance))
		return false;
	initialGame();
	return true;
}
void coreRelease() {
	releaseInput();
	releaseRenderer();
	releaseWindow();
}

void rendering() {
	device3d->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 0xff222222, 1.0f, 0);
	device3d->BeginScene();

	renderGame(device3d, width, height);
	
	device3d->EndScene();
	device3d->Present(nullptr, nullptr, nullptr, nullptr);
}

void updateInput() {
	HRESULT result{ S_OK };
	{
		char newKeyState[256];
		keyboard->GetDeviceState(256, newKeyState);
		if (memcmp(newKeyState, keyState, 256)) {
			for (int i = 0; i < 256; i++)
			{
				if (newKeyState[i] != keyState[i]) {
					if (newKeyState[i] & 0x80)
						gameKeyDown(i);
					else
						gameKeyUp(i);
					keyState[i] = newKeyState[i];
				}
			}
		}
		for (int i = 0; i < 256; i++)
		{
			if (newKeyState[i] & 0x80) {
				gameKeyPress(i);
			}
		}
	}
	
	{
		DIMOUSESTATE newMouseState;
		mouse->GetDeviceState(sizeof(DIMOUSESTATE), &newMouseState);
		mouse->Unacquire();
		if (memcmp(&newMouseState, &mouseState, sizeof(DIMOUSESTATE))) {
			if (newMouseState.lX || newMouseState.lY) {
				gameMouseMove({ (float)newMouseState.lX, (float)newMouseState.lY });
			}
			if (newMouseState.lZ) {
				gameMouseWheel(newMouseState.lZ / WHEEL_DELTA);
			}
			for (int i = 0; i < 4; i++)
			{
				if (newMouseState.rgbButtons[i] != mouseState.rgbButtons[i]) {
					if (newMouseState.rgbButtons[i] & 0x80)
						gameMouseDown(i);
					else
						gameMouseUp(i);
					mouseState.rgbButtons[i] = newMouseState.rgbButtons[i];
				}
			}
		}
	}
}

bool coreRun() {
	MSG msg{ 0 };
	while (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
			return false;
	}

	updateInput();

	static auto oldTime = timeGetTime();
	auto newTime = timeGetTime();
	auto time = (newTime - oldTime) * 0.001f;
	oldTime = newTime;

	updateGame(time);

	rendering();

	return true;
}

D3DXVECTOR2 getWindowSize()
{
	RECT r;
	::GetClientRect(hwnd, &r);
	return D3DXVECTOR2(r.right - r.left, r.bottom - r.top);
}

void closeGame()
{
	::DestroyWindow(hwnd);
}

LPDIRECT3DDEVICE9 getRenderDevice()
{
	return device3d;
}
