#pragma once

#include <string>
#include <d3d9.h>


void consoleWrite(std::string text);
void renderConsole(LPDIRECT3DDEVICE9 device);
void enableConsole(bool state);

void toggleConsole();