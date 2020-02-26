#pragma once
#include <algorithm>

#include "InternalClasses/ColorPixel.h"

namespace Tes32 {
	namespace GraphicsDevice {
		namespace Optimizations {
			bool CheckForDifferenceInRenderBuffer(Tes32::GraphicsDevice::InternalTypes::ColorPixel* arr1, Tes32::GraphicsDevice::InternalTypes::ColorPixel* arr2, int graphicsmode);
		}
	}
}