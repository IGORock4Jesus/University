#include "game.h"
#include <d3dx9.h>
#include <dinput.h>
#include "painter.h"
#include "terrain.h"
#include "core.h"
#include "scene.h"
#include "console.h"
#include "fps.h"
#include "resource_manager.h"


D3DXVECTOR2 cameraPosition;
float cameraSpeed{ 1.0f };
Terrain terrain;
const int zoomCount = 6;
int zoom = 0;
float zoomChoose[]{
	1.0f, 0.5f, 0.25f, 0.125f, 0.0625f, 0.03125f
};
rect viewport;



void initialGame() {
	loadTexture(getRenderDevice(), "ground", "..\\Resources\\Textures\\rocky_ground.png");
}

void updateGame(float time)
{
	updateFPS(time);
}

void renderGame(LPDIRECT3DDEVICE9 device, int width, int height)
{
	renderCamera(device, cameraPosition, getWindowSize() * zoomChoose[zoom]);

	renderDirectionLight(device, { 0.1f, -0.1f, -0.9f }, { 1.0f, 1.0f, 1.0f, 1.0f });

	renderTerrain(device, terrain);

	renderScene(device, &viewport);

	renderConsole(device);

	renderFPS(device, width, height);
}

void gameKeyDown(BYTE key)
{
	if (key == DIK_ESCAPE) {
		consoleWrite("game-close");
		closeGame();
	}
	if (key == DIK_E)
		if (zoom + 1 < zoomCount) {
			zoom++;
			consoleWrite("zoom-in");
		}
	if (key == DIK_Q)
		if (zoom > 0) {
			zoom--;
			consoleWrite("zoom-out");
		}
	if (key == DIK_F9) {
		toggleFPS();
	}
	if (key == DIK_F10) {
		toggleConsole();
	}
}

void gameKeyUp(BYTE key)
{
}

void gameKeyPress(BYTE key)
{
	if (key == DIK_W)
		cameraPosition += D3DXVECTOR2{ 0.0f, -1.0f } *cameraSpeed  * zoomChoose[zoom];
	if (key == DIK_S)
		cameraPosition += D3DXVECTOR2{ 0.0f, 1.0f } *cameraSpeed  * zoomChoose[zoom];
	if (key == DIK_A)
		cameraPosition += D3DXVECTOR2{ -1.0f, 0.0f } *cameraSpeed  * zoomChoose[zoom];
	if (key == DIK_D)
		cameraPosition += D3DXVECTOR2{ 1.0f, 0.0f } *cameraSpeed  * zoomChoose[zoom];

}

void gameMouseDown(BYTE key)
{
}

void gameMouseUp(BYTE key)
{
}

void gameMousePress(BYTE key)
{
}

void gameMouseMove(D3DXVECTOR2 relative)
{
}

void gameMouseWheel(int wheel)
{
}
