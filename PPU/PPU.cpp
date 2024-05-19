#include "PPU.h"
#include "../Utils/Addresses.h"

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
			renderPixel(tileTest[j] >> (2*(4 - (i+1))) & 0x03, 50+i+(4*(j%2)), 50+(j/2));
		}
	}


	mScreen->render(mPixelArray);

	/* En fonction du cycle
	*	1 frame = 70224 dots
	*	1 scanline = 456 dots
	*		2 : OAM SCAN : 80 dots	
	*		3 : DRAWING  : 172-289 dots
	*		0 : HBLANK	 : 87-204 dots (376 - DRAWING)
	*		1 : VBLANK	 : 10 scanlines = 4560 dots
	*/

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

		if (mPPUModeDots >= PPU_DRAWING_DOTS) 
		{
			mPPUModeDots -= PPU_DRAWING_DOTS;

			setPPUMode(PPU_HBLANK);
		}

		// On passe en HBLANK
		// Interrupt ?

		break;
	}
}

void PPU::renderScanline()
{
	// Render Background Scanline
	// Si Window activée : render Window ScanLine

	// On copie les pixels de BG+W dans le tableau à afficher

	// Si OBJ activé : render OBJ Scanline
}

void PPU::renderBGScanline()
{
	/* LCDC.0=0
	*   BG désactivé : tout s'affiche en blanc
	*/

	// On charge la palette
	// Adressage TileData
}

void PPU::renderWindowScanline()
{

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
}


void PPU::renderPixel(u8 pixelID, int i, int j)
{
	auto bgp = getBGP();
	// 11 10 01 00

	Pixel pixelColor = mScreenColors[bgp.byte >> (2 * pixelID) & 0x03];
	mPixelArray[j][i] = pixelColor;
}