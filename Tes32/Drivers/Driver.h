#pragma once

#include "DriverType.h"

#define __TES32_PRIMARY_DEVICE 0
#define __TES32_SECONDARY_DEVICE_ON_REQUEST 1

namespace Tes32 {
	namespace Drivers {
		class Driver {
			Driver(int drivertype, const char* executable, int device_num);
		};
	}
}