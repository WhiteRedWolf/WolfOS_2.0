#include "LoadOperatingSystem.h"

Tes32::Bootloader::Bootloader::Bootloader()
{
}

Tes32::Bootloader::Bootloader::~Bootloader()
{
	if(this->header.Destructor != NULL)
		this->header.Destructor();
}

bool Tes32::Bootloader::Bootloader::LoadOperatingSystem(Tes32::Bootloader::InternalTypes::SystemHeader* system_header, void (*construct_operating_system)())
{
	Tes32::Bootloader::InternalTypes::SystemHeader read_header = *system_header;

	this->header = read_header;

	printf("Tes32::Bootloader::Bootloader::LoadOperatingSystem -> *system_header.Name == %s", read_header.Name);
	printf("Tes32::Bootloader::Bootloader::LoadOperatingSystem -> *system_header.Version == %x", read_header.Version);
	
	if      (read_header.Flags & 0b10000000 == 0b10000000) { //Allow Unsafe Kernel Operations
		printf("void(*%s)()::TES32_KERNEL_STDOUT_INTERRUPT:: Enabled Unsafe Kernel Operations!", read_header.Name);
#define _TES32_UNSAFE_KERNEL_OPERATIONS
	}
	else if (read_header.Flags & 0b01000000 == 0b01000000) { //Enable Kernel Hard Drive Routines
		printf("void(*%s)()::TES32_KERNEL_STDOUT_INTERRUPT:: Enabled Kernel Hard Drive Routines!", read_header.Name);
#define _TES32_ENABLE_KERNEL_HARD_DRIVE_ROUTINE
	}
	else if (read_header.Flags & 0b00100000 == 0b00100000) { //Automatically Destroy GraphicsDevice
		printf("void(*%s)()::TES32_KERNEL_STDOUT_INTERRUPT:: Kernel will destruct GraphicsDevice automatically!", read_header.Name);
#define _TES32_DESTROY_GRAPHICS_DEVICE
	} 
	else if (read_header.Flags & 0b00010000 == 0b00010000) { //Automatically Destroy AudioDevice
		printf("void(*%s)()::TES32_KERNEL_STDOUT_INTERRUPT:: Kernel will destruct AudioDevice automatically!", read_header.Name);
#define _TES32_DESTROY_AUDIO_DEVICE
	}

	printf("\n\n\nCalling Operating System Constructor, Leaving Bootloader!!\nCopyright Eeveelution 2020-2020\n");

	construct_operating_system();

	return true;
}
