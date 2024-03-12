#include "Bus.h"

Bus::Bus() 
{
	mMemory = Memory();
}

u8 Bus::read(const u16 &address) const
{
	u8 data = mMemory.read(address);
	return data;
}


void Bus::write(const u16 &address, const u8 &data)
{
	mMemory.write(address, data);
}

u8* Bus::getDataPtr(const u16& address)
{
	return mMemory.getDataPtr(address);
}

interrupt_flags* Bus::getInterruptFlags()
{
	return mMemory.getInterruptFlags();
}

void Bus::setInterruptFlags(const u8 flags)
{
	mMemory.setInterruptFlag(flags);
}

void Bus::setInterruptFlags(const interrupt_flags flags)
{
	mMemory.setInterruptFlag(flags);
}
