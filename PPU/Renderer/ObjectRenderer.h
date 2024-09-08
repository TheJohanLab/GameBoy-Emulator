#pragma once

#include "IRenderer.h"
#include "Utils/Utils.h"
#include <vector>

class PPU;

class ObjectRenderer: public IRenderer
{
private:
	PPU* mPPU;
	std::vector<u8> mObjectsOAMIndex;	
	std::vector<std::array<int16_t, 3>> mCurrentLinePixelsInfos;


public:
	ObjectRenderer(PPU* ppu);

	void renderScanline() override;

private:
	inline void storeObjectsInCurrentLine(u8 spriteHeightMode);
	inline void storePixelsInfos(u8 spriteHeightMode);
	void handleObjectsOverlap(int16_t objectXOnScreen, u8 objOamIndex, u8 currentTilePixel, u8 spriteHeightMode);
	inline u8 getPixelColorID(u8 objOamIndex, u8 currentXTilePixel, u8 spriteHeightMode) const;
	inline void renderCurrentLineObjectsPixels(u8 spriteHeightMode);

};

