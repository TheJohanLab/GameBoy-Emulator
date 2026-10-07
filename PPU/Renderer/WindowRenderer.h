#pragma once

#include "IRenderer.h"

class PPU;

class WindowRenderer: public IRenderer
{
private:
	PPU* mPPU;

public:
	WindowRenderer(PPU* ppu);
	void renderScanline() override;

private:
	inline u8 getCurrentPixelColorID(u16 tileIndexInVRAM, u8 pixelXInTile, u8 pixelYInTile);

};

