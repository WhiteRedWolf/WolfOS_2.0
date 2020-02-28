#pragma once
#include "Boundary.h"


namespace Tes32 {
	namespace GraphicsDevice {
		namespace InternalTypes {
			struct BMPImage {
				unsigned char* pixeldata;
				Tes32::GraphicsDevice::InternalTypes::Boundary2D size;
			};
		}
	}
}