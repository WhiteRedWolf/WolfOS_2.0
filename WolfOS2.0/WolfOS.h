#pragma once

#include <stdio.h>
#include <thread>

#include "../Tes32/GraphicsDevice/GraphicsController.h"
#include "../Tes32/AudioDevice/AudioController.h"

namespace WolfOS {
	namespace Bootloader {
		void LoadOperatingSystem();
	}

	void wolfos_main();
}