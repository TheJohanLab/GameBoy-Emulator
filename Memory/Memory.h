#pragma once

#include <array>
#include "../Utils/Utils.h"

class Memory
{
	private:
		std::array<u8, 8 * 1024> mWRAM;
		std::array<u8, 8 * 1024> mVRAM;
		std::array<u8, 8 * 1024> mERAM;
		std::array<u8, 127> mHRAM;

	public:
		Memory();
		virtual ~Memory() = default;

		u8 read(u16 const& address) const;
		void write(u16 const& address, u8 const& data);
};

