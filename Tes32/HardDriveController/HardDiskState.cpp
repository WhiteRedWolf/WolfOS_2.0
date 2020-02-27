#include "HardDiskState.h"


std::vector<char> Tes32::HardDriveController::ReadFile(const char* filename)
{
	std::ifstream inFile;
	size_t size = 0; // here

	inFile.open(filename, std::ios::in | std::ios::binary | std::ios::ate);
	char* oData = 0;

	inFile.seekg(0, std::ios::end); // set the pointer to the end
	size = inFile.tellg(); // get the length of the file
	inFile.seekg(0, std::ios::beg); // set the pointer to the beginning

	oData = new char[size + 1]; //  for the '\0'
	inFile.read(oData, size);
	oData[size] = '\0'; // set '\0' 

	std::vector<char> returnbuf;

	for (int i = 0; i != size; i++) {
		returnbuf.push_back(oData[i]);
	}

	return returnbuf;
}

std::vector<std::string> Tes32::HardDriveController::ReadLines(const char* filename)
{
	std::vector<std::string> lines;

	std::ifstream file(std::experimental::filesystem::current_path().string() + filename);
	if (file.is_open()) {
		
		std::string line;
		while (getline(file, line)) {
			lines.push_back(line);
		}
		file.close();
	}

	return lines;
}

bool Tes32::HardDriveController::WriteFile(char* buffer, const char* filename)
{
	try {
		std::ofstream out;
		out.open(filename);
		out << buffer << "\0";
		out.close();

		return true;
	}
	catch (...) {
		return false;
	}
}
