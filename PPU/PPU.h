#pragma once

#include <array>
#include <memory>
#include <variant>
#include <cstdint>
#include <functional>

#include "Bus/Bus.h"
#include "Screen/Screen.h"
#include "Screen/ImGuiRenderer.h"
#include "OAM.h"

#include "Interrupts/InterruptsManager.h"

#define LINE_OBJ_LIMIT 10

class Registries;

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

	std::shared_ptr<Bus> mBus;
	std::shared_ptr<Screen> mScreen;
	std::shared_ptr<OAM> mOAM;
	std::array<std::array<Pixel, SCREEN_WIDTH>, SCREEN_HEIGHT> mPixelArray{ 0 };

	u8 mLY { 0 };
	std::vector<u8> mObjectsOAMIndex;
	std::vector<std::array<int16_t, 3>> mCurrentLinePixelsInfos;

	u16 mPPUModeDots{ 0 };
	std::array<Pixel, 4> mScreenColors;

	bool mIsScanlineDrawn = false;
	u8 mDotsElapsed = 0;

	//TO REMOVE LATER
	using onVBlankEvent = std::function<void(InterruptsTypes)>;
	onVBlankEvent mOnVBlank{ nullptr };

public:
	PPU(std::shared_ptr<Bus> bus, std::shared_ptr<Screen> screen);
	~PPU();

	Screen* getScreen() { return mScreen.get(); }

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
	void decSCY();
	void incSCX();


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

	u8 readFromMemory(u16 address) const;

	void render(u8 cycles);

	u8 renderPixelsScanline();

	void startDMATransfer(const u8& address);

	void setCloseEventCallback(std::function<void()> callback);
	void handleWindowEvents();

	u8 readIndexInTileMap(u8 xIndex, u8 yIndex, u8 tileMapId) const;
	u16 getTileIndexInVRAM(std::variant<u8, int8_t> tileIndex, u8 tileDataAddressingType) const;
	void renderPixel(u8 pixelColor, int x, int y, u8 palette, bool object = false);

	void executeFullFrameRender();
	void draw();

	void setTile(u8 tileIndex, const std::vector<u8>& tileData);
	void setTileMap(u8 tileMapIndex, const std::vector<u8>& tileMapData);


	//TO REMOVE LATER
	void waitForNextFrame();
	void setOnVBlankListener(onVBlankEvent onVBlank) { mOnVBlank = onVBlank; }
	void setRegistriesRef(Registries* registries);
	

private:

	void initializePPU();

	template<typename T>
	void renderScanline();
};


