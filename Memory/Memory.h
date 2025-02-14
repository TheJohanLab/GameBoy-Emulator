#pragma once

#include <array>
#include "../Utils/Utils.h"

#include <functional>

class Memory
{
	using DMACallback = std::function<void(const u8)>;

	private:
		std::array<u8, 8 * kiB> mWRAM = { 0x00 };
		std::array<u8, 8 * kiB> mVRAM = { 0x00 };
		std::array<u8, 8 * kiB> mERAM	= { 0x00 };
		std::array<u8, HRAM_SIZE> mHRAM = { 0x00 };
		std::array<u8, OAM_SIZE> mOAM	= { 0x00 };
		std::array<u8, 2> mInterruptRegistries = { 0x00 };
		std::array<u8, 12> mLCDRegistries = { 0x00 };
		u8 mDmaRegistry = 0x00;

		DMACallback mDMACallback = nullptr;
	
	public:
		Memory();
		virtual ~Memory() = default;

		u8 read(u16 const& address) const;
		void write(u16 const& address, u8 const& data);

		u8* getDataPtr(u16 const& address);

		void setDMACallback(const DMACallback& callback) { mDMACallback = callback; }

		void reset();

	private:
		void writeLCD(const u16& address, const u8& data);
		u8 readLCD(const u16& address) const;
		u8* getLCDPtr(const u16& address);
		

};

