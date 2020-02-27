#include "Interpreter.h"
#include "../GraphicsController.h"
#include "../../KernelFunctions/Split.h"
#include "../../KernelFunctions/Replace.h"
#include "../../KernelFunctions/Round.h"

#include "../../ExternLibs/tinyexpr/tinyexpr.h"

/*
	Command List:

	draw_line     (from_x)   (from_y)  (to_x)    (to_y)    (color)
	[0]			  [1]		 [2]	   [3]	     [4]       [5]
	std::string   uint32_t   uint32_t  uint32_t  uint32_t  ColorPixel
	draw_line 0, 0, 4, 4, 255|255|255
*/


void Tes32::GraphicsDevice::CGL::DrawCGLPrefabToVRAM(std::vector<std::string> cgl_newlines, Tes32::GraphicsDevice::GraphicsController& render_ctx, Tes32::GraphicsDevice::InternalTypes::Boundary2D origin, Tes32::GraphicsDevice::InternalTypes::Boundary2D buffer_size)
{
	for (std::string s : cgl_newlines) {
		if (s == "") continue;
		std::string OriginFormatted = tstd::Replace(s, "%origin_x", std::to_string(origin.x));
					OriginFormatted = tstd::Replace(OriginFormatted, "%origin_y", std::to_string(origin.y));

		
		std::vector<std::string> bmath_CommandSplit = tstd::split(OriginFormatted, " ");

		std::vector<std::string> final_commands;
		for (std::string m : bmath_CommandSplit) {
			if (m.find("+") != std::string::npos || m.find("-") != std::string::npos || m.find("/") != std::string::npos || m.find("*") != std::string::npos) {
				int math = (int)te_interp(m.c_str(), 0);
				final_commands.push_back(std::to_string(math));
			}
			else {
				final_commands.push_back(m);
			}
		}

		std::vector<std::string> color = tstd::split(final_commands[5], "|");

		Tes32::GraphicsDevice::InternalTypes::ColorPixel clr = { (char)atoi(color[0].c_str()), (char)atoi(color[1].c_str()), (char)atoi(color[2].c_str()) };

#define ROUND(a) ((int) (a + 0.5))

#define xa atoi(final_commands[1].c_str())
#define ya atoi(final_commands[2].c_str())
#define xb atoi(final_commands[3].c_str())
#define yb atoi(final_commands[4].c_str())

		int dx = xb - xa;
		int dy = yb - ya;
		int steps, k;

		float xIncrement, yIncrement, x = xa, y = ya;

		if (abs(dx) > abs(dy)) steps = abs(dx);
		else steps = abs(dy);

		xIncrement = dx / (float)steps;
		yIncrement = dy / (float)steps;

		render_ctx.WriteToVideoMemory(ROUND(x), ROUND(y), clr);

		for (int k = 0; k < steps; k++) {
			x += xIncrement;
			y += yIncrement;

			render_ctx.WriteToVideoMemory(x, y, clr);
		}
		
		render_ctx.RenderRegion(xa+1, ya+1, xb+1, yb+1);
		
	}
}
