#include "pch.h"

#include "Memory.h"


Memory::Memory()
{
	initWriterHandler();
}        


u8 Memory::read(u16 const address) const
{
	return mMemory.rawMemory[address];
}

u8& Memory::read(u16 const address)
{
	return mMemory.rawMemory[address];
}



void Memory::write(u16 const address, u8 const data)
{
	mWriterHandler[address](address, data);
}

u8* Memory::getDataPtr(u16 const address)
{
	return &mMemory.rawMemory[address];
}


void Memory::resetMemory()
{
	auto LCD_CTRL = mMemory.LCD_CTRL;
	
	mMemory.rawMemory.fill(0x00);

	//TODO check why it is mandatory for the reset
	mMemory.LCD_CTRL = LCD_CTRL;

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


void Memory::initWriterHandler()
{
	for (size_t i = 0; i < MEMORY_SIZE; i++)
	{
		mWriterHandler[i] = BIND_FUNC_2_ARGS(this, Memory::defaultWrite);
	}
	mWriterHandler[DMA] = BIND_FUNC_2_ARGS(this, Memory::DMAWrite);

	// STAT: bits 0-2 (PPU mode, LY=LYC) are read-only for the CPU, bit 7 reads 1. The PPU writes them
	// directly. Without this, any 'ldh [rSTAT], a' moved the PPU state machine to an arbitrary mode.
	mWriterHandler[LCD_STATUS] = [this](const u16 address, const u8 data) {
		mMemory.rawMemory[address] = 0x80 | (data & 0x78) | (mMemory.rawMemory[address] & 0x07);
	};
	// LY is read-only for the CPU.
	mWriterHandler[LY] = [](const u16, const u8) {};
}

void Memory::defaultWrite(const u16 address, const u8 data)
{
	mMemory.rawMemory[address] = data;
}

void Memory::DMAWrite(const u16 address, const u8 data)
{
	mMemory.rawMemory[address] = data;
	mDMACallback(data);
}


