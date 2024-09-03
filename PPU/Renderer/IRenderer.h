#pragma once

class IRenderer
{
public:
	virtual void renderScanline() = 0;
private:
	virtual void getCurrentPixelColorID() = 0;
};
