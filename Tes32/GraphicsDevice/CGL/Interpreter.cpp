#include "Interpreter.h"
#include "../GraphicsController.h"
#include "../../KernelFunctions/Split.h"
#include "../../KernelFunctions/Replace.h"
#include "../../KernelFunctions/Round.h"

#include "../../ExternLibs/tinyexpr/tinyexpr.h"

/*
	Command List:

	draw_line,    (from_x),  (from_y), (to_x),   (to_y),   (color)
	[0]			  [1]		 [2]	   [3]	     [4]       [5]
	std::string   uint32_t   uint32_t  uint32_t  uint32_t  ColorPixel
	draw_line 0, 0, 4, 4, 255|255|255

	plot_pixel,  (x),      (y),      (color)
	[0]			 [1]       [2]		 [3]
	std::string  uint32_t  uint32_t  ColorPixel
	plot_pixel 64,64, 128|128|128

	draw_filled_circle, (x),      (y),      (radius)  (color)
	[0]				    [1]	      [2]		[3]	      [4]
	std::string         uint32_t  uint32_t  uint32_t  ColorPixel

	draw_circle, (x),      (y),      (radius)  (color)
	[0]			 [1]	   [2]		 [3]	   [4]
	std::string  uint32_t  uint32_t  uint32_t  ColorPixel

	draw_thick_circle  (x)       (y)       (inner)   (outer)   (color)
	[0]				   [1]		 [2]	   [3]       [4]       [5]
	std::string		   uint32_t  uint32_t  uint32_t  uint32_t  ColorPixel

	draw_filled_rectangle  (x1)      (y1)      (x2)      (y2)      (color)
	[0]                    [1]       [2]       [3]       [4]       [5]
	std::string            uint32_t  uint32_t  uint32_t  uint32_t  ColorPixel
*/


void Tes32::GraphicsDevice::CGL::DrawCGLPrefabToVRAM(std::vector<std::string> cgl_newlines, Tes32::GraphicsDevice::GraphicsController& render_ctx, Tes32::GraphicsDevice::InternalTypes::Boundary2D origin, Tes32::GraphicsDevice::InternalTypes::Boundary2D buffer_size)
{
	for (std::string s : cgl_newlines) {
		if (s == "") continue;
		std::string OriginFormatted = tstd::Replace(s, "%origin_x", std::to_string(origin.x));
					OriginFormatted = tstd::Replace(OriginFormatted, "%origin_y", std::to_string(origin.y));

		
		std::vector<std::string> bmath_CommandSplit = tstd::split(OriginFormatted, ",");

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


		if (final_commands[0] == "draw_line") {
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

			render_ctx.RenderRegion(xa + 1, ya + 1, xb + 1, yb + 1);
		}
		else if (final_commands[0] == "plot_pixel") {
			std::vector<std::string> color = tstd::split(final_commands[3], "|");

			Tes32::GraphicsDevice::InternalTypes::ColorPixel clr = { (char)atoi(color[0].c_str()), (char)atoi(color[1].c_str()), (char)atoi(color[2].c_str()) };

			render_ctx.WriteToVideoMemory(atoi(final_commands[1].c_str()), atoi(final_commands[2].c_str()), clr);
		}
		else if (final_commands[0] == "draw_filled_circle") {
			std::vector<std::string> color = tstd::split(final_commands[4], "|");
			Tes32::GraphicsDevice::InternalTypes::ColorPixel clr = { (char)atoi(color[0].c_str()), (char)atoi(color[1].c_str()), (char)atoi(color[2].c_str()) };

#define r atoi(final_commands[3].c_str())
#define ox atoi(final_commands[1].c_str())
#define oy atoi(final_commands[2].c_str())

			for (int x = -r; x < r; x++) {
				int height = (int)sqrt(r * r - x * x);

				for (int y = -height; y < height; y++) {
					render_ctx.WriteToVideoMemory(x + ox, y + oy, clr);
				}
			}

								 
		}
		else if (final_commands[0] == "draw_circle") {
			std::vector<std::string> color = tstd::split(final_commands[4], "|");
			Tes32::GraphicsDevice::InternalTypes::ColorPixel clr = { (char)atoi(color[0].c_str()), (char)atoi(color[1].c_str()), (char)atoi(color[2].c_str()) };

#define r atoi(final_commands[3].c_str())
#define ox atoi(final_commands[1].c_str())
#define oy atoi(final_commands[2].c_str())

			int x = r;
			int y = 0;
			int err = 0;

			while (x >= y) {
				render_ctx.WriteToVideoMemory(ox + x, oy + y, clr);
				render_ctx.WriteToVideoMemory(ox + y, oy + x, clr);
				render_ctx.WriteToVideoMemory(ox - y, oy + x, clr);
				render_ctx.WriteToVideoMemory(ox - x, oy + y, clr);
				render_ctx.WriteToVideoMemory(ox - x, oy - y, clr);
				render_ctx.WriteToVideoMemory(ox - y, oy - x, clr);
				render_ctx.WriteToVideoMemory(ox + y, oy - x, clr);
				render_ctx.WriteToVideoMemory(ox + x, oy - y, clr);

				if (err <= 0) {
					y += 1;
					err += 2 * y + 1;
				}
				if (err > 0) {
					x -= 1;
					err -= 2 * x + 1;
				}
			}
		}
		else if (final_commands[0] == "draw_thick_circle") {
			std::vector<std::string> color = tstd::split(final_commands[5], "|");
			Tes32::GraphicsDevice::InternalTypes::ColorPixel clr = { (char)atoi(color[0].c_str()), (char)atoi(color[1].c_str()), (char)atoi(color[2].c_str()) };

#define xc atoi(final_commands[1].c_str())
#define yc atoi(final_commands[2].c_str())
#define inner atoi(final_commands[3].c_str())
#define outer atoi(final_commands[4].c_str())

#define xLine(x1, x2, y) while(x1 <= x2) render_ctx.WriteToVideoMemory(x1++, y, clr)
#define yLine(x, y1, y2) while(y1 <= y2) render_ctx.WriteToVideoMemory(x, y1++, clr);

			int xo = outer;
			int xi = inner;

			int y = 0;
			
			int erro = 1 - xo;
			int erri = 1 - xi;

			while (xo > y) {

				xLine(xc + xi, xc + xo, yc + y);
				yLine(xc + y, yc + xi, yc + xo);
				xLine(xc - xo, xc - xi, yc + y);
				yLine(xc - y, yc + xi, yc + xo);
				xLine(xc - xo, xc - xi, yc - y);
				yLine(xc - y, yc - xo, yc - xi);
				xLine(xc + xi, xc + xo, yc - y);
				yLine(xc + y, yc - xo, yc - xi);

				y++;

				if (erro < 0) {
					erro += 2 * y + 1;
				}
				else {
					xo--;
					erro += 2 * (y - xo + 1);
				}

				if (y > inner) {
					xi = y;
				}
				else {
					if (erri < 0) {
						erri += 2 * y + 1;
					}
					else {
						xi--;
						erri += 2 * (y - xi + 1);
					}
				}

			}
		}
		else if (final_commands[0] == "draw_filled_rectangle") {
			std::vector<std::string> color = tstd::split(final_commands[5], "|");
			Tes32::GraphicsDevice::InternalTypes::ColorPixel clr = { (char)atoi(color[0].c_str()), (char)atoi(color[1].c_str()), (char)atoi(color[2].c_str()) };


#define x1 atoi(final_commands[1].c_str())
#define y1 atoi(final_commands[2].c_str())

#define x2 atoi(final_commands[3].c_str())
#define y2 atoi(final_commands[4].c_str())

			for (int x = x1; x != x2; x++) {
				for (int y = y1; y != y2; y++) {
					
					render_ctx.WriteToVideoMemory(x, y, clr);
				}
			}
		}

	}
}
