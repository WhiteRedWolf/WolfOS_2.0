#include "WolfOS.h"

void WolfOS::Bootloader::LoadOperatingSystem()
{
	printf("WolfOS!!!!!");
	wolfos_main();
}

void WolfOS::wolfos_main()
{

	printf("\n\nInitializing AudioDevice...");
	Tes32::AudioDevice::AudioController a_ctx;

	printf("Initializing GraphicsDevice...");
	Tes32::GraphicsDevice::GraphicsController g_ctx;

	
}
