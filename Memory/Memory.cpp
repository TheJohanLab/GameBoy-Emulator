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
	if (address == 0xFF0F)
		return IR.byte;
	if (address == 0xFFFF)
		return IE.byte;
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
	if (address == 0xFF0F)
		IR.byte = data;
	if (address == 0xFFFF)
		IE.byte = data;
}

u8* Memory::getDataPtr(u16 const& address)
{
	if (address >= 0xC000 && address <= 0xDFFF)
		return &mWRAM[address - 0xC000];
	if (address >= 0x8000 && address <= 0x9FFF)
		return &mVRAM[address - 0x8000];
	if (address >= 0xA000 && address <= 0xBFFF)
		return &mERAM[address - 0xA000];
	if (address >= 0xFF80 && address <= 0xFFFE)
		return &mHRAM[address - 0xFF80];
	else
		return nullptr;

}

interrupt_flag Memory::getInterruptFlag() const
{
	return IR;
}

void Memory::setInterruptFlag(const u8 byte)
{
	IR.byte = byte;
}

void Memory::setInterruptFlag(const interrupt_flag interruptFlags)
{
	IR = interruptFlags;
}

interrupt_flag Memory::getInterruptEnable() const
{
	return IR;
}

void Memory::setInterruptEnable(const u8 byte)
{
	IR.byte = byte;
}

void Memory::setInterruptEnable(const interrupt_flag interruptFlags)
{
	IR = interruptFlags;
}
