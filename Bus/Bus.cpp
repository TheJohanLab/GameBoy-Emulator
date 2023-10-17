#include "Bus.h"

Bus::Bus() 
{
	mMemory = Memory();
}

u8 Bus::read(const u16 &address) const
{
	return mMemory.read(address);
}


void Bus::write(const u16 &address, const u8 &data)
{
	mMemory.write(address, data);
}