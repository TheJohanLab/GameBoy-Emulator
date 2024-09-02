#pragma once

#include <array>
#include <memory>
#include <variant>
#include <cstdint>

#include "../Bus/Bus.h"
#include "../Screen/Screen.h"
#include "OAM.h"


#define LINE_OBJ_LIMIT 10


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

	u8 mLY = 0;
	std::vector<u8> mObjectsOAMIndex;
	std::vector<std::array<int16_t, 3>> mCurrentLinePixelsInfos;

	u16 mPPUModeDots = 0;
	std::array<Pixel, 4> mScreenColors;

public:
	PPU(Bus* bus, Screen* screen);
	~PPU();

	Screen* getScreen() { return mScreen; }

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
	void incSCY();


	Palette_data getBGP() const; //FF47
	void setBGP(const u8 flags);

	u8 readOBP0() const; // FF48
	void setOBP0(const u8 flags);
	u8 readOBP1() const; // FF49
	void setOBP1(const u8 flags);

	u8 readWY() const; //FF4A
	u8 readWX() const; //FF4B
	void setWX(u8 value);
	void setWY(u8 value);


	void render(u8 cycles);
	void renderScanline();
	void renderBGScanline();
	void renderWindowScanline();
	void renderOBJScanline();

	void startDMATransfer(const u8& address);

	void setCloseEventCallback(std::function<void()> callback);
	void handleWindowEvents();

	void draw();

private:

	void initializePPU();
	void renderPixel(u8 pixelColor, int x, int y, u8 palette, bool object = false);
	u8 readIndexInTileMap(u8 xIndex, u8 yIndex, u8 tileMapId) const;

	inline void storeObjectsInCurrentLine(u8 spriteHeightMode);
	inline void storePixelsInfos(u8 spriteHeightMode);
	void handleObjectsOverlap(int16_t objectXOnScreen, u8 objOamIndex, u8 currentTilePixel, u8 spriteHeightMode);
	inline u8 getCurrentObjectPixelId(u8 objOamIndex, u8 currentXTilePixel, u8 spriteHeightMode) const;
	inline void renderCurrentLineObjectsPixels(u8 spriteHeightMode);
	inline u16 getTileIndexInVRAM(std::variant<u8, int8_t> tileIndex, u8 tileDataAddressingType) const;


};

