#include "Memory.h"
#include <iostream>


Memory::Memory(){}

u8 Memory::read(u16 const& address) const
{
	if (address >= 0xC000 && address <= 0xDFFF)
		return mWRAM[address - 0xC000];
	if (address >= 0x8000 && address <= 0x9FFF)
		return mVRAM[address - 0x8000];
	if (address >= 0xA000 && address <= 0xBFFF)
		return mERAM[address - 0xA000];
	if (address >= 0xFF80 && address <= 0xFFFE)
		return mHRAM[address - 0xFF80];

	return -1;
}	


void Memory::write(u16 const& address, u8 const& data)
{
	if (address >= 0xC000 && address <= 0xDFFF)
		 mWRAM[address - 0xC000] = data;
	if (address >= 0x8000 && address <= 0x9FFF)
		mVRAM[address - 0x8000] = data;
	if (address >= 0xA000 && address <= 0xBFFF)
		mERAM[address - 0xA000] = data;
	if (address >= 0xFF80 && address <= 0xFFFE)
		mHRAM[address - 0xFF80] = data;
}