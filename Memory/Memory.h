#pragma once

#include <array>
#include "../Utils/Utils.h"

class Memory
{
	private:
		std::array<u8, 8 * kiB> mWRAM;
		std::array<u8, 8 * kiB> mVRAM;
		std::array<u8, 8 * kiB> mERAM;
		std::array<u8, HRAMSize> mHRAM;

	public:
		Memory();
		virtual ~Memory() = default;

		u8 read(u16 const& address) const;
		void write(u16 const& address, u8 const& data);
};

