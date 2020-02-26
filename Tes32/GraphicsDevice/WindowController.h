#pragma once
#include <Windows.h>
#include "InternalClasses/Boundary.h"

namespace Tes32 {
	namespace GraphicsDevice {
		namespace OutputWindow {
			bool SetOutputWindowSize(HANDLE& window_ctx, Tes32::GraphicsDevice::InternalTypes::Boundary2D xy, Tes32::GraphicsDevice::InternalTypes::Boundary2D wh);
		}
	}
}