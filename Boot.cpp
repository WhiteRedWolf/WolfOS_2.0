#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <thread>
#include <time.h>
#include <stdlib.h>

#include "Tes32/KeyboardController/KeyboardController.h"
#include "Tes32/Bootloader/LoadOperatingSystem.h"

#include "WolfOS2.0/WolfOS.h"

int main(int argc, char** argv) {

	srand(time(NULL));
	int OS_KEY = std::rand();

	printf("OS Key Generated for disabling User Generated Kernel Interrupts: %i\n", OS_KEY);

	Tes32::KeyboardController::KeyboardDriver k_ctx;
	std::thread keyboard(&Tes32::KeyboardController::KeyboardDriver::KernelKeyboardDriverLoop, k_ctx);


	system("sleep 1");
	system("clear");

	Tes32::Bootloader::InternalTypes::SystemHeader WolfOS;
		WolfOS.Destructor = NULL;
		WolfOS.Flags = 0b11110000;
		WolfOS.Version = 1;
		strcpy(WolfOS.Name, "WolfOS");

	Tes32::Bootloader::Bootloader loader;
	loader.LoadOperatingSystem(&WolfOS, WolfOS::Bootloader::LoadOperatingSystem);

	keyboard.join();

}