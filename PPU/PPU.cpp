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
	return mBus->read(LY);
}

//FF45
u8 PPU::readLYC() const
{
	return mBus->read(LY_COMPARE);
}

void PPU::incLY()
{
	u8 ly = mBus->read(LY);
	mBus->write(LY, (ly + 1) % 144);

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

	setPPUMode(PPU_DRAWING);

	mPPUModeDots += cycle;

	switch (getPPUMode())
	{
		//Mode 0
	case PPU_HBLANK :
		// fin de scanline
		
		if (mPPUModeDots >= PPU_HBLANK_DOTS) 
		{
			mPPUModeDots -= PPU_HBLANK_DOTS;

			// On passe � la ligne suivante

			/* Si ligne suivante = 144 :
			*   On passe � VBLANK
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

			// On incr�mente la ligne

			// Si ligne suivante = 154 : on revient en haut et passe en OAM
			// Interrupt ?
			setPPUMode(PPU_OAM_SCAN);
		}


		break;

		//Mode 2
	case PPU_OAM_SCAN :
		// On d�cr�mente les cycles et on passe en DRAWING

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

		for (u8 i = 0; i < SCREEN_HEIGHT; i++)
		{
			renderScanline();
			incLY();
		}

		/*if (mPPUModeDots >= PPU_DRAWING_DOTS) 
		{
			mPPUModeDots -= PPU_DRAWING_DOTS;

			setPPUMode(PPU_HBLANK);
		}*/

		// On passe en HBLANK
		// Interrupt ?

		break;
	}

	mScreen->render(mPixelArray);
}

void PPU::renderScanline()
{
	// Render Background Scanline

	renderBGScanline();

	// Si Window activ�e : render Window ScanLine

	renderWindowScanline();
	
	// On copie les pixels de BG+W dans le tableau � afficher

	// Si OBJ activ� : render OBJ Scanline

	renderOBJScanline();
}

void PPU::renderBGScanline()
{
	/* LCDC.0=0
	*   BG d�sactiv� : tout s'affiche en blanc
	*/

	// On charge la palette
	auto backgroundPalette = getBGP();

	//A changer en fonction de LCD control
	u16 tileAddressingOffset = 0;

	// On r�cpu�re l'index Y (vertical) de la tile dans la tilemap en cours
	// /8 car une tile est compos�e de 8 x 8 pixels
	// %32 pour g�rer le wrapping sur la tilemap
	u8 tileY = ((readSCY() + readLY()) / 8) % 32;

	// On r�cup�re l'index Y (vertical) du pixel dans la tile en cours
	u8 pixelYInTile = (readSCY() + readLY()) % 8;

	for (int x = 0; x < 160; x++)
	{
		// On r�cup�re l'index X (horizontal) de la tile dans la tilemap en cours
		u8 tileX = ((readSCX() + x) / 8) % 32;

		// On r�cup�re - dans la tilemap - l'index de la tile dans la tiledata
		u16 tileIndex = readIndexInTileMap(tileX, tileY, 0);

		// TODO : g�rer le cas index n�gatif
		// 16 car une tile fait 16 bytes de long dans la VRAM
		u16 tileIndexInVRAM = (tileIndex + tileAddressingOffset) * 16;

		// * 2 car une ligne d'une tile est compos�e de 2 bytes
		u16 lineIndexInVRAM = tileIndexInVRAM + (pixelYInTile * 2);

		// On r�cup�re les 2 lignes de bits
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
	*   Window d�sactiv�e
	*/

	// On r�cup�re le num�ro de ligne dans la Window � afficher
	int16_t lineYInWindow = readLY() - readWY();
	if (lineYInWindow < 0)
		return;

	// On charge la palette
	auto backgroundPalette = getBGP();

	//A changer en fonction de LCD control (BLOCK)
	u16 tileAddressingOffset = 0x0000;

	u8 tileYInWindow = lineYInWindow / 8;
	u8 pixelYInTile = lineYInWindow % 8;

	int16_t xPosOnScreen = readWX() - 7;
	for (int x = 0; x < 160; x++)
	{
		// On r�cup�re l'index X (horizontal) de la tile dans la tilemap en cours
		if (x < xPosOnScreen)
			continue;

		// On r�cup�re - dans la tilemap - l'index de la tile dans la tiledata
		u8 tileXInWindow = (x - xPosOnScreen) / 8;

		// TODO : g�rer le cas index n�gatif
		// 16 car une tile fait 16 bytes de long dans la VRAM	
		u16 tileIndex = readIndexInTileMap(tileXInWindow, tileYInWindow, 1);

		// * 2 car une ligne d'une tile est compos�e de 2 bytes
		u16 tileIndexInVRAM = (tileIndex+ tileAddressingOffset) * 16;

		// * 2 car une ligne d'une tile est compos�e de 2 bytes
		u16 lineIndexInVRAM = tileIndexInVRAM + (pixelYInTile * 2);

		// On r�cup�re les 2 lignes de bits
		u8 lineLSB = mBus->read(VRAM_BEG_ADDRESS + lineIndexInVRAM);
		u8 lineMSB = mBus->read(VRAM_BEG_ADDRESS + lineIndexInVRAM + 1);

		u8 pixelXInTile = (x - xPosOnScreen) % 8;
		u8 pixelColorIdLSB = (lineLSB >> (7 - pixelXInTile)) & 0x01;
		u8 pixelColorIdMSB = (lineMSB >> (7 - pixelXInTile)) & 0x01;
		u8 pixelColorID = pixelColorIdLSB + (pixelColorIdMSB << 1);

		renderPixel(pixelColorID, x, readLY(), getBGP().byte, false);

	}

}

void PPU::renderOBJScanline()
{

	// On r�cup�re les 10 premiers objects de la line dans l'OAM
	std::vector<u8> objectsOAMIndex;
	objectsOAMIndex.reserve(LINE_OBJ_LIMIT);

	u8 spriteHeightMode = getLCDControl().flags.OBJSize ? 16 : 8;
	u8 ly = readLY();
	u8 objCnt = 0;

	for (int i = 0; i < MAX_OBJECTS; i ++)
	{
		auto objectY = mOAM->getObjects()[i].YPos;
		u8 objectYOnScreen = objectY - 16;

		if (ly >= (objectYOnScreen) && ly < objectYOnScreen + spriteHeightMode)
			objectsOAMIndex.emplace_back(i);

		if (objCnt >= MAX_OBJECTS)
			break;
	}

	for (const auto objOamIndex : objectsOAMIndex)
	{
		OAM::Object object = mOAM->getObjects()[objOamIndex];

		int16_t objectYOnScreen = object.YPos - 16;
		int16_t objectXOnScreen = object.XPos - 8;
		u8 objectTileIndex = spriteHeightMode == 16 ? object.tileIndex & 0xFE : object.tileIndex;
		OAM::Attributes_Flags objectFlags = object.AttributeFlags;

		u16 lineData;
		
		u16 tileAddress = VRAM_BEG_ADDRESS + objectTileIndex * 16;

		u8 lineYInTile = ly - objectYOnScreen;


		if (!objectFlags.attr.YFlip)
		{
			u8 LSB = mBus->read(tileAddress + (2 * lineYInTile));
			u8 MSB = mBus->read(tileAddress + (2 * lineYInTile) + 1);
			lineData = JOIN_BYTES(MSB, LSB);
		} else
		{
			u8 LSB = mBus->read(tileAddress + 2 * (spriteHeightMode - lineYInTile - 1));
			u8 MSB = mBus->read(tileAddress + 2 * (spriteHeightMode - lineYInTile - 1) + 1);
			lineData = JOIN_BYTES(MSB, LSB);
		}


		for (u8 pixelIndex = 0; pixelIndex < 8; pixelIndex++)
		{
			int16_t pixelXPos = objectXOnScreen + pixelIndex;
			u8 pixelColorID = 0;

			if (pixelXPos >= 0 && pixelXPos < SCREEN_WIDTH)
			{
				if (!objectFlags.attr.XFlip) 
				{
					u8 pixelColorIDMSB = (lineData >> (8 + (7 - pixelIndex))) & 0x01;
					u8 pixelColorIDLSB = (lineData >> (7 - pixelIndex)) & 0x01;
					pixelColorID = (pixelColorIDMSB << 1) + pixelColorIDLSB;
				} else 
				{
					u8 pixelColorIDMSB = (lineData >> (8 + pixelIndex)) & 0x01;
					u8 pixelColorIDLSB = (lineData >> pixelIndex) & 0x01;
					pixelColorID = (pixelColorIDMSB << 1) + pixelColorIDLSB;
				}

			}

			u8 palette = objectFlags.attr.DMGPalette ? readOBP1() : readOBP0();
			// TODO : appeler render avec la bonne palette
			renderPixel(pixelColorID, pixelXPos, ly, palette, true);
		}

		
	}


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

	setWX(50);
	setWY(50);

	mOAM = std::make_shared<OAM>();
}


void PPU::renderPixel(u8 pixelID, int x, int y, u8 palette, bool object)
{
	if (x < 0 || y < 0)
		return;

	if (object && pixelID == 0x00)
		return;

	Pixel pixelColor = mScreenColors[palette >> (2 * pixelID) & 0x03];
	mPixelArray[y][x] = pixelColor;
}


u8 PPU::readIndexInTileMap(u8 xIndex, u8 yIndex, u8 tileMapId) const
{
	return mBus->read(VRAM_BEG_ADDRESS + 0x1800 + (tileMapId * 0x0400) + (yIndex*32) + xIndex);
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

	// address : 8 bits de poids fort de l'adresse : *0x100 pour d�caler � gauche
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
