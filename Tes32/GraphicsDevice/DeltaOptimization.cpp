#include "DeltaOptimization.h"

bool Tes32::GraphicsDevice::Optimizations::CheckForDifferenceInRenderBuffer(Tes32::GraphicsDevice::InternalTypes::ColorPixel* arr1, Tes32::GraphicsDevice::InternalTypes::ColorPixel* arr2, int graphicsmode)
{
	int it_mx;

	if (graphicsmode == 0) {
		it_mx = 640 * 480;
	}

	for (int i = 0; i != it_mx; i++) {
		if (arr1[i].r != arr2[i].r || arr1[i].g != arr2[i].g || arr1[i].b != arr2[i].b) {
			return false;
		}
	}
	return true;
}
