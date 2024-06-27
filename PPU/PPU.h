#pragma once

#include <array>
#include <memory>

#include "../Bus/Bus.h"
#include "../Screen/Screen.h"
#include "OAM.h"

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
	std::shared_ptr<OAM> mOAM;
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

	void writeOAM(u8 index, const u8& YPos, const u8& XPos, const u8& tileIndex, const u8& attrs);
	void writeOAM_YPos(u8 index, const u8& data);
	void writeOAM_XPos(u8 index, const u8& data);
	void writeOAM_TileIndex(u8 index, const u8& data);
	void writeOAM_Attrs(u8 index, const u8& data);

	OAM::Object readOAM(u8 index) const;
	u8 readOAM_YPos(u8 index) const;
	u8 readOAM_XPos(u8 index) const;
	u8 readOAM_TileIndex(u8 index) const;
	u8 readOAM_Attrs(u8 index) const;


	u8 readSCY() const; //FF42
	u8 readSCX() const; //FF43
	u8 readLY() const; //FF44
	u8 readLYC() const; //FF45

	void incLY();


	BG_palette_data getBGP() const; //FF47
	void setBGP(const u8 flags);

	u8 readOBP0() const; // FF48
	u8 readOBP1() const; // FF49

	u8 readWY() const; //FF4A
	u8 readWX() const; //FF4B
	void setWX(u8 value);
	void setWY(u8 value);


	void render(u8 cycles);
	void renderScanline();
	void renderBGScanline();
	void renderWindowScanline();
	void renderOBJScanline();

private:



	void initializePPU();
	void renderPixel(u8 pixelColor, int i, int j);
	u8 readIndexInTileMap(u8 xIndex, u8 yIndex) const;
};

