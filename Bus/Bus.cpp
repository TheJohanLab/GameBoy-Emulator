#include "Bus.h"
#include "Utils/Addresses.h"
#include <memory>

Bus::Bus() 
	:mCartridge(std::make_shared<Cartridge>())
{
	mMemory = Memory();
	//mCartridge = Cartridge();
}

u8 Bus::read(const u16 &address) const
{
	if (address >= 0x100 && address < 8000)
		return mCartridge->read(address);
	else
		return mMemory.read(address);

}

void Bus::write(const u16 &address, const u8 &data)
{
	mMemory.write(address, data);
}

u8* Bus::getDataPtr(const u16& address)
{
	return mMemory.getDataPtr(address);
}


interrupt_flag Bus::getInterruptEnable() const
{
	interrupt_flag IE;
	IE.byte = mMemory.read(INTERRUPT_ENABLE);
	return IE;
}

interrupt_flag Bus::getInterruptFlag() const
{
	interrupt_flag IF;
	IF.byte = mMemory.read(INTERRUPT_FLAG);
	return IF;
}

void Bus::setInterruptEnable(const u8 flags)
{
	mMemory.write(INTERRUPT_ENABLE,flags);
}

void Bus::setInterruptFlag(const u8 flags)
{
	mMemory.write(INTERRUPT_FLAG, flags);
}

