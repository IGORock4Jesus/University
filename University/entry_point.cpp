#include "core.h"
#include <thread>


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR, int) {
	if (coreInitialize(hinstance)) {
		while (coreRun())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
	coreRelease();

	return 0;
}
