#include "fps.h"
#include "painter.h"
#include "font.h"
#include "core.h"


static bool enabled{ false };
static int frameCount{ 0 };
static float forSecondTime{ 0.0f };
static int drawFrames{ 0 };
static std::unique_ptr<font> fpsFont;


void updateFPS(float time)
{
	if (!enabled)return;

	frameCount++;

	forSecondTime += time;

	if (forSecondTime >= 1.0f) {
		forSecondTime -= 1.0f;

		drawFrames = frameCount;

		frameCount = 0;
	}
}

void renderFPS(LPDIRECT3DDEVICE9 device, int width, int height)
{
	if (!enabled)return;
	if (fpsFont)
		drawText(fpsFont.get(), { 0.0f, 0.0f }, { (float)width, (float)height }, "FPS = " + std::to_string(drawFrames), 0xffffffff, DT_RIGHT | DT_BOTTOM);
}

static void createFont() {
	if (enabled)
		fpsFont = std::make_unique<font>(getRenderDevice(), 16, "Consolas");
}

void enableFPS(bool state)
{
	enabled = state;
	createFont();
}

void toggleFPS()
{
	enabled = !enabled;
	createFont();
}
