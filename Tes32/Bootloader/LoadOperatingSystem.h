#pragma once

#include "InternalTypes/SystemHeader.h"

#include <stdio.h>

namespace Tes32 {
	namespace Bootloader {
		class Bootloader {
		public:
			Bootloader();
			~Bootloader();
			bool LoadOperatingSystem(Tes32::Bootloader::InternalTypes::SystemHeader* system_header, void (*construct_operating_system)());
		private:
			Tes32::Bootloader::InternalTypes::SystemHeader header;
		};
	}
}