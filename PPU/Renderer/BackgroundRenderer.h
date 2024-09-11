#pragma once
#include "IRenderer.h"

class PPU;

class BackgroundRenderer: public IRenderer
{
private:
	PPU* mPPU;
public:
	BackgroundRenderer(PPU* ppu);
	void renderScanline() override;
private:
	inline u8 getCurrentPixelColorID(u16 tileIndexInVRAM, u8 currXIndex, u8 pixelYInTile);

};

