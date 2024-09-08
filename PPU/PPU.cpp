#include "PPU.h"
#include "../Utils/Addresses.h"
#include "../Utils/Log.h"
#include "Utils/ScreenColors.h"

#include "Renderer/BackgroundRenderer.h"
#include "Renderer/WindowRenderer.h"
#include "Renderer/ObjectRenderer.h"

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
inline u8 PPU::readLY() const
{
	return mLY;
	//return mBus->read(LY);
}

//FF45
inline u8 PPU::readLYC() const
{
	return mBus->read(LY_COMPARE);
}

inline void PPU::incLY()
{
	mLY = (mLY + 1) % 144;
	//u8 ly = mBus->read(LY);
	mBus->write(LY, mLY);
}

inline void PPU::incSCY()
{
	u8 scy = mBus->read(SCY);
	mBus->write(SCY, (scy + 1) % 256);
}

inline void PPU::incSCX()
{
	u8 scx = mBus->read(SCX);
	mBus->write(SCX, (scx + 1) % 256);
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
			incSCY();
			incSCX();
			//mOAM->getObjects()[2].XPos = (mOAM->getObjects()[2].XPos + 1) % 256;
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

		renderPixelsScanline();
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

void PPU::renderPixelsScanline()
{
	renderScanline<BackgroundRenderer>();
	renderScanline<WindowRenderer>();
	renderScanline<ObjectRenderer>();
}

// ------------------------------------//
//			PRIVATE METHODS
// ------------------------------------//
void PPU::initializePPU()
{
	mScreenColors[0] = gbe::COLOR_WHITE;		// WHITE
	mScreenColors[1] = gbe::COLOR_LIGHT_GREEN;	// LIGHT GREEN
	mScreenColors[2] = gbe::COLOR_DARK_GREEN;	// DARK GREEN
	mScreenColors[3] = gbe::COLOR_BLACK;		// BLACK

	setBGP(0b00011011);
	//setBGP(0b10011010);
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


	Pixel pixelColor = mScreenColors[palette >> (2 * pixelID) & 0x03];
	mPixelArray[y][x] = pixelColor;
}


u8 PPU::readIndexInTileMap(u8 xIndex, u8 yIndex, u8 tileMapId) const
{
	//400 est la taille d'une tilemap
	return mBus->read(VRAM_BEG_ADDRESS + TILEMAPS_OFFSET + (tileMapId * 0x0400) + (yIndex*32) + xIndex);
}


u16 PPU::getTileIndexInVRAM(std::variant<u8, int8_t> tileIndex, u8 tileDataAddressingType) const
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

u8 PPU::readFromMemory(u16 address) const
{
	return mBus->read(address);
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

template<typename T>
inline void PPU::renderScanline()
{
	T renderer(this);
	renderer.renderScanline(); // Faire retourner le temps d'attente CPU

	//TODO gerer les attentes cpu ici
}

void PPU::setCloseEventCallback(std::function<void()> callback)
{
	mScreen->setOnCloseEvent(callback);
}

void PPU::handleWindowEvents()
{
	mScreen->handleEvents();
}

void PPU::executeFullFrameRender()
{
	mLY = 0;
	for (int line = 0; line < SCREEN_HEIGHT; line++)
	{
		renderPixelsScanline();
		incLY();
	}
		draw();
}

void PPU::draw()
{
	mScreen->render(mPixelArray);
}
