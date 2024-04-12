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

void PPU::render()
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
	switch (getPPUMode())
	{

	case 0x00 :
		break;

	case 0x01 :
		break;

	case 0x02 :
		break;

	case 0x03 :
		break;
	}
}
