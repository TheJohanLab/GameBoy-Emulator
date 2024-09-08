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
	inline u8 getCurrentPixelColorID(u8 tileIndex, u8 currXIndex, u8 xPosOnScreen, u8 pixelYInTile);

};

