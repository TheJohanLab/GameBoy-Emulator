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


