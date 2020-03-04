#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <thread>
#include <time.h>
#include <stdlib.h>

#include "Tes32/GraphicsDevice/GraphicsController.h"
#include "Tes32/AudioDevice/AudioController.h"
#include "Tes32/Bootloader/LoadOperatingSystem.h"

#include "WolfOS2.0/WolfOS.h"

int main(int argc, char** argv) {
		
	printf("\n\nInitializing AudioDevice...");
	Tes32::AudioDevice::AudioController a_ctx;

	printf("Initializing GraphicsDevice...");
	Tes32::GraphicsDevice::GraphicsController g_ctx;

	printf("\n\tCreating Thread %%gctx.RenderLoop");

	system("sleep 1");
	system("clear");

	Tes32::Bootloader::InternalTypes::SystemHeader WolfOS;
		WolfOS.Destructor = NULL;
		WolfOS.Flags = 0b11110000;
		WolfOS.Version = 1;
		strcpy(WolfOS.Name, "WolfOS");

	Tes32::Bootloader::Bootloader loader;
	loader.LoadOperatingSystem(&WolfOS, WolfOS::Bootloader::LoadOperatingSystem);

#ifdef _TES32_DESTROY_GRAPHICS_DEVICE
	g_ctx.Destroy();
#endif

#ifdef _TES32_DESTROY_AUDIO_DEVICE
	a_ctx = nullptr;
#endif
}