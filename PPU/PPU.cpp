#include "PPU.h"
#include "../Utils/Addresses.h"
#include "../Utils/Log.h"


PPU::PPU(Bus* bus, Screen* screen)
	:mBus(bus), mScreen(screen)
{
	initializePPU();
}

PPU::~PPU()
{

}

//FF40
LCD_control PPU::getLCDControl() const
{
	LCD_control flags;
	flags.byte = mBus->read(LCD_CONTROL);
	return flags;
}

//FF41
LCD_status PPU::getLCDStatus() const
{
	LCD_status flags;
	flags.byte = mBus->read(LCD_STATUS);
	return flags;
}

void PPU::setLCDControl(const u8 flags)
{
	mBus->write(LCD_CONTROL, flags);
}

void PPU::setLCDStatus(const u8 flags)
{
	mBus->write(LCD_STATUS, flags);
}

u8 PPU::getPPUMode() const
{
	return getLCDStatus().flags.PPUMode;
}

void PPU::setPPUMode(u8 mode)
{
	LCD_status flags = getLCDStatus();
	flags.flags.PPUMode = mode & (0x03);
	setLCDStatus(flags.byte);

}


/// -------------------------- ///
/// ---------- OAM ----------- ///
/// -------------------------- ///
/// 
void PPU::writeOAM(u8 index, const u8& YPos, const u8& XPos, const u8& tileIndex, const u8& attrs)
{
	mOAM->write(index, YPos, XPos, tileIndex, attrs);

	u16 objectAddr = OAM_BEG_ADDRESS + 4 * index;
	mBus->write(objectAddr, YPos);
	mBus->write(objectAddr + 1, XPos);
	mBus->write(objectAddr + 2, tileIndex);
	mBus->write(objectAddr + 3, attrs);

}

void PPU::writeOAM_YPos(u8 index, const u8& data)
{
	mOAM->writeYPos(index, data);
	u16 objectAddr = OAM_BEG_ADDRESS + 4 * index;
	mBus->write(objectAddr, data);
}

void PPU::writeOAM_XPos(u8 index, const u8& data)
{
	mOAM->writeXPos(index, data);
	u16 objectAddr = OAM_BEG_ADDRESS + 4 * index;
	mBus->write(objectAddr + 1, data);
}

void PPU::writeOAM_TileIndex(u8 index, const u8& data)
{
	mOAM->writeTileIndex(index, data);

	u16 objectAddr = OAM_BEG_ADDRESS + 4 * index;
	mBus->write(objectAddr + 2, data);
}

void PPU::writeOAM_Attrs(u8 index, const u8& data)
{
	mOAM->writeAttrs(index, data);

	u16 objectAddr = OAM_BEG_ADDRESS + 4 * index;
	mBus->write(objectAddr + 3, data);
}

OAM::Object PPU::readOAM(u8 index) const
{
	return mOAM->read(index);
}

u8 PPU::readOAM_YPos(u8 index) const
{
	return mOAM->readYPos(index);
}

u8 PPU::readOAM_XPos(u8 index) const
{
	return mOAM->readXPos(index);
}

u8 PPU::readOAM_TileIndex(u8 index) const
{
	return mOAM->readTileIndex(index);

}

u8 PPU::readOAM_Attrs(u8 index) const
{
	return mOAM->readAttrs(index);

}

//FF42
u8 PPU::readSCY() const
{
	return mBus->read(SCY);
}

//FF43
u8 PPU::readSCX() const
{
	return mBus->read(SCX);
}

//FF44
u8 PPU::readLY() const
{
	return mLY;
	//return mBus->read(LY);
}

//FF45
u8 PPU::readLYC() const
{
	return mBus->read(LY_COMPARE);
}

void PPU::incLY()
{
	mLY = (mLY + 1) % 144;
	//u8 ly = mBus->read(LY);
	mBus->write(LY, mLY);
}

void PPU::incSCY()
{
	u8 scy = mBus->read(SCY);
	mBus->write(SCY, (scy + 1) % 256);
}

//FF47
Palette_data PPU::getBGP() const
{
	Palette_data flags;
	flags.byte = mBus->read(BG_PALETTE);
	return flags;
}

void PPU::setBGP(const u8 flags)
{
	mBus->write(BG_PALETTE, flags);
}

//FF48
u8 PPU::readOBP0() const
{
	return mBus->read(OBP0);
}

void PPU::setOBP0(const u8 flags)
{
	mBus->write(OBP0, flags);
}

//FF49
 u8 PPU::readOBP1() const
{
	return mBus->read(OBP1);
}

void PPU::setOBP1(const u8 flags)
{
	mBus->write(OBP1, flags);
}



//FF4A
u8 PPU::readWY() const
{
	return  mBus->read(WINDOW_Y);
}

//FF4B
u8 PPU::readWX() const
{
	return  mBus->read(WINDOW_X);
}

void PPU::render(u8 cycle)
{
	/*for (int i = 0; i < 160; i++)
	{
		for (int j = 0; j < 144; j++)
		{
			renderPixel(0x00, i, j);
			// ARGB
		}
	}*/

	/*
	std::array<u8, 16> tileTest = {
	0b00101111,0b11111000,
	0b00110000,0b00001100,
	0b00110000,0b00001100,
	0b00110000,0b00001100,
	0b00110111,0b11111100,
	0b00010101,0b11011100,
	0b00110111,0b01111000,
	0b00101111,0b11100000
	};

	for (int j = 0; j < 16; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			//								PIXEL ID		    X coord		   Y coord	
			renderPixel(tileTest[j] >> (2*(4 - (i+1))) & 0x03, 50+i+(4*(j%2)), 50+(j/2));
		}
	}*/


	

	/* En fonction du cycle
	*	1 frame = 70224 dots
	*	1 scanline = 456 dots
	*		2 : OAM SCAN : 80 dots	
	*		3 : DRAWING  : 172-289 dots
	*		0 : HBLANK	 : 87-204 dots (376 - DRAWING)
	*		1 : VBLANK	 : 10 scanlines = 4560 dots
	*/

	//setPPUMode(PPU_DRAWING);

	mPPUModeDots += cycle;

	switch (getPPUMode())
	{
		//Mode 0
	case PPU_HBLANK :
		// fin de scanline
		
		if (mPPUModeDots >= PPU_HBLANK_DOTS) 
		{
			mPPUModeDots -= PPU_HBLANK_DOTS;
			draw();
			incLY();
			//incSCY();
			setPPUMode(PPU_OAM_SCAN);
			// On passe à la ligne suivante

			/* Si ligne suivante = 144 :
			*   On passe à VBLANK
			*	On a fait toutes les lignes, on render l'image
			*	Interrupt ?
			*/

			/* Sinon :
			*	On passe en OAM pour recommencer
			*	Interrupt ?
			*/


		}
		
		break;

		 // Mode 1
	case PPU_VBLANK :

		if (mPPUModeDots >= PPU_VBLANK_DOTS) 
		{

			mPPUModeDots -= PPU_VBLANK_DOTS;
			// 10 scanlines

			// On incrémente la ligne
			incLY();

			// Si ligne suivante = 154 : on revient en haut et passe en OAM
			// Interrupt ?
			setPPUMode(PPU_OAM_SCAN);
		}


		break;

		//Mode 2
	case PPU_OAM_SCAN :
		// On décrémente les cycles et on passe en DRAWING

		if (mPPUModeDots >= PPU_OAM_SCAN_DOTS)
		{
			//TODO gerer les dots dans le CPU
			mPPUModeDots -= cycle;
			setPPUMode(PPU_DRAWING);
		}
		break;

		//Mode 3
	case PPU_DRAWING :
		// Render Scanline

		renderScanline();
		/*for (u8 i = 0; i < SCREEN_HEIGHT; i++)
		{
			
		}*/

		if (mPPUModeDots >= PPU_DRAWING_DOTS)
		{
			mPPUModeDots -= PPU_DRAWING_DOTS;
			auto ly = readLY();
			
			if (ly >= SCREEN_HEIGHT - 1)
				setPPUMode(PPU_HBLANK);
			else
				setPPUMode(PPU_VBLANK);
			
		}
		// On passe en HBLANK
		// Interrupt ?

		break;
	}

	//mScreen->render(mPixelArray);
	
}

void PPU::renderScanline()
{
	// Render Background Scanline

	renderBGScanline();

	// Si Window activée : render Window ScanLine

	renderWindowScanline();
	
	// On copie les pixels de BG+W dans le tableau à afficher

	// Si OBJ activé : render OBJ Scanline

	renderOBJScanline();
}

void PPU::renderBGScanline()
{
	/* LCDC.0=0
	*   BG désactivé : tout s'affiche en blanc
	*/

	// On charge la palette
	auto backgroundPalette = getBGP();

	//Numéro de la TileMap utilisée (LCDC.3)
	u8 tileMapNumber = getLCDControl().flags.BGtileMap;

	//Type d'adressage de la TileData (LCDC.4)
	u8 tileDataAddressingType = getLCDControl().flags.BG_WindowTiles;

	// On récpuère l'index Y (vertical) de la tile dans la tilemap en cours
	// /8 car une tile est composée de 8 x 8 pixels
	// %32 pour gérer le wrapping sur la tilemap
	u8 tileY = ((readSCY() + readLY()) / 8) % 32;

	// On récupère l'index Y (vertical) du pixel dans la tile en cours
	u8 pixelYInTile = (readSCY() + readLY()) % 8;

	for (int x = 0; x < 160; x++)
	{
		// On récupère l'index X (horizontal) de la tile dans la tilemap en cours
		u8 tileX = ((readSCX() + x) / 8) % 32;

		// On récupère - dans la tilemap - l'index de la tile dans la tiledata
		std::variant<u8, int8_t> tileIndex;
		u16 tileIndexInVRAM;


		tileIndex = tileDataAddressingType == 1
			? std::variant<u8, int8_t>(readIndexInTileMap(tileX, tileY, tileMapNumber))
			: std::variant<u8, int8_t>(static_cast<int8_t>(readIndexInTileMap(tileX, tileY, tileMapNumber)));


		tileIndexInVRAM = getTileIndexInVRAM(tileIndex, tileDataAddressingType);

		// * 2 car une ligne d'une tile est composée de 2 bytes
		u16 lineIndexInVRAM = tileIndexInVRAM + (pixelYInTile * 2);

		// On récupère les 2 lignes de bits
		u8 lineLSB = mBus->read(VRAM_BEG_ADDRESS + lineIndexInVRAM);
		u8 lineMSB = mBus->read(VRAM_BEG_ADDRESS + lineIndexInVRAM + 1);

		u8 pixelXInTile = (readSCX() + x) % 8;
		u8 pixelColorIdLSB = (lineLSB >> (7 - pixelXInTile)) & 0x01;
		u8 pixelColorIdMSB = (lineMSB >> (7 - pixelXInTile)) & 0x01;
		u8 pixelColorID = pixelColorIdLSB + (pixelColorIdMSB << 1);

		renderPixel(pixelColorID, x, readLY(), getBGP().byte, false);
	}


	// Adressage TileData
}

void PPU::renderWindowScanline()
{
	/* LCDC.5=0
	*   Window désactivée
	*/

	// On récupère le numéro de ligne dans la Window à afficher
	int16_t lineYInWindow = readLY() - readWY();
	if (lineYInWindow < 0)
		return;

	// On charge la palette
	auto backgroundPalette = getBGP();

	//Numéro de la TileMap utilisée (LCDC.6)
	u8 tileMapNumber = getLCDControl().flags.windowTileMap;

	//Type d'adressage de la TileData (LCDC.4)
	u8 tileDataAddressingType = getLCDControl().flags.BG_WindowTiles;

	u8 tileYInWindow = lineYInWindow / 8;
	u8 pixelYInTile = lineYInWindow % 8;

	int16_t xPosOnScreen = readWX() - 7;
	for (int x = 0; x < 160; x++)
	{
		// On récupère l'index X (horizontal) de la tile dans la tilemap en cours
		if (x < xPosOnScreen)
			continue;

		// On récupère - dans la tilemap - l'index de la tile dans la tiledata
		u8 tileXInWindow = (x - xPosOnScreen) / 8;

		// On récupère - dans la tilemap - l'index de la tile dans la tiledata
		std::variant<u8, int8_t> tileIndex;
		u16 tileIndexInVRAM;

		tileIndex = tileDataAddressingType == 1
			? std::variant<u8, int8_t>(readIndexInTileMap(tileXInWindow, tileYInWindow, tileMapNumber))
			: std::variant<u8, int8_t>(static_cast<int8_t>(readIndexInTileMap(tileXInWindow, tileYInWindow, tileMapNumber)));

		tileIndexInVRAM = getTileIndexInVRAM(tileIndex, tileDataAddressingType);

		// * 2 car une ligne d'une tile est composée de 2 bytes
		u16 lineIndexInVRAM = tileIndexInVRAM + (pixelYInTile * 2);

		// On récupère les 2 lignes de bits
		u8 lineLSB = mBus->read(VRAM_BEG_ADDRESS + lineIndexInVRAM);
		u8 lineMSB = mBus->read(VRAM_BEG_ADDRESS + lineIndexInVRAM + 1);

		u8 pixelXInTile = (x - xPosOnScreen) % 8;
		u8 pixelColorIdLSB = (lineLSB >> (7 - pixelXInTile)) & 0x01;
		u8 pixelColorIdMSB = (lineMSB >> (7 - pixelXInTile)) & 0x01;
		u8 pixelColorID = pixelColorIdLSB + (pixelColorIdMSB << 1);

		renderPixel(pixelColorID, x, readLY(), getBGP().byte, false);

	}

}

#define X_COORD 0
#define INDEX 1
#define PIXEL_INDEX 2

void PPU::renderOBJScanline()
{

	// On récupère les 10 premiers objects de la line dans l'OAM
	std::vector<u8> objectsOAMIndex;
	objectsOAMIndex.reserve(LINE_OBJ_LIMIT);

	mObjectsOAMIndex.clear();
	mCurrentLinePixelsInfos.assign(SCREEN_WIDTH, { -1, -1, -1 });

	u8 spriteHeightMode = getLCDControl().flags.OBJSize ? 16 : 8;
	//u8 ly = readLY();
	
	storeObjectsInCurrentLine(spriteHeightMode);
	storePixelsInfos(spriteHeightMode);
	renderCurrentLineObjectsPixels(spriteHeightMode);

}

// ------------------------------------//
//			PRIVATE METHODS
// ------------------------------------//
void PPU::initializePPU()
{
	mScreenColors[0] = { 0xFF, 0xE0, 0xF8, 0xD0 }; // WHITE
	mScreenColors[1] = { 0xFF, 0x88, 0xC0, 0x70 }; // LIGHT GREEN
	mScreenColors[2] = { 0xFF, 0x34, 0x68, 0x56 }; // DARK GREEN
	mScreenColors[3] = { 0xFF, 0x08, 0x18, 0x20 }; // BLACK

	setBGP(0b00011011);
	setOBP0(0b00011011);
	setOBP1(0b00011011);

	setWX(50);
	setWY(50);

	mOAM = std::make_shared<OAM>();
	mObjectsOAMIndex.reserve(LINE_OBJ_LIMIT);
	mCurrentLinePixelsInfos.reserve(SCREEN_WIDTH);
	mCurrentLinePixelsInfos.assign(SCREEN_WIDTH, { -1, -1, -1 });

}


void PPU::renderPixel(u8 pixelID, int x, int y, u8 palette, bool object)
{
	if (x < 0 || y < 0)
		return;

	//if (object && pixelID == 0x00)
	//	return;

	Pixel pixelColor = mScreenColors[palette >> (2 * pixelID) & 0x03];
	mPixelArray[y][x] = pixelColor;
}


u8 PPU::readIndexInTileMap(u8 xIndex, u8 yIndex, u8 tileMapId) const
{
	//400 est la taille d'une tilemap
	return mBus->read(VRAM_BEG_ADDRESS + TILEMAPS_OFFSET + (tileMapId * 0x0400) + (yIndex*32) + xIndex);
}


inline void PPU::storeObjectsInCurrentLine(u8 spriteHeightMode) 
{
	u8 objCnt = 0;
	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		auto objectY = mOAM->getObjects()[i].YPos;
		u8 objectYOnScreen = objectY - 16;

		if (mLY >= (objectYOnScreen) && mLY < objectYOnScreen + spriteHeightMode)
		{
			mObjectsOAMIndex.emplace_back(i);
			objCnt++;
		}

		if (objCnt >= LINE_OBJ_LIMIT)
			break;
	}
}

inline void PPU::storePixelsInfos(u8 spriteHeightMode)
{
	// 1 - X bas = priorité haute
	// 2 - index bas = priorité haute

	for (const auto& objOamIndex : mObjectsOAMIndex)
	{
		OAM::Object object = mOAM->getObjects()[objOamIndex];

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

void PPU::handleObjectsOverlap(int16_t objectXOnScreen, u8 objOamIndex, u8 currentTilePixel, u8 spriteHeightMode)
{
	//TODO recuperer les pixelsID pour pouvoir gerer la transparence en cas d'overlap	

	if (mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][X_COORD] != objectXOnScreen)
	{
		if (objectXOnScreen < mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][X_COORD])
		{
			u8 pixelID = getCurrentObjectPixelId(
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
			u8 pixelID = getCurrentObjectPixelId(
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
	
		
			u8 pixelID = getCurrentObjectPixelId(
				mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][INDEX],
				mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][PIXEL_INDEX],
				spriteHeightMode);

			if (pixelID == 0)
			{
				mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][X_COORD] = objectXOnScreen;
				mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][INDEX] = objOamIndex;
				mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][PIXEL_INDEX] = currentTilePixel;
			}

			//mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][X_COORD] = objectXOnScreen;
			//mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][INDEX] = objOamIndex;
			//mCurrentLinePixelsInfos[objectXOnScreen + currentTilePixel][PIXEL_INDEX] = currentTilePixel;
		
		
	}
}

inline u8 PPU::getCurrentObjectPixelId(u8 objOamIndex, u8 currentXTilePixel, u8 spriteHeightMode) const
{
	OAM::Object object = mOAM->getObjects()[objOamIndex];
	OAM::Attributes_Flags objectFlags = object.AttributeFlags;

	int16_t objectYOnScreen = object.YPos - 16;

	u16 lineData;

	u8 objectTileIndex = spriteHeightMode == 16 ? object.tileIndex & 0xFE : object.tileIndex;
	u16 tileAddress = VRAM_BEG_ADDRESS + objectTileIndex * 16;

	u8 lineYInTile = mLY - objectYOnScreen;


	if (!objectFlags.attr.YFlip)
	{
		u8 LSB = mBus->read(tileAddress + (2 * lineYInTile));
		u8 MSB = mBus->read(tileAddress + (2 * lineYInTile) + 1);
		lineData = JOIN_BYTES(MSB, LSB);
	}
	else
	{
		u8 LSB = mBus->read(tileAddress + 2 * (spriteHeightMode - lineYInTile - 1));
		u8 MSB = mBus->read(tileAddress + 2 * (spriteHeightMode - lineYInTile - 1) + 1);
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

inline void PPU::renderCurrentLineObjectsPixels(u8 spriteHeightMode)
{
	//for (const auto objOamIndex : objectsOAMIndex)
	//{
	for (int pixel = 0; pixel < SCREEN_WIDTH; pixel++)
	{
		const auto& pixelInfo = mCurrentLinePixelsInfos[pixel];

		if (pixelInfo[INDEX] == -1)
			continue;

		OAM::Object object = mOAM->getObjects()[pixelInfo[INDEX]];

		//int16_t objectYOnScreen = object.YPos - 16;
		//int16_t objectXOnScreen = object.XPos - 8;

		OAM::Attributes_Flags objectFlags = object.AttributeFlags;
		u8 pixelColorID = getCurrentObjectPixelId(
			pixelInfo[INDEX], pixelInfo[PIXEL_INDEX], spriteHeightMode
		);


		//u8 objectTileIndex = spriteHeightMode == 16 ? object.tileIndex & 0xFE : object.tileIndex;

		//u16 lineData;

		//u16 tileAddress = VRAM_BEG_ADDRESS + objectTileIndex * 16;

		//u8 lineYInTile = mLY - objectYOnScreen;


		//if (!objectFlags.attr.YFlip)
		//{
		//	u8 LSB = mBus->read(tileAddress + (2 * lineYInTile));
		//	u8 MSB = mBus->read(tileAddress + (2 * lineYInTile) + 1);
		//	lineData = JOIN_BYTES(MSB, LSB);
		//}
		//else
		//{
		//	u8 LSB = mBus->read(tileAddress + 2 * (spriteHeightMode - lineYInTile - 1));
		//	u8 MSB = mBus->read(tileAddress + 2 * (spriteHeightMode - lineYInTile - 1) + 1);
		//	lineData = JOIN_BYTES(MSB, LSB);
		//}

		////for (u8 pixelIndex = 0; pixelIndex < 8; pixelIndex++)
		////{
		//	//int16_t pixelXPos = objectXOnScreen + pixelIndex;
		//u8 pixelColorID = 0;

		////if (pixelXPos >= 0 && pixelXPos < SCREEN_WIDTH)
		////{
		//if (!objectFlags.attr.XFlip)
		//{
		//	u8 pixelColorIDMSB = (lineData >> (8 + (7 - pixelInfo[PIXEL_INDEX]))) & 0x01;
		//	u8 pixelColorIDLSB = (lineData >> (7 - pixelInfo[PIXEL_INDEX])) & 0x01;
		//	pixelColorID = (pixelColorIDMSB << 1) + pixelColorIDLSB;
		//}
		//else
		//{
		//	u8 pixelColorIDMSB = (lineData >> (8 + pixelInfo[PIXEL_INDEX])) & 0x01;
		//	u8 pixelColorIDLSB = (lineData >> pixelInfo[PIXEL_INDEX]) & 0x01;
		//	pixelColorID = (pixelColorIDMSB << 1) + pixelColorIDLSB;
		//}

		//}

		u8 palette = objectFlags.attr.DMGPalette ? readOBP1() : readOBP0();
		// TODO : appeler render avec la bonne palette
		renderPixel(pixelColorID, pixel, mLY, palette, true);
		//}


	}
}

inline u16 PPU::getTileIndexInVRAM(std::variant<u8, int8_t> tileIndex, u8 tileDataAddressingType) const
{
	//0 ou 1000 pour correspondre à l'adresse de depart de le bonne tilemap (8000 ou 9000)
	u16 tileAddressingOffset = tileDataAddressingType == 1 ? 0x0000 : 0x1000;

	return std::visit([&](auto&& index) -> u16 {
		return static_cast<u16>(tileAddressingOffset + (index * 16));
		}, tileIndex);
}




void PPU::setWX(u8 value)
{
	mBus->write(WINDOW_X, value);
}

void PPU::setWY(u8 value)
{
	mBus->write(WINDOW_Y, value);
}

void PPU::startDMATransfer(const u8& address)
{
	GBE_LOG_INFO("Start DMA Transfer");

	// address : 8 bits de poids fort de l'adresse : *0x100 pour décaler à gauche
	u16 sourceAddress = (static_cast<u16>(address) * 0x100);
	for (u8 objectIndex = 0x00; objectIndex < 40; objectIndex++ )
	{
		writeOAM(objectIndex, 
		mBus->read(sourceAddress | (objectIndex * 4)),
		mBus->read(sourceAddress | (objectIndex * 4 + 1)),
		mBus->read(sourceAddress | (objectIndex * 4 + 2)),
		mBus->read(sourceAddress | (objectIndex * 4 + 3)));
	}

	//TODO Attendre 160 mcycles ou 640 dots
}

void PPU::setCloseEventCallback(std::function<void()> callback)
{
	mScreen->setOnCloseEvent(callback);
}

void PPU::handleWindowEvents()
{
	mScreen->handleEvents();
}

void PPU::draw()
{
	mScreen->render(mPixelArray);
}
