#include "pch.h"

#include "Bus.h"
//#include "Utils/Addresses.h"
//#include <memory>

Bus::Bus(std::shared_ptr<Memory> memory, std::shared_ptr<Cartridge> cartridge)
	//: mCartridge(std::make_shared<Cartridge>()),
	  //mMemory(std::make_shared<Memory>())
	: mMemory(memory), mCartridge(cartridge)
{
	}

u8 Bus::read(const u16 address) const
{
	if (address >= 0x00 && address < 0x8000)
		return mCartridge->read(address);
	else
		return mMemory->read(address);

}

u8& Bus::read(const u16 address)
{
	if (address >= 0x00 && address < 0x8000)
		return mCartridge->read(address);
	else
		return mMemory->read(address);
}

void Bus::write(const u16 address, const u8 data)
{
	mMemory->write(address, data);
}

u8* Bus::getDataPtr(const u16 address)
{
	return mMemory->getDataPtr(address);
}


interrupt_flag Bus::getInterruptEnable() const
{
	interrupt_flag IE;
	IE.byte = mMemory->read(INTERRUPT_ENABLE);
	return IE;
}

interrupt_flag Bus::getInterruptFlag() const
{
	interrupt_flag IF;
	IF.byte = mMemory->read(INTERRUPT_FLAG);
	return IF;
}

void Bus::setInterruptEnable(const u8 flags)
{
	mMemory->write(INTERRUPT_ENABLE, flags);
}

void Bus::setInterruptFlag(const u8 flags)
{

	mMemory->write(INTERRUPT_FLAG, flags);
}

void Bus::reset()
{
	mMemory->resetMemory();
}

