#include "pch.h"

#include "PPU.h"
//#include "../Utils/Addresses.h"
//#include "../Utils/Log.h"
#include "Utils/ScreenColors.h"

#include "Renderer/BackgroundRenderer.h"
#include "Renderer/WindowRenderer.h"
#include "Renderer/ObjectRenderer.h"

#include "GameLoop/GameLoop.h"
#include "Interrupts/InterruptsManager.h"

#include "Registries/Registries.h"

#include "Interrupts/InterruptsManager.h"

PPU::PPU(std::shared_ptr<Bus> bus, std::shared_ptr<Screen> screen)
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
	LCD_status STAT = getLCDStatus();
	STAT.flags.PPUMode = mode & (0x03);
	setLCDStatus(STAT.byte);

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
	//return mLY;
	return mBus->read(LY);
}

//FF45
inline u8 PPU::readLYC() const
{
	return mBus->read(LY_COMPARE);
}

inline void PPU::incLY()
{
	//mLY = (mLY + 1) % 144;
	u8 ly = readLY();
	u8 lyc = readLYC();
	if (ly == lyc) 
	{
		LCD_status STAT = getLCDStatus();
		STAT.flags.LYC_LY = 0x01;
		setLCDStatus(STAT.byte);
	}
	else 
	{
		LCD_status STAT = getLCDStatus();
		STAT.flags.LYC_LY = 0x00;
		setLCDStatus(STAT.byte);
	}
	mBus->write(LY, (ly + 1) % 144);
}

inline void PPU::incSCY()
{
	u8 scy = mBus->read(SCY);
	mBus->write(SCY, (scy + 1) % 256);
}

void PPU::decSCY()
{
	u8 scy = mBus->read(SCY);
	mBus->write(SCY, (scy - 1));
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

// cycle = dots
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

#ifdef LOG_DEBUG
	m_currCycles += cycle;
	GBE_LOG_INFO("nb cycles : {0}", cycle);
	GBE_LOG_INFO("frame en cours - nb cycles ecoules : {0}", m_currCycles % 456);
#endif

	switch (getPPUMode())
	{
		//Mode 0
	case PPU_HBLANK :
		// fin de scanline
#ifdef DEBUG_LOG
		GBE_LOG_INFO("HBLANK Mode - mPPUModeDots : {0} / {1}", mPPUModeDots, PPU_HBLANK_DOTS);
#endif
		if (mPPUModeDots >= PPU_HBLANK_DOTS) 
		{
			mPPUModeDots -= PPU_HBLANK_DOTS;
			
			incLY();
			//mOAM->getObjects()[2].XPos = (mOAM->getObjects()[2].XPos + 1) % 256;

			if (readLY() >= SCREEN_HEIGHT - 1)
			{
				setPPUMode(PPU_VBLANK);
				//mOnVBlank(InterruptsTypes::VBLANK);
				InterruptsManager::setInterrupt(InterruptsTypes::VBLANK);

			}
			else
			{
				setPPUMode(PPU_OAM_SCAN);
			}

			STATInterruptHandler();
			
			// On passe à la ligne suivante

			/* Si ligne suivante = 144 :
			*   On passe à VBLANK
			*	On a fait toutes les lignes, on render l'image
			*	Interrupt STAT
			*/

			/* Sinon :
			*	On passe en OAM pour recommencer
			*	Interrupt STAT
			*/


		}
		
		break;

		// Mode 1
	case PPU_VBLANK :

#ifdef LOG_DEBUG
		GBE_LOG_INFO("VBLANK Mode - mPPUModeDots : {0} / {1}", mPPUModeDots, PPU_VBLANK_DOTS);
#endif
		if (mPPUModeDots >= PPU_VBLANK_DOTS) 
		{

			mPPUModeDots -= PPU_VBLANK_DOTS;
			// 10 scanlines

			draw();
			// On incrémente la ligne
			incLY();

			// Si ligne suivante = 154 : on revient en haut et passe en OAM
			// Interrupt ?
			setPPUMode(PPU_OAM_SCAN);
			STATInterruptHandler();

		}


		break;

		//Mode 2
	case PPU_OAM_SCAN :
		// On décrémente les cycles et on passe en DRAWING

#ifdef LOG__DEBUG
		GBE_LOG_INFO("OAM SCAN Mode - mPPUModeDots : {0} / {1}", mPPUModeDots, PPU_OAM_SCAN_DOTS);
#endif
		if (mPPUModeDots >= PPU_OAM_SCAN_DOTS)
		{
			//TODO gerer les dots dans le CPU
			//mPPUModeDots -= cycle;
			mPPUModeDots -= PPU_OAM_SCAN_DOTS;
			setPPUMode(PPU_DRAWING);
		}
		break;

		//Mode 3
	case PPU_DRAWING :




		if (!mIsScanlineDrawn)
		{
			mDotsElapsed = renderPixelsScanline();
			mIsScanlineDrawn = true;
		}

#ifdef LOG_DEBUG
		GBE_LOG_INFO("DRAWING Mode - mPPUModeDots : {0} / {1}, dots elapsed : {2}", mPPUModeDots, PPU_DRAWING_DOTS, mDotsElapsed);
#endif
		if ((mPPUModeDots ) >= PPU_DRAWING_DOTS)
		{
			mIsScanlineDrawn = false;
			mPPUModeDots -= (PPU_DRAWING_DOTS );
			
			setPPUMode(PPU_HBLANK);
			STATInterruptHandler();
		}
		// On passe en HBLANK
		// Interrupt ?

		break;
	}

	//mScreen->render(mPixelArray);
	
}


 u8 PPU::renderPixelsScanline()
{
	u64 scanlineBegin = SDL_GetPerformanceCounter();
	renderScanline<BackgroundRenderer>();
	renderScanline<WindowRenderer>();
	renderScanline<ObjectRenderer>();

	double scanlineElapsedInSec = (double)(SDL_GetPerformanceCounter() - scanlineBegin) / SDL_GetPerformanceFrequency();

	return (scanlineElapsedInSec * CLOCK_FREQUENCY);
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

	//setWX(50);
	//setWY(50);

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

	//GameLoop::addVirtualWaitingDots(640);
}

template<typename T>
inline void PPU::renderScanline()
{
	T renderer(this);
	renderer.renderScanline(); 

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
	//u8* pPixels = new u8[sizeof(mPixelArray)];
	//memcpy(pPixels, static_cast<void const*>(&mPixelArray), 160 * 144 * 4);
	mOnRender(mPixelArray);
	//mScreen->startRendering(mPixelArray);
}

void PPU::setTile(u8 tileIndex, const std::vector<u8>& tileData)
{
	if (tileIndex >= 16)
	{
		int a{ 0 };
	}
	for (int i = 0; i < TILE_BYTE_SIZE; i++)
	{
		mBus->write(VRAM_BEG_ADDRESS + (tileIndex * TILE_BYTE_SIZE) + i, tileData[i]);
	}
}

void PPU::setTileMap(u8 tileMapIndex, const std::vector<u8>& tileMapData)
{
	u16 tileMapAddressOffset = tileMapIndex == 0 ? TILE_MAP_1_BEG_ADDRESS : TILE_MAP_2_BEG_ADDRESS;
	for (int i = 0; i < TILEMAP_BYTE_SIZE; i++)
	{
		mBus->write(tileMapAddressOffset + i, tileMapData[i]);
	}
}


void PPU::reset()
{
	mOAM->reset();

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
			mPixelArray[i][j] = { 0 };
	}

	mObjectsOAMIndex.clear();

	initializePPU();

}

void PPU::waitForNextFrame()
{
	executeFullFrameRender();
}


void PPU::STATInterruptHandler()
{
	LCD_status STAT = getLCDStatus();
	u8 LYCCondition = STAT.flags.LYCintSelect == 0x01 ? STAT.flags.LYC_LY : 0x00;
	u8 mode0Condition = 0x00;
	if (STAT.flags.mode0intSelect == 0x01)
	{
		mode0Condition = STAT.flags.PPUMode == 0x00 ? 0x01 : 0x00;
	}
	u8 mode1Condition = 0x00;
	if (STAT.flags.mode1intSelect == 0x01)
	{
		mode1Condition = STAT.flags.PPUMode == 0x01 ? 0x01 : 0x00;
	}
	//test
	u8 mode2Condition = 0x00;
	if (STAT.flags.mode2intSelect == 0x01)
	{
		mode2Condition = STAT.flags.PPUMode == 0x02 ? 0x01 : 0x00;
	}

	u8 newStatLine = LYCCondition | mode0Condition | mode1Condition | mode2Condition;

	if (mStatLine == 0x00 && newStatLine == 0x01)
	{
		InterruptsManager::setInterrupt(InterruptsTypes::LCD_STAT);
	}

	mStatLine = newStatLine;




}