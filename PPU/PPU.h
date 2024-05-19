#pragma once

#include <array>
#include "../Bus/Bus.h"
#include "../Screen/Screen.h"

struct Pixel
{
	u8 alpha = 0x00;
	u8 red = 0x00;
	u8 green = 0x00;
	u8 blue = 0x00;
};

class PPU
{
private:

	Bus* mBus;
	Screen* mScreen;
	std::array<std::array<Pixel, SCREEN_WIDTH>, SCREEN_HEIGHT> mPixelArray;

	u16 mPPUModeDots = 0;
	std::array<Pixel, 4> mScreenColors;

public:
	PPU(Bus* bus, Screen* screen);
	~PPU();

	LCD_control getLCDControl() const; //FF40
	LCD_status getLCDStatus() const; //FF41
	void setLCDControl(const u8 flags);
	void setLCDStatus(const u8 flags);

	u8 getPPUMode() const; //FF41.0-1
	void setPPUMode(const u8 mode); //FF41.0-1

	u8 readSCY() const; //FF42
	u8 readSCX() const; //FF43
	u8 readLY() const; //FF44
	u8 readLYC() const; //FF45


	BG_palette_data getBGP() const; //FF47
	void setBGP(const u8 flags);

	u8 readOBP0() const; // FF48
	u8 readOBP1() const; // FF49

	u8 readWY() const; //FF4A
	u8 readWX() const; //FF4B

	void render(u8 cycles);
	void renderScanline();
	void renderBGScanline();
	void renderWindowScanline();
	void renderOBJScanline();

private:

	void initializePPU();
	void renderPixel(u8 pixelColor, int i, int j);
};

