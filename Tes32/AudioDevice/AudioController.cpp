#include "AudioController.h"
#include "../HardDriveController/HardDiskState.h"
#include <filesystem>

#pragma comment(lib, "winmm.lib")

void ReadWavFileIntoMemory(std::string fname, BYTE** pb, DWORD* fsize) {
	std::ifstream f(fname, std::ios::binary);

	f.seekg(0, std::ios::end);
	int lim = f.tellg();
	*fsize = lim;

	*pb = new BYTE[lim];
	f.seekg(0, std::ios::beg);

	f.read((char*)* pb, lim);

	f.close();
}

Tes32::AudioDevice::AudioController::AudioController()
{
	std::vector<std::string> split;
	
	std::ifstream file(std::experimental::filesystem::current_path().string() + "\\HDD\\System\\Drivers\\tessnd.inf");
	if (file.is_open()) {
		
		std::string line;
		while (getline(file, line)) {
			split.push_back(line);
		}
		file.close();
	}

	for(std::string s : split) {
		std::vector<std::string> Setting = this->split(s, "=");
		if (Setting[0] == "Volume") {
			this->volume = atoi(Setting[1].c_str());
		}
		else if (Setting[0] == "StartupChime") {
			std::stringstream ss;
			ss << "HDD/System/" << Setting[1];
			
			this->PlayWAV(this->volume, ss.str().c_str());
		}
	}


}

bool Tes32::AudioDevice::AudioController::PlayWAV(float volume, const char* filename)
{
	DWORD dwFileSize;
	BYTE* pFileBytes;
	ReadWavFileIntoMemory(filename, &pFileBytes, &dwFileSize);

	BYTE* pDataOffset = (pFileBytes + 40);

	float fVolume = volume/100;

	__int16* p = (__int16*)(pDataOffset + 8);
	for (int i = 80 / sizeof(*p); i < dwFileSize / sizeof(*p); i++) {
		p[i] = (float)p[i] * fVolume;
	}

	PlaySound((LPCSTR)pFileBytes, NULL, SND_MEMORY);

	return true;
}

std::vector<std::string> Tes32::AudioDevice::AudioController::split(const std::string& str, const std::string& delim)
{
	std::vector<std::string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == std::string::npos) pos = str.length();
		std::string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}
