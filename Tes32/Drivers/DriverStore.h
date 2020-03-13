#pragma once

#include <string>
#include <vector>

#include "Driver.h"

namespace Tes32 {
	namespace Drivers {
		class DriverStore {
		public:
			DriverStore();
			DriverStore(const char* stored_filename);
			
			void AddDriver(Tes32::Drivers::Driver driver);
			bool CallDriver(int drivertype, int devicenum, std::string json);

		private:
			std::vector<Tes32::Drivers::Driver> graphics_devices;
			std::vector<Tes32::Drivers::Driver> audio_devices;
			std::vector<Tes32::Drivers::Driver> network_devices;
			std::vector<Tes32::Drivers::Driver> encoding_devices;
		};
	}
}