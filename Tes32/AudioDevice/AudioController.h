#pragma once

#include <Windows.h>
#include <vector>
#include <fstream>
#include <ios>
#include <string>
#include <sstream>

namespace Tes32 {
	namespace AudioDevice {
		class AudioController {
		public:
			AudioController();
			bool PlayWAV(float volume, const char* filename);
		private:
			std::vector<std::string> split(const std::string& str, const std::string& delim);
			float volume = 0.0f;
		};
	}
}