#pragma once
#include <vector>
#include <string>
#include <cmath>
#include "../ReadImageFormats/ReadBMP.h"
#include "../InternalClasses/BMPImage.h"

#include "../InternalClasses/ColorPixel.h"
#include "../InternalClasses/Boundary.h"
#include "../GraphicsController.h"

namespace Tes32 {
	namespace GraphicsDevice {
		namespace CGL {
			void DrawCGLPrefabToVRAM(std::vector<std::string> cgl_newlines, Tes32::GraphicsDevice::GraphicsController& render_ctx, Tes32::GraphicsDevice::InternalTypes::Boundary2D origin, Tes32::GraphicsDevice::InternalTypes::Boundary2D buffer_size);
		}
	}
}