#define _CRT_SECURE_NO_WARNINGS
#include "KeyboardController.h"

void Tes32::KeyboardController::KeyboardDriver::KernelKeyboardDriverLoop()
{

	/*
		cd: __tes32_harddrive_controller___thread_this___change_directory_root|%passed_1?
		kernel_x: __tes32_kernel_mode_completed_?
		ls: __tes32_harddrive_controller___list_directory_of|/romfs/tes32|_tes32_typespace___only_show_command
	*/

	bool dontexit = false;
	#define CheckKey(x) CheckForKeyboardHeldInput(x)
	while (this->RunKeyboardInputs) {
		if (CheckKey(VK_CONTROL) && CheckKey(VK_RSHIFT) && CheckKey(VK_F12) || dontexit) {
			
			std::string kernel_interrupt_input;
			printf("\nKERNEL INTERRUPT MODE - ONLY USE IN EMERGENCY!\nkernel@keyboardinterrupt:/romfs/tes32$ ");
			std::cin >> kernel_interrupt_input;
			if (kernel_interrupt_input == "__tes32_power_state_interrupt_?shutdown") {
				exit(12001);
			}
			else if (kernel_interrupt_input == "ls") {
				printf("                                     $ __tes32_harddrive_controller___list_directory_of|/romfs/tes32|_tes32_typespace___only_show_command?");

				printf("\n[ls.tbf      ][shutdown.tbf][kernel_x.tbf] | [98 bytes  ][39 bytes  ][31 bytes  ]\n");
				printf("\n[cd.tbf      ][exit_os.tbf ][            ] | [77 bytes  ][78 bytes  ][          ]\n");
				printf("\n[            ][            ][            ] | [          ][          ][          ]\n");
				dontexit = true;
			}
		}
	}
}

bool Tes32::KeyboardController::KeyboardDriver::CheckForKeyboardHeldInput(int key)
{
	return (GetAsyncKeyState(key) & 0x8000) != 0;
}
