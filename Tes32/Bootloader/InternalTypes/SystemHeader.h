#pragma once
namespace Tes32 {
	namespace Bootloader {
		namespace InternalTypes {
			struct SystemHeader {
				char Version; //Version of System Header, for future compatibility;
				/*
					Bit 1: Allow Unsafe Operations (Active-High)
					Bit 2: Use Kernel Hard Disk Routines (Active-High)
					Bit 3: Automatically Destroy GraphicsDevice (Active-High)
					Bit 4: Automatically Destroy AudioDevice (Active-High)
					rest currently unused.
				*/
				char Flags;
				
				char Name[8];
				void (*Destructor)();
			};
		}
	}
}