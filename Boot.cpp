#include <stdio.h>
#include <thread>
#include <time.h>
#include <stdlib.h>

#include "Tes32/GraphicsDevice/GraphicsController.h"
#include "Tes32/AudioDevice/AudioController.h"


int main(int argc, char** argv) {
	

	printf("\n\nInitializing AudioDevice...");
	Tes32::AudioDevice::AudioController a_ctx;
	
	
	
	printf("Initializing GraphicsDevice...");
	Tes32::GraphicsDevice::GraphicsController g_ctx;

	printf("\n\tCreating Thread %%gctx.RenderLoop");

	system("sleep 1");
	system("clear");
	
	

	std::thread g_ctx_renderloop(&Tes32::GraphicsDevice::GraphicsController::RenderThread, g_ctx);

	


	g_ctx_renderloop.join();
}