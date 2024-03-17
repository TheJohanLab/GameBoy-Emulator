#pragma once

#include <array>
#include "../Utils/Utils.h"

class Memory
{
	private:
		std::array<u8, 8 * kiB> mWRAM = { 0x00 };
		std::array<u8, 8 * kiB> mVRAM = { 0x00 };
		std::array<u8, 8 * kiB> mERAM = { 0x00 };
		std::array<u8, HRAMSize> mHRAM = { 0x00 };
		interrupt_flag IR;
		interrupt_enable IE;

	public:
		Memory();
		virtual ~Memory() = default;

		u8 read(u16 const& address) const;
		void write(u16 const& address, u8 const& data);

		u8* getDataPtr(u16 const& address);

		interrupt_flag getInterruptFlag() const;
		void setInterruptFlag(u8 byte);
		void setInterruptFlag(interrupt_flag byte);

		interrupt_flag getInterruptEnable() const;
		void setInterruptEnable(u8 byte);
		void setInterruptEnable(interrupt_flag byte);


};

