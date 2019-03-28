#include "console.h"
#include "painter.h"
#include <list>
#include "font.h"
#include "core.h"


std::list<std::string> debugList;
constexpr size_t MAX_DEBUG_STRINGS = 20;
static std::unique_ptr<font> consoleFont;
static bool enabled{ false };


void consoleWrite(std::string text) {
#ifdef _DEBUG
	debugList.push_front(text);
	if (debugList.size() > MAX_DEBUG_STRINGS)
		debugList.pop_back();
#endif // _DEBUG
}

void renderConsole(LPDIRECT3DDEVICE9 device)
{
	if (!enabled) return;
	int x = 20, y = 20;
	int step = 20;

	if (consoleFont)
		for (auto&& s : debugList) {
			drawText(consoleFont.get(), { (float)x, (float)y }, { (float)500, (float)20 }, s, 0xffffffff, DT_LEFT | DT_TOP);
			y += step;
		}


}
static void createFont() {
	if (enabled && !consoleFont) {
		consoleFont = std::make_unique<font>(getRenderDevice(), 16, "Consolas");
	}
}
void enableConsole(bool state)
{
	enabled = state;
	createFont();
}

void toggleConsole()
{
	enabled = !enabled;
	createFont();
}
