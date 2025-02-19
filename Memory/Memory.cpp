#include "pch.h"

#include "Memory.h"


Memory::Memory()
{
}        


u8 Memory::read(u16 const address) const
{
	//if (address >= 0xC000 && address <= 0xDFFF)
	//	return mWRAM[address - 0xC000];
	//else if (address >= 0x8000 && address <= 0x9FFF)
	//	return mVRAM[address - 0x8000];
	//else if (address >= 0xA000 && address <= 0xBFFF)
	//	return mERAM[address - 0xA000];
	//else if (address >= 0xFE00 && address <= 0xFE9F) // OAM
	//	return mOAM[address - 0xFE00];
	//else if (address >= LCD_CONTROL && address <= WINDOW_X)
	//	return readLCD(address);
	//else if (address >= 0xFF80 && address <= 0xFFFE)
	//	return mHRAM[address - 0xFF80];
	//else if (address == INTERRUPT_FLAG) // IF Register
	//	return mInterruptRegistries[0];
	//else if (address == INTERRUPT_ENABLE) // IE Register
	//	return mInterruptRegistries[1];

	return mMemory.rawMemory[address];
}	


void Memory::write(u16 const address, u8 const data)
{

	mMemory.rawMemory[address] = data;
	if (address == DMA)
		mDMACallback(data);

	//if (address >= 0xC000 && address <= 0xDFFF)
	//	mWRAM[address - 0xC000] = data;
	//else if (address >= 0x8000 && address <= 0x9FFF)
	//	mVRAM[address - 0x8000] = data;
	//else if (address >= 0xA000 && address <= 0xBFFF)
	//	mERAM[address - 0xA000] = data;
	//else if (address >= 0xFE00 && address <= 0xFE9F) // OAM
	//	mOAM[address - 0xFE00] = data;
	//else if (address != DMA && address >= LCD_CONTROL && address <= WINDOW_X)
	//	writeLCD(address, data);
	//else if (address >= 0xFF80 && address <= 0xFFFE)
	//	mHRAM[address - 0xFF80] = data;
	//else if (address == INTERRUPT_FLAG) // IF Register
	//	mInterruptRegistries[0] = data;
	//else if (address == INTERRUPT_ENABLE) // IE Register
	//	mInterruptRegistries[1] = data;
	/*else if (address == DMA)
	{
 		mDMACallback(data);
	}*/
}

u8* Memory::getDataPtr(u16 const address)
{
	//if (address >= 0xC000 && address <= 0xDFFF)
	//	return &mWRAM[address - 0xC000];
	//if (address >= 0x8000 && address <= 0x9FFF)
	//	return &mVRAM[address - 0x8000];
	//if (address >= 0xA000 && address <= 0xBFFF)
	//	return &mERAM[address - 0xA000];
	//else if (address >= 0xFE00 && address <= 0xFE9F) // OAM
	//	return &mOAM[address - 0xFE00];
	//else if (address >= LCD_CONTROL && address <= WINDOW_X)
	//	return getLCDPtr(address);
	//if (address >= 0xFF80 && address <= 0xFFFE)
	//	return &mHRAM[address - 0xFF80];
	//if (address == INTERRUPT_FLAG) // IF Register
	//	return &mInterruptRegistries[0];
	//if (address == INTERRUPT_ENABLE) // IE Register
	//	return &mInterruptRegistries[1];
	//else
	//	return nullptr;

	return &mMemory.rawMemory[address];

}


void Memory::reset()
{
	auto LCD_CTRL = mMemory.LCD_CTRL;
	
	mMemory.rawMemory.fill(0x00);

	//TODO check why the is necesarry for the reset
	mMemory.LCD_CTRL = LCD_CTRL;

	//for (auto& WRAM : mWRAM)
	//	WRAM = { 0x00 };
	//for (auto& VRAM : mVRAM)
	//	VRAM = { 0x00 };
	//for (auto& ERAM : mERAM)
	//	ERAM = { 0x00 };
	//for (auto& HRAM : mHRAM)
	//	HRAM = { 0x00 };
	//for (auto& OAM : mOAM)
	//	OAM = { 0x00 };
	//TODO Check why these two reset don't work
	//for (auto& IR : mInterruptRegistries)
	//	IR = { 0x00 };
	//for (auto& LCDR : mLCDRegistries)
	//	LCDR = { 0x00 };

}

const MemoryUnion& Memory::getMemory() const
{
	return mMemory;
}



std::vector<std::pair<std::string, MemoryRegion>> Memory::getMemoryRegions() const
{
	return mMemoryRegions;
}

const u8* Memory::getMemoryRegionData(const MemoryRegion& region) const
{
	return (mMemory.rawMemory.data() + region.offset);
}


