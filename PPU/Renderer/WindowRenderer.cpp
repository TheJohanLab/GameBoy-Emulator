#include "WindowRenderer.h"

#include "PPU/PPU.h"
#include "Utils/Addresses.h"

WindowRenderer::WindowRenderer(PPU* ppu)
	:mPPU(ppu)
{
}

void WindowRenderer::renderScanline()
{
	/* LCDC.5=0
	*   Window désactivée
	*/

	// On récupère le numéro de ligne dans la Window à afficher
	int16_t lineYInWindow = mPPU->readLY() - mPPU->readWY();
	if (lineYInWindow < 0)
		return;

	// On charge la palette
	auto backgroundPalette = mPPU->getBGP();

	//Numéro de la TileMap utilisée (LCDC.6)
	u8 tileMapNumber = mPPU->getLCDControl().flags.windowTileMap;

	//Type d'adressage de la TileData (LCDC.4)
	u8 tileDataAddressingType = mPPU->getLCDControl().flags.BG_WindowTiles;

	u8 tileYInWindow = lineYInWindow / 8;
	u8 pixelYInTile = lineYInWindow % 8;

	int16_t xPosOnScreen = mPPU->readWX() - 7;
	for (int x = 0; x < 160; x++)
	{
		// On récupère l'index X (horizontal) de la tile dans la tilemap en cours
		if (x < xPosOnScreen)
			continue;

		// On récupère - dans la tilemap - l'index de la tile dans la tiledata
		u8 tileXInWindow = (x - xPosOnScreen) / 8;

		// On récupère - dans la tilemap - l'index de la tile dans la tiledata
		std::variant<u8, int8_t> tileIndex;

		tileIndex = tileDataAddressingType == 1
			? std::variant<u8, int8_t>(mPPU->readIndexInTileMap(tileXInWindow, tileYInWindow, tileMapNumber))
			: std::variant<u8, int8_t>(static_cast<int8_t>(mPPU->readIndexInTileMap(tileXInWindow, tileYInWindow, tileMapNumber)));

		u16 tileIndexInVRAM = mPPU->getTileIndexInVRAM(tileIndex, tileDataAddressingType);
		u8 pixelColorID = getCurrentPixelColorID(tileIndexInVRAM, x, xPosOnScreen, pixelYInTile);

		mPPU->renderPixel(pixelColorID, x, mPPU->readLY(), mPPU->getBGP().byte, false);

	}
}

u8 WindowRenderer::getCurrentPixelColorID(u8 tileIndex, u8 currXIndex, u8 xPosOnScreen, u8 pixelYInTile)
{
	// * 2 car une ligne d'une tile est composée de 2 bytes
	u16 lineIndexInVRAM = tileIndex + (pixelYInTile * 2);

	// On récupère les 2 lignes de bits
	u8 lineLSB = mPPU->readFromMemory(VRAM_BEG_ADDRESS + lineIndexInVRAM);
	u8 lineMSB = mPPU->readFromMemory(VRAM_BEG_ADDRESS + lineIndexInVRAM + 1);

	u8 pixelXInTile = (currXIndex - xPosOnScreen) % 8;
	u8 pixelColorIdLSB = (lineLSB >> (7 - pixelXInTile)) & 0x01;
	u8 pixelColorIdMSB = (lineMSB >> (7 - pixelXInTile)) & 0x01;
	
	return pixelColorIdLSB + (pixelColorIdMSB << 1);
}
