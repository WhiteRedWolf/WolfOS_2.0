#include <stdio.h>
#include <thread>
#include <time.h>
#include <stdlib.h>

#include "Tes32/GraphicsDevice/GraphicsController.h"
#include "Tes32/AudioDevice/AudioController.h"
#include "Tes32/GraphicsDevice/CGL/Interpreter.h"
#include "Tes32/HardDriveController/HardDiskState.h"

int main(int argc, char** argv) {
	

	printf("\n\nInitializing AudioDevice...");
	Tes32::AudioDevice::AudioController a_ctx;
	
	
	
	printf("Initializing GraphicsDevice...");
	Tes32::GraphicsDevice::GraphicsController g_ctx;

	printf("\n\tCreating Thread %%gctx.RenderLoop");

	system("sleep 1");
	system("clear");
	
	

	g_ctx.Render();

	
	Tes32::GraphicsDevice::CGL::DrawCGLPrefabToVRAM(Tes32::HardDriveController::ReadLines("\\HDD\\System\\Drivers\\vga_cgl_prefabs\\test.cgl"), std::ref(g_ctx), { 50,50 }, {640, 480});
	
	g_ctx.Render();

	
}