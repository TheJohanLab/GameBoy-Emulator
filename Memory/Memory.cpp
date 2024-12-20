#include "Memory.h"
#include <iostream>

#include "../Utils/Addresses.h"


/*0b00101111, 0b11111000,
0b00110000, 0b00001100,
0b00110000, 0b00001100,
0b00110000, 0b00001100,
0b00110111, 0b11111100,
0b00010101, 0b11011100,
0b00110111, 0b01111000,
0b00101111, 0b11100000*/


Memory::Memory()
{
	//const u16 offset = 0x1000 - 16;

	//mVRAM[offset + 0] = 0b00111100;		mVRAM[offset + 1] = 0b01111110;
	//mVRAM[offset + 2] = 0b01000010;		mVRAM[offset + 3] = 0b01000010;
	//mVRAM[offset + 4] = 0b01000010;		mVRAM[offset + 5] = 0b01000010;
	//mVRAM[offset + 6] = 0b01000010;		mVRAM[offset + 7] = 0b01000010;
	//mVRAM[offset + 8] = 0b01111110;		mVRAM[offset + 9] = 0b01011110;
	//mVRAM[offset + 10] = 0b01111110;	mVRAM[offset + 11] = 0b00001010;
	//mVRAM[offset + 12] = 0b01111100;	mVRAM[offset + 13] = 0b01010110;
	//mVRAM[offset + 14] = 0b00111000;	mVRAM[offset + 15] = 0b01111100;


	/*mLCDRegistries[2] = 22;
	mLCDRegistries[3] = 17;*/

}

u8 Memory::read(u16 const& address) const
{
	if (address >= 0xC000 && address <= 0xDFFF)
		return mWRAM[address - 0xC000];
	else if (address >= 0x8000 && address <= 0x9FFF)
		return mVRAM[address - 0x8000];
	else if (address >= 0xA000 && address <= 0xBFFF)
		return mERAM[address - 0xA000];
	else if (address >= LCD_CONTROL && address <= WINDOW_X)
		return readLCD(address);
	else if (address >= 0xFF80 && address <= 0xFFFE)
		return mHRAM[address - 0xFF80];
	else if (address == INTERRUPT_FLAG) // IF Register
		return mInterruptRegistries[0];
	else if (address == INTERRUPT_ENABLE) // IE Register
		return mInterruptRegistries[1];
	return -1;
}	


void Memory::write(u16 const& address, u8 const& data)
{
	if (address >= 0xC000 && address <= 0xDFFF)
		mWRAM[address - 0xC000] = data;
	else if (address >= 0x8000 && address <= 0x9FFF)
		mVRAM[address - 0x8000] = data;
	else if (address >= 0xA000 && address <= 0xBFFF)
		mERAM[address - 0xA000] = data;
	else if (address >= 0xFE00 && address <= 0xFE9F) // OAM
		mOAM[address - 0xFE00] = data;
	else if (address != DMA && address >= LCD_CONTROL && address <= WINDOW_X)
		writeLCD(address, data);
	else if (address >= 0xFF80 && address <= 0xFFFE)
		mHRAM[address - 0xFF80] = data;
	else if (address == INTERRUPT_FLAG) // IF Register
		mInterruptRegistries[0] = data;
	else if (address == INTERRUPT_ENABLE) // IE Register
		mInterruptRegistries[1] = data;
	else if (address == DMA)
	{
		mDmaRegistry = data;
 		mDMACallback(data);
	}

}

u8* Memory::getDataPtr(u16 const& address)
{
	if (address >= 0xC000 && address <= 0xDFFF)
		return &mWRAM[address - 0xC000];
	if (address >= 0x8000 && address <= 0x9FFF)
		return &mVRAM[address - 0x8000];
	if (address >= 0xA000 && address <= 0xBFFF)
		return &mERAM[address - 0xA000];
	else if (address >= LCD_CONTROL && address <= WINDOW_X)
		return getLCDPtr(address);
	if (address >= 0xFF80 && address <= 0xFFFE)
		return &mHRAM[address - 0xFF80];
	if (address == INTERRUPT_FLAG) // IF Register
		return &mInterruptRegistries[0];
	if (address == INTERRUPT_ENABLE) // IE Register
		return &mInterruptRegistries[1];
	else
		return nullptr;

}

u8 Memory::readLCD(const u16& address) const
{
	switch (address)
	{
	case LCD_CONTROL:
		return mLCDRegistries[0];
		break;
	case LCD_STATUS:
		return mLCDRegistries[1];
		break;
	case SCY:
		return mLCDRegistries[2];
		break;
	case SCX:
		return mLCDRegistries[3];
		break;
	case LY:
		return mLCDRegistries[4];
		break;
	case LY_COMPARE:
		return mLCDRegistries[5];
		break;
	case BG_PALETTE:
		return mLCDRegistries[7];
		break;
	case OBP0:
		return mLCDRegistries[8];
		break;
	case OBP1:
		return mLCDRegistries[9];
		break;
	case WINDOW_Y:
		return mLCDRegistries[0xA];
		break;
	case WINDOW_X:
		return mLCDRegistries[0xB];
		break;
	default:
		return -1;
		break;
	}
}


void Memory::writeLCD(const u16& address, const u8& data)
{
	switch(address)
	{
	case LCD_CONTROL:
		mLCDRegistries[0] = data;
		break;
	case LCD_STATUS:
		mLCDRegistries[1] = data;
		break;
	case SCY:
		mLCDRegistries[2] = data;
		break;
	case SCX:
		mLCDRegistries[3] = data;
		break;
	case LY:
		mLCDRegistries[4] = data;
		break;
	case LY_COMPARE:
		mLCDRegistries[5] = data;
		break;
	case BG_PALETTE:
		mLCDRegistries[7] = data;
		break;
	case OBP0:
		mLCDRegistries[8] = data;
		break;
	case OBP1:
		mLCDRegistries[9] = data;
		break;
	case WINDOW_Y:
		mLCDRegistries[0xA] = data;
		break;
	case WINDOW_X:
		mLCDRegistries[0xB] = data;
		break;
	default:
		break;

	}
}

u8* Memory::getLCDPtr(const u16& address)
{
	switch (address)
	{
	case LCD_CONTROL:
		return &mLCDRegistries[0];
		break;
	case LCD_STATUS:
		return &mLCDRegistries[1];
		break;
	case SCY:
		return &mLCDRegistries[2];
		break;
	case SCX:
		return &mLCDRegistries[3];
		break;
	case LY:
		return &mLCDRegistries[4];
		break;
	case LY_COMPARE:
		return &mLCDRegistries[5];
		break;
	case BG_PALETTE:
		return &mLCDRegistries[7];
		break;
	case OBP0:
		return &mLCDRegistries[8];
		break;
	case OBP1:
		return &mLCDRegistries[9];
		break;
	case WINDOW_Y:
		return &mLCDRegistries[0xA];
		break;
	case WINDOW_X:
		return &mLCDRegistries[0xB];
		break;
	default:
		return nullptr;
		break;
	}
}