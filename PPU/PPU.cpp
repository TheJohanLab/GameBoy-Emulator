#include "PPU.h"
#include "../Utils/Addresses.h"

PPU::PPU(Bus* bus, Screen* screen)
	:mBus(bus), mScreen(screen)
{

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
	for (int i = 0; i < 160; i++)
	{
		for (int j = 0; j < 144; j++)
		{
			u8 red = 0;
			u8 green = 0;
			if (i % 8 >= 0 && i % 8 < 4)
			{
				red = 255;
				green = 0;
			}
			else {
				red = 0;
				green = 255;
			}
			mPixelArray[j][i] = { 255, red, green, 0 };
			// ARGB
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
