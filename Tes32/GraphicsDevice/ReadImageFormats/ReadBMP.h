#pragma once
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "../InternalClasses/BMPImage.h"
#include "../../HardDriveController/HardDiskState.h"

namespace Tes32 {
	namespace GraphicsDevice {
		namespace ImageFormats {
			namespace BMP {
				Tes32::GraphicsDevice::InternalTypes::BMPImage ReadBMP(const char* filename);
			}
		}
	}
}