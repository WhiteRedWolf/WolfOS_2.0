#include "GraphicsController.h"


Tes32::GraphicsDevice::GraphicsController::GraphicsController()
{

	this->display_ctx = GetConsoleWindow();
	this->render_ctx = GetDC(display_ctx);
	this->display_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	std::vector<std::string> driversettings;

	int width, height;
	Tes32::GraphicsDevice::InternalTypes::ColorPixel fillclr;

	std::ifstream file(std::experimental::filesystem::current_path().string() + "\\HDD\\System\\Drivers\\tesvga.inf");
	if (file.is_open()) {
		printf("LOADED!");
		std::string line;
		while (getline(file, line)) {
			driversettings.push_back(line);
		}
		file.close();
	}

	for (std::string s : driversettings) {
		std::vector<std::string> Split = tstd::split(s, "=");
		
		if (Split[0] == "GraphicsMode") {
			if (Split[1] == "1040x480") {
				this->graphicsmode = 0;
				width = 1040; // 1040 / 120 = 8.6px
				height = 480; // 480 / 30 = 16px
				//Tes32::GraphicsDevice::OutputWindow::SetOutputWindowSize(this->display_handle, { 0,0 }, { 64, 64 });
			}
		}
		else if (Split[0] == "FillColor") {
			std::vector<std::string> color = tstd::split(Split[1], ",");

			int r, g, b;
			r = atoi(color[0].c_str());
			g = atoi(color[1].c_str());
			b = atoi(color[2].c_str());

			r--; g--; b--;

			this->fillcolor = { (char)r, (char)g, (char)b };
			fillclr = { (char)r, (char)g, (char)b };
			
		}
		else if (Split[0] == "ColorAdjust_R") { this->clr_adjust_r = atoi(Split[1].c_str()); }
		else if (Split[0] == "ColorAdjust_G") { this->clr_adjust_g = atoi(Split[1].c_str()); }
		else if (Split[0] == "ColorAdjust_B") { this->clr_adjust_b = atoi(Split[1].c_str()); }
		

	}

	this->display_buffer = new Tes32::GraphicsDevice::InternalTypes::ColorPixel[width * height];

	for (int y = 0; y != height; y++) {
		for (int x = 0; x != width; x++) {
			this->display_buffer[x + width * y] = fillclr;
		}
	}

	this->ctx_size = { width, height };

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}



bool Tes32::GraphicsDevice::GraphicsController::Destroy()
{
	try {
		this->KeepRendering = false;
		delete this->display_buffer;
		ReleaseDC(this->display_ctx, this->render_ctx);
	}
	catch (std::exception& e){
		printf("!!!KERNEL PANIC!!! g_ctx:: Failed to Destroy GraphicsController // Details: %s\n", e.what());
		return false;
	}

	return true;
}

void Tes32::GraphicsDevice::GraphicsController::ModifySyncRegisters(bool sRender, bool sStayWhileNotRendering)
{
	this->KeepRendering = sRender;
	this->Hold = sStayWhileNotRendering;
}


void Tes32::GraphicsDevice::GraphicsController::Render()
{
	int start, movement, end;
	Tes32::GraphicsDevice::InternalTypes::ColorPixel* vram = this->display_buffer;

	start = 0;
	movement = 1;
	end = this->ctx_size.y;

	for (int y = start; y != end; y++) {
		for (int x = 0; x != this->ctx_size.x; x++) {
			SetPixel(
				render_ctx,
				x, y,
				RGB(
					display_buffer[x + this->ctx_size.x * y].r,
					display_buffer[x + this->ctx_size.x * y].g,
					display_buffer[x + this->ctx_size.x * y].b
				)
			);
					
		}
	}
		
	
}
void Tes32::GraphicsDevice::GraphicsController::RenderRegion(int xa, int ya, int xb, int yb)
{
	int start, movement, end;
	Tes32::GraphicsDevice::InternalTypes::ColorPixel* vram = this->display_buffer;

	start = 0;
	movement = 1;
	end = 480;

	for (int y = ya; y != yb; y++) {
		for (int x = xa; x != xb; x++) {
			SetPixel(
				render_ctx,
				x, y,
				RGB(
					display_buffer[x + this->ctx_size.x * y].r,
					display_buffer[x + this->ctx_size.x * y].g,
					display_buffer[x + this->ctx_size.x * y].b
				)
			);

		}
	}


}
void Tes32::GraphicsDevice::GraphicsController::RenderThread()
{
	int start, movement, end;
	Tes32::GraphicsDevice::InternalTypes::ColorPixel* vram = this->display_buffer;

	start = 0;
	movement = 1;
	end = 480;



	while (this->Hold) {
		if (this->KeepRendering) {
			for (int y = start; y != end; y++) {
				for (int x = 0; x != this->ctx_size.x; x++) {


					SetPixel(
						render_ctx,
						x, y,
						RGB(
							display_buffer[x + this->ctx_size.x * y].r,
							display_buffer[x + this->ctx_size.x * y].g,
							display_buffer[x + this->ctx_size.x * y].b
						)
					);

				}
			}
		}
		//while(Tes32::GraphicsDevice::Optimizations::CheckForDifferenceInRenderBuffer(vram, this->display_buffer, this->graphicsmode) == true){}
	}
}
void Tes32::GraphicsDevice::GraphicsController::RenderPixel(int x, int y)
{
	int start, movement, end;
	Tes32::GraphicsDevice::InternalTypes::ColorPixel* vram = this->display_buffer;

	start = 0;
	movement = 1;
	end = 480;
			SetPixel(
				render_ctx,
				x, y,
				RGB(
					display_buffer[x + this->ctx_size.x * y].r,
					display_buffer[x + this->ctx_size.x * y].g,
					display_buffer[x + this->ctx_size.x * y].b
				)
			);


}
void Tes32::GraphicsDevice::GraphicsController::WriteToVideoMemory(int x, int y, Tes32::GraphicsDevice::InternalTypes::ColorPixel data)
{
	this->display_buffer[x + this->ctx_size.x * y] = data;
}

