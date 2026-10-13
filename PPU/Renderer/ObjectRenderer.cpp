#include "pch.h"

#include "ObjectRenderer.h"

#define X_COORD 0
#define INDEX 1
#define PIXEL_INDEX 2

#include "PPU/PPU.h"
//#include "Utils/Addresses.h"

ObjectRenderer::ObjectRenderer(PPU* ppu)
	: mPPU(ppu)
{

	mObjectsOAMIndex.reserve(LINE_OBJ_LIMIT);
	mCurrentLinePixelsInfos.reserve(SCREEN_WIDTH);
	mCurrentLinePixelsInfos.assign(SCREEN_WIDTH, { -1, -1, -1 });
}

void ObjectRenderer::renderScanline()
{
	if (!mPPU->getLCDControl().flags.OBJEnable)
	{
		return;
	}

	mObjectsOAMIndex.clear();
	mCurrentLinePixelsInfos.assign(SCREEN_WIDTH, { -1, -1, -1 });

	u8 spriteHeightMode = mPPU->getLCDControl().flags.OBJSize ? 16 : 8;

	storeObjectsInCurrentLine(spriteHeightMode);
	storePixelsInfos(spriteHeightMode);
	renderCurrentLineObjectsPixels(spriteHeightMode);
}

inline void ObjectRenderer::storeObjectsInCurrentLine(u8 spriteHeightMode)
{
	// OAM scan: the first 10 objects (OAM order) covering this line. Y is stored + 16, so it must be
	// computed in int: with u8 an object partly above the screen (Y < 16) wrapped and vanished.
	const int ly = mPPU->readLY();
	for (int i = 0; i < MAX_OBJECTS && mObjectsOAMIndex.size() < LINE_OBJ_LIMIT; i++)
	{
		const int objectYOnScreen = static_cast<int>(mPPU->readOAM_YPos(i)) - 16;
		if (ly >= objectYOnScreen && ly < objectYOnScreen + spriteHeightMode)
			mObjectsOAMIndex.emplace_back(i);
	}
}

inline void ObjectRenderer::storePixelsInfos(u8 spriteHeightMode)
{
	// DMG object-to-object priority: smaller X wins, then lower OAM index (= earlier in the list).
	// Transparent pixels (color 0) never claim a pixel.
	for (const auto& objOamIndex : mObjectsOAMIndex)
	{
		const int16_t objectXOnScreen = static_cast<int16_t>(mPPU->readOAM_XPos(objOamIndex)) - 8; // X is stored + 8

		for (int i = 0; i < TILE_WIDTH; i++)
		{
			const int x = objectXOnScreen + i;
			if (x < 0 || x >= SCREEN_WIDTH)
				continue;
			if (getPixelColorID(objOamIndex, i, spriteHeightMode) == 0)
				continue;

			auto& info = mCurrentLinePixelsInfos[x];
			if (info[INDEX] == -1 || objectXOnScreen < info[X_COORD])
				info = { objectXOnScreen, static_cast<int16_t>(objOamIndex), static_cast<int16_t>(i) };
		}
	}
}




inline u8 ObjectRenderer::getPixelColorID(u8 objOamIndex, u8 currentXTilePixel, u8 spriteHeightMode) const
{
	OAM::Object object = mPPU->readOAM(objOamIndex);
	OAM::Attributes_Flags objectFlags = object.AttributeFlags;

	int16_t objectYOnScreen = object.YPos - 16;

	u16 lineData;

	u8 objectTileIndex = spriteHeightMode == 16 ? object.tileIndex & 0xFE : object.tileIndex;
	u16 tileAddress = VRAM_BEG_ADDRESS + objectTileIndex * 16;

	u8 lineYInTile = mPPU->readLY() - objectYOnScreen;


	if (!objectFlags.attr.YFlip)
	{
		u8 LSB = mPPU->readFromMemory(tileAddress + (2 * lineYInTile));
		u8 MSB = mPPU->readFromMemory(tileAddress + (2 * lineYInTile) + 1);
		lineData = JOIN_BYTES(MSB, LSB);
	}
	else
	{
		u8 LSB = mPPU->readFromMemory(tileAddress + 2 * (spriteHeightMode - lineYInTile - 1));
		u8 MSB = mPPU->readFromMemory(tileAddress + 2 * (spriteHeightMode - lineYInTile - 1) + 1);
		lineData = JOIN_BYTES(MSB, LSB);
	}

	u8 pixelColorID = 0;


	if (!objectFlags.attr.XFlip)
	{
		u8 pixelColorIDMSB = (lineData >> (8 + (7 - currentXTilePixel))) & 0x01;
		u8 pixelColorIDLSB = (lineData >> (7 - currentXTilePixel)) & 0x01;
		pixelColorID = (pixelColorIDMSB << 1) + pixelColorIDLSB;
	}
	else
	{
		u8 pixelColorIDMSB = (lineData >> (8 + currentXTilePixel)) & 0x01;
		u8 pixelColorIDLSB = (lineData >> currentXTilePixel) & 0x01;
		pixelColorID = (pixelColorIDMSB << 1) + pixelColorIDLSB;
	}

	return pixelColorID;

}

inline void ObjectRenderer::renderCurrentLineObjectsPixels(u8 spriteHeightMode)
{
	const int ly = mPPU->readLY();
	for (int pixel = 0; pixel < SCREEN_WIDTH; pixel++)
	{
		const auto& pixelInfo = mCurrentLinePixelsInfos[pixel];
		if (pixelInfo[INDEX] == -1)
			continue;

		OAM::Object object = mPPU->readOAM(pixelInfo[INDEX]);
		OAM::Attributes_Flags objectFlags = object.AttributeFlags;

		// Priority bit = 1 (BG over OBJ): the object only shows where BG/window color is 0. It used
		// to hide such objects completely.
		if (objectFlags.attr.priority == 0x01 && mPPU->getBGColorIndex(pixel) != 0)
			continue;

		u8 pixelColorID = getPixelColorID(pixelInfo[INDEX], pixelInfo[PIXEL_INDEX], spriteHeightMode);
		u8 palette = objectFlags.attr.DMGPalette ? mPPU->readOBP1() : mPPU->readOBP0();
		mPPU->renderPixel(pixelColorID, pixel, ly, palette, true);
	}
}