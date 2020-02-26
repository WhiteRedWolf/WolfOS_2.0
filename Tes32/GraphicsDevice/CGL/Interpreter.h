#pragma once
#include <vector>
#include <string>

#include "../InternalClasses/ColorPixel.h"
#include "../InternalClasses/Boundary.h"

namespace Tes32 {
	namespace GraphicsDevice {
		namespace CGL {
			void DrawCGLPrefabToVRAM(std::vector<std::string> cgl_newlines, Tes32::GraphicsDevice::InternalTypes::ColorPixel& vram, Tes32::GraphicsDevice::InternalTypes::Boundary2D origin);
		}
	}
}