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
BG_palette_data PPU::getBGP() const
{
	BG_palette_data flags;
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

//FF49
u8 PPU::readOBP1() const
{
	return mBus->read(OBP1);
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

	case PPU_HBLANK :
		// fin de scanline
		
		if (mPPUModeDots >= PPU_HBLANK_DOTS) 
		{
			mPPUModeDots -= PPU_HBLANK_DOTS;

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

	case PPU_VBLANK :

		if (mPPUModeDots >= PPU_VBLANK_DOTS) 
		{

			mPPUModeDots -= PPU_VBLANK_DOTS;
			// 10 scanlines

			// On incrémente la ligne

			// Si ligne suivante = 154 : on revient en haut et passe en OAM
			// Interrupt ?
			setPPUMode(PPU_OAM_SCAN);
		}


		break;

	case PPU_OAM_SCAN :
		// On décrémente les cycles et on passe en DRAWING

		if (mPPUModeDots >= PPU_OAM_SCAN_DOTS)
		{
			mPPUModeDots -= cycle;
			setPPUMode(PPU_DRAWING);
		}
		break;

	case PPU_DRAWING :
		// Render Scanline
		renderScanline();

		incLY();
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

	// Si Window activée : render Window ScanLine

	renderWindowScanline();
	
	// On copie les pixels de BG+W dans le tableau à afficher

	// Si OBJ activé : render OBJ Scanline
}

void PPU::renderBGScanline()
{
	/* LCDC.0=0
	*   BG désactivé : tout s'affiche en blanc
	*/

	// On charge la palette
	auto backgroundPalette = getBGP();

	//A changer en fonction de LCD control
	u16 tileAddressingOffset = 0;

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
		u16 tileIndex = readIndexInTileMap(tileX, tileY);

		// TODO : gérer le cas index négatif
		// 16 car une tile fait 16 bytes de long dans la VRAM
		u16 tileIndexInVRAM = (tileIndex + tileAddressingOffset) * 16;

		// * 2 car une ligne d'une tile est composée de 2 bytes
		u16 lineIndexInVRAM = tileIndexInVRAM + (pixelYInTile * 2);

		// On récupère les 2 lignes de bits
		u8 lineLSB = mBus->read(VRAM_BEG_ADDRESS + lineIndexInVRAM);
		u8 lineMSB = mBus->read(VRAM_BEG_ADDRESS + lineIndexInVRAM + 1);

		u8 pixelXInTile = (readSCX() + x) % 8;
		u8 pixelColorIdLSB = (lineLSB >> (7 - pixelXInTile)) & 0x01;
		u8 pixelColorIdMSB = (lineMSB >> (7 - pixelXInTile)) & 0x01;
		u8 pixelColorID = pixelColorIdLSB + (pixelColorIdMSB << 1);

		renderPixel(pixelColorID, x, readLY());
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

	//A changer en fonction de LCD control
	u16 tileAddressingOffset = 0x0400;

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

		// TODO : gérer le cas index négatif
		// 16 car une tile fait 16 bytes de long dans la VRAM	
		u16 tileIndex = readIndexInTileMap(tileXInWindow, tileYInWindow);

		// * 2 car une ligne d'une tile est composée de 2 bytes
		u16 tileIndexInVRAM = (tileIndex + tileAddressingOffset) * 16;

		// * 2 car une ligne d'une tile est composée de 2 bytes
		u16 lineIndexInVRAM = tileIndexInVRAM + (pixelYInTile * 2);

		// On récupère les 2 lignes de bits
		u8 lineLSB = mBus->read(VRAM_BEG_ADDRESS + lineIndexInVRAM);
		u8 lineMSB = mBus->read(VRAM_BEG_ADDRESS + lineIndexInVRAM + 1);

		u8 pixelXInTile = (x - xPosOnScreen) % 8;
		u8 pixelColorIdLSB = (lineLSB >> (7 - pixelXInTile)) & 0x01;
		u8 pixelColorIdMSB = (lineMSB >> (7 - pixelXInTile)) & 0x01;
		u8 pixelColorID = pixelColorIdLSB + (pixelColorIdMSB << 1);

		renderPixel(pixelColorID, x, readLY());

	}

}

void PPU::renderOBJScanline()
{

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


void PPU::renderPixel(u8 pixelID, int i, int j)
{
	auto bgp = getBGP();
	// 11 10 01 00

	Pixel pixelColor = mScreenColors[bgp.byte >> (2 * pixelID) & 0x03];
	mPixelArray[j][i] = pixelColor;
}


u8 PPU::readIndexInTileMap(u8 xIndex, u8 yIndex) const
{
	u16 BGModeAddressingOffset = 0x1800; // 0 ou 0x1000 selon flag (nb de la tilemap)
	return mBus->read(VRAM_BEG_ADDRESS + BGModeAddressingOffset + (yIndex*32) + xIndex);
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
		sourceAddress | (objectIndex * 4),
		sourceAddress | (objectIndex * 4 + 1), 
		sourceAddress | (objectIndex * 4 + 2), 
		sourceAddress | (objectIndex * 4 + 3));
	}

	//TODO Attendre 160 mcycles ou 640 dots
}