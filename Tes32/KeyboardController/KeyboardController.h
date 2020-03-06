#pragma once

#include <Windows.h>
#include <stdio.h>
#include <iostream>

namespace Tes32 {
	namespace KeyboardController {
		class KeyboardDriver {
		public:
			void KernelKeyboardDriverLoop();
			bool CheckForKeyboardHeldInput(int key);
			
			void DisableInterrupts(int os_key);
		private:
			bool RunKeyboardInputs = true;
			int OS_KEY;
		};
	}
}