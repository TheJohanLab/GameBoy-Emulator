#include "pch.h"

#include "WindowRenderer.h"

#include "PPU/PPU.h"
//#include "Utils/Addresses.h"

WindowRenderer::WindowRenderer(PPU* ppu)
	:mPPU(ppu)
{
}

void WindowRenderer::renderScanline()
{
	auto lcdc = mPPU->getLCDControl().flags;
	if (!lcdc.BG_WindowEnable || !lcdc.windowEnable)
		return;

	const int ly = mPPU->readLY();
	const int wx = mPPU->readWX();
	if (ly < mPPU->readWY() || wx > 166)
		return;

	// The window has its own line counter: it only advances on lines where the window was drawn
	// (LY - WY is wrong as soon as the window is hidden or moved during the frame).
	const u8 lineInWindow = mPPU->getWindowLine();
	const u8 tileYInWindow = lineInWindow / 8;
	const u8 pixelYInTile = lineInWindow % 8;

	const u8 tileMapNumber = lcdc.windowTileMap;          // LCDC.6
	const u8 tileDataAddressingType = lcdc.BG_WindowTiles; // LCDC.4

	const int xPosOnScreen = wx - 7; // negative when WX < 7
	for (int x = (xPosOnScreen < 0 ? 0 : xPosOnScreen); x < SCREEN_WIDTH; x++)
	{
		const int xInWindow = x - xPosOnScreen;
		const u8 tileXInWindow = xInWindow / 8;

		std::variant<u8, int8_t> tileIndex = tileDataAddressingType == 1
			? std::variant<u8, int8_t>(mPPU->readIndexInTileMap(tileXInWindow, tileYInWindow, tileMapNumber))
			: std::variant<u8, int8_t>(static_cast<int8_t>(mPPU->readIndexInTileMap(tileXInWindow, tileYInWindow, tileMapNumber)));

		u16 tileIndexInVRAM = mPPU->getTileIndexInVRAM(tileIndex, tileDataAddressingType);
		u8 pixelColorID = getCurrentPixelColorID(tileIndexInVRAM, xInWindow % 8, pixelYInTile);

		mPPU->renderPixel(pixelColorID, x, ly, mPPU->getBGP().byte, false);
	}

	mPPU->markWindowLineDrawn();
}

u8 WindowRenderer::getCurrentPixelColorID(u16 tileIndexInVRAM, u8 pixelXInTile, u8 pixelYInTile)
{
	// 2 bytes per tile line: low bits first, then high bits
	u16 lineIndexInVRAM = tileIndexInVRAM + (pixelYInTile * 2);
	u8 lineLSB = mPPU->readFromMemory(VRAM_BEG_ADDRESS + lineIndexInVRAM);
	u8 lineMSB = mPPU->readFromMemory(VRAM_BEG_ADDRESS + lineIndexInVRAM + 1);

	u8 pixelColorIdLSB = (lineLSB >> (7 - pixelXInTile)) & 0x01;
	u8 pixelColorIdMSB = (lineMSB >> (7 - pixelXInTile)) & 0x01;
	return pixelColorIdLSB + (pixelColorIdMSB << 1);
}
