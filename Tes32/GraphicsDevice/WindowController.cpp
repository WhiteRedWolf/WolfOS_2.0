#include "WindowController.h"

bool Tes32::GraphicsDevice::OutputWindow::SetOutputWindowSize(HANDLE& window_ctx, Tes32::GraphicsDevice::InternalTypes::Boundary2D xy, Tes32::GraphicsDevice::InternalTypes::Boundary2D wh)
{
	SMALL_RECT windowSize = { 0,0,100,100 };
	if (!SetConsoleWindowInfo(window_ctx, TRUE, &windowSize)) {
		return false;
	}
	else {
		return true;
	}
}
