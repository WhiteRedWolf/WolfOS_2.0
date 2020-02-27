#include <stdio.h>
#include <fstream>
#include <ios>
#include <vector>
#include <string>
#include <filesystem>

#define DEFAULT_HARD_DISK_IMAGE "harddisk.t3h"

#pragma once

namespace Tes32 {
	namespace HardDriveController {
		std::vector<char> ReadFile(const char* filename);
		std::vector<std::string> ReadLines(const char* filename);
		bool WriteFile(char* buffer, const char* filename);
	}
}