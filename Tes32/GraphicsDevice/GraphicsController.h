#pragma once
#include <stdio.h>
#include <cstdint>
#include <exception>
#include <Windows.h>
#include <fstream>
#include <ios>
#include <string>
#include <vector>
#include <filesystem>
#include <thread>

#include "InternalClasses/ColorPixel.h"
#include "InternalClasses/Boundary.h"
#include "WindowController.h"
#include "DeltaOptimization.h"

namespace Tes32 {
	namespace GraphicsDevice {
		class GraphicsController {

		public:

			GraphicsController();
			

			bool Destroy();
			void ModifySyncRegisters(bool sRender, bool sStayWhileNotRendering);
			Tes32::GraphicsDevice::InternalTypes::ColorPixel* display_buffer;
			void RenderThread();
		private:
			std::vector<std::string> split(const std::string& str, const std::string& delim);
			
			

			Tes32::GraphicsDevice::InternalTypes::Boundary2D ctx_size;

			bool KeepRendering = true;
			bool Hold = true;

			//Driver Settings
			int graphicsmode = 0;

			Tes32::GraphicsDevice::InternalTypes::ColorPixel fillcolor;

			int clr_adjust_r = 0;
			int clr_adjust_g = 0;
			int clr_adjust_b = 0;

			int multithread = 2;

			HWND display_ctx;
			HDC  render_ctx;
			HANDLE display_handle;
		};
	}
}