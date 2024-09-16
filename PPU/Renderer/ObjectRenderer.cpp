#include "ObjectRenderer.h"

#define X_COORD 0
#define INDEX 1
#define PIXEL_INDEX 2

#include "PPU/PPU.h"
#include "Utils/Addresses.h"

ObjectRenderer::ObjectRenderer(PPU* ppu)
	: mPPU(ppu)
{

	mObjectsOAMIndex.reserve(LINE_OBJ_LIMIT);
	mCurrentLinePixelsInfos.reserve(SCREEN_WIDTH);
	mCurrentLinePixelsInfos.assign(SCREEN_WIDTH, { -1, -1, -1 });
}

void ObjectRenderer::renderScanline()
{
	// On récupère les 10 premiers objects de la line dans l'OAM
	std::vector<u8> objectsOAMIndex;
	objectsOAMIndex.reserve(LINE_OBJ_LIMIT);

	mObjectsOAMIndex.clear();
	mCurrentLinePixelsInfos.assign(SCREEN_WIDTH, { -1, -1, -1 });

	u8 spriteHeightMode = mPPU->getLCDControl().flags.OBJSize ? 16 : 8;
		
	storeObjectsInCurrentLine(spriteHeightMode);
	storePixelsInfos(spriteHeightMode);
	renderCurrentLineObjectsPixels(spriteHeightMode);
}

inline void ObjectRenderer::storeObjectsInCurrentLine(u8 spriteHeightMode)
{
	u8 objCnt = 0;
	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		auto objectY = mPPU->readOAM(i).YPos;
		u8 objectYOnScreen = objectY - 16;

		if (mPPU->readLY() >= (objectYOnScreen) && mPPU->readLY() < objectYOnScreen + spriteHeightMode)
		{
			mObjectsOAMIndex.emplace_back(i);
			objCnt++;
		}

		if (objCnt >= LINE_OBJ_LIMIT)
			break;
	}
}

inline void ObjectRenderer::storePixelsInfos(u8 spriteHeightMode)
{
	// 1 - X bas = priorité haute
	// 2 - index bas = priorité haute

	for (const auto& objOamIndex : mObjectsOAMIndex)
	{
		OAM::Object object = mPPU->readOAM(objOamIndex);

		int16_t objectXOnScreen = object.XPos - 8;

		for (int i = 0; i < TILE_WIDTH; i++)
		{
			// Current object doesn't overlap with any other object
			if (mCurrentLinePixelsInfos[objectXOnScreen + i][X_COORD] == -1)
			{
				mCurrentLinePixelsInfos[objectXOnScreen + i][X_COORD] = objectXOnScreen;
				mCurrentLinePixelsInfos[objectXOnScreen + i][INDEX] = objOamIndex;
				mCurrentLinePixelsInfos[objectXOnScreen + i][PIXEL_INDEX] = i;
			}

			//Current object overlaps
			else
			{
				handleObjectsOverlap(objectXOnScreen, objOamIndex, i, spriteHeightMode);
			}
		}
	}
}

void ObjectRenderer::handleObjectsOverlap(int16_t objectXOnScreen, u8 objOamIndex, u8 currentTilePixel, u8 spriteHeightMode)
{
	if (mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][X_COORD] != objectXOnScreen)
	{
		if (objectXOnScreen < mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][X_COORD])
		{
			u8 pixelID = getPixelColorID(
				objOamIndex,
				currentTilePixel,
				spriteHeightMode);

			if (pixelID != 0)
			{
				mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][X_COORD] = objectXOnScreen;
				mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][INDEX] = objOamIndex;
				mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][PIXEL_INDEX] = currentTilePixel;
			}
		}
		else
		{
			u8 pixelID = getPixelColorID(
				mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][INDEX],
				mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][PIXEL_INDEX],
				spriteHeightMode);

			if (pixelID == 0)
			{
				mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][X_COORD] = objectXOnScreen;
				mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][INDEX] = objOamIndex;
				mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][PIXEL_INDEX] = currentTilePixel;
			}
		}
	}
	else
	{
		u8 pixelID = getPixelColorID(
			mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][INDEX],
			mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][PIXEL_INDEX],
			spriteHeightMode);

		if (pixelID == 0)
		{
			mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][X_COORD] = objectXOnScreen;
			mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][INDEX] = objOamIndex;
			mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][PIXEL_INDEX] = currentTilePixel;
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

	for (int pixel = 0; pixel < SCREEN_WIDTH; pixel++)
	{
		const auto& pixelInfo = mCurrentLinePixelsInfos[pixel];

		if (pixelInfo[INDEX] == -1)
			continue;

		OAM::Object object = mPPU->readOAM(pixelInfo[INDEX]);

		OAM::Attributes_Flags objectFlags = object.AttributeFlags;
		u8 pixelColorID = getPixelColorID(
			pixelInfo[INDEX], pixelInfo[PIXEL_INDEX], spriteHeightMode
		);

		u8 palette = objectFlags.attr.DMGPalette ? mPPU->readOBP1() : mPPU->readOBP0();

		if (pixelColorID != 0x00 && objectFlags.attr.priority == 0x00)
		{
			mPPU->renderPixel(pixelColorID, pixel, mPPU->readLY(), palette, true);
		}

	}
}