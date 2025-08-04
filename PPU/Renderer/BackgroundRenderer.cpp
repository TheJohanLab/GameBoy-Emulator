#include "pch.h"

#include "BackgroundRenderer.h"

//#include "Utils/Utils.h"
#include "PPU/PPU.h"
//#include "Utils/Addresses.h"
#include "Utils/ScreenColors.h"

BackgroundRenderer::BackgroundRenderer(PPU* ppu)
	:mPPU(ppu)
{
}

void BackgroundRenderer::renderScanline()
{
	//BG desactive : tout s'affiche en blanc

	if (!mPPU->getLCDControl().flags.BG_WindowEnable) 
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
			mPPU->renderPixel(3, x, mPPU->readLY(), mPPU->getBGP().byte, false);
	
		return;
	}

// On charge la palette
	auto backgroundPalette = mPPU->getBGP();

	//Numero de la TileMap utilisee (LCDC.3)
	u8 tileMapNumber = mPPU->getLCDControl().flags.BGtileMap;

	//Type d'adressage de la TileData (LCDC.4)
	u8 tileDataAddressingType = mPPU->getLCDControl().flags.BG_WindowTiles;

	// On recpere l'index Y (vertical) de la tile dans la tilemap en cours
	// /8 car une tile est composée de 8 x 8 pixels
	// %32 pour gerer le wrapping sur la tilemap
	u8 tileY = ((mPPU->readSCY() + mPPU->readLY()) / 8) % 32;

	// On recupere l'index Y (vertical) du pixel dans la tile en cours
	u8 pixelYInTile = (mPPU->readSCY() + mPPU->readLY()) % 8;

	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		// On recupere l'index X (horizontal) de la tile dans la tilemap en cours
		u8 tileX = ((mPPU->readSCX() + x) / 8) % 32;

		// On recupere - dans la tilemap - l'index de la tile dans la tiledata
		std::variant<u8, int8_t> tileIndex;

		tileIndex = tileDataAddressingType == 1
			? std::variant<u8, int8_t>(mPPU->readIndexInTileMap(tileX, tileY, tileMapNumber))
			: std::variant<u8, int8_t>(static_cast<int8_t>(mPPU->readIndexInTileMap(tileX, tileY, tileMapNumber)));


		u16 tileIndexInVRAM = mPPU->getTileIndexInVRAM(tileIndex, tileDataAddressingType);
		if (pixelYInTile == 2)
			int a{ 1 };
		u8 pixelColorID = getCurrentPixelColorID(tileIndexInVRAM, x, pixelYInTile);


		mPPU->renderPixel(pixelColorID, x, mPPU->readLY(), mPPU->getBGP().byte, false);
	}
}

u8 BackgroundRenderer::getCurrentPixelColorID(u16 tileIndexInVRAM, u8 currXIndex, u8 pixelYInTile)
{
	// * 2 car une ligne d'une tile est composée de 2 bytes
	u16 lineIndexInVRAM = tileIndexInVRAM + (pixelYInTile * 2);

	// On récupère les 2 lignes de bits
	u8 lineLSB = mPPU->readFromMemory(VRAM_BEG_ADDRESS + lineIndexInVRAM);
	u8 lineMSB = mPPU->readFromMemory(VRAM_BEG_ADDRESS + lineIndexInVRAM + 1);

	u8 pixelXInTile = (mPPU->readSCX() + currXIndex) % 8;
	u8 pixelColorIdLSB = (lineLSB >> (7 - pixelXInTile)) & 0x01;
	u8 pixelColorIdMSB = (lineMSB >> (7 - pixelXInTile)) & 0x01;
	 
	return pixelColorIdLSB + (pixelColorIdMSB << 1);
}
