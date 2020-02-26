#include <stdio.h>
#include <fstream>
#include <ios>
#include <vector>

#define DEFAULT_HARD_DISK_IMAGE "harddisk.t3h"

#pragma once

namespace Tes32 {
	namespace HardDriveController {
		std::vector<char> ReadFile(const char* filename);
		bool WriteFile(char* buffer, const char* filename);
	}
}