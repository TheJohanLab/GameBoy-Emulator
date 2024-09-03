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
	void getCurrentPixelColorID() override;

};

