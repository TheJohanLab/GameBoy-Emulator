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

	public:
		Memory();
		virtual ~Memory() = default;

		u8 read(u16 const& address) const;
		void write(u16 const& address, u8 const& data);

		u8* getDataPtr(u16 const& address);
};

