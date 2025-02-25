#pragma once

#include <array>
#include "Utils/Utils.h"

#include <functional>
#include "Utils/Addresses.h"


struct MemoryRegion 
{
	u16 size;
	u16 offset;
};

union MemoryUnion
{
	std::array<u8, MEMORY_SIZE> rawMemory;
	struct
	{
		u8 _padding1[0x8000];  // TODO 0x0000 - 0x7FFF CARTRIDGE
		std::array<u8, 0x2000> VRAM; // 0x8000 - 0x9FFF
		std::array<u8, 0x2000> ERAM; // 0xA000 - 0xBFFF
		std::array<u8, 0x2000> WRAM; // 0xC000 - 0xDFFF
		u8 _padding2[0x1E00];  // 0xE000 - 0xFDFF echo RAM (not used)
		std::array<u8, 0x00A0> OAM;  // 0xFE00 - 0xFE9F 
		u8 _padding3[0x0060];  // 0xFEA0 - 0xFEFF (not used)
		u8 _padding4[0x000F];  // 0xFEA0 - 0xFEFF (not used)
		u8 IF;				   // 0xFF0F
		u8 _padding5[0x0030]; // TODO check these values 0xFF10 - 0xFF3F
		std::array<u8, 12> LCD_CTRL; //0xFF40 - 0xFF4B 
		u8 _padding6[0x0034]; //0xFF4C - 0x FF7F
		std::array<u8, 0x007F> HRAM; // 0xFF80 - 0xFFFE 
		u8 IE;  // 0xFFFF (Interruption Enable Register)
	};

	MemoryUnion() {
		rawMemory.fill(0x00);
	}

};


class Memory
{
	private:
		
		//std::array<u8, 8 * kiB> mWRAM = { 0x00 };
		//std::array<u8, 8 * kiB> mVRAM = { 0x00 };
		//std::array<u8, 8 * kiB> mERAM = { 0x00 };
		//std::array<u8, HRAM_SIZE> mHRAM = { 0x00 };
		//std::array<u8, OAM_SIZE> mOAM = { 0x00 };
		//std::array<u8, 2> mInterruptRegistries = { 0x00 };
		//std::array<u8, 12> mLCDRegistries = { 0x00 };
		MemoryUnion mMemory;

		std::vector<std::pair<std::string, MemoryRegion>> mMemoryRegions =
		{
			{"VRAM"		, {(u16)mMemory.VRAM.size()		, VRAM_OFFSET}},
			{"ERAM"		, {(u16)mMemory.ERAM.size()		, ERAM_OFFSET}},
			{"WRAM"		, {(u16)mMemory.WRAM.size()		, WRAM_OFFSET}},
			{"OAM"		, {(u16)mMemory.OAM.size()		, OAM_OFFSET}},
			{"LCD_CTRL"	, {(u16)mMemory.LCD_CTRL.size()	, LCD_CTRL_OFFSET}},
			{"HRAM"		, {(u16)mMemory.HRAM.size()		, HRAM_OFFSET}},
			{"IF"		, {1							, IF_OFFSET}},
			{"IE"		, {1							, IE_OFFSET}}
		};

		using writerHandler = std::function<void(const u16, const u8)>;
		writerHandler mWriterHandler[MEMORY_SIZE];
	
	public:
		Memory();
		virtual ~Memory() = default;

		u8 read(u16 const address) const;
		void write(u16 const address, u8 const data);

		u8* getDataPtr(u16 const address);

		void reset();

		const MemoryUnion& getMemory() const;
		std::vector<std::pair<std::string, MemoryRegion>> getMemoryRegions() const;
		const u8* getMemoryRegionData(const MemoryRegion& region) const;

	private:
		void initWriterHandler();
		void defaultWrite(const u16 address, const u8 data);
		void DMAWrite(const u16 address, const u8 data);


//callbacks
	using DMACallback = std::function<void(const u8)>;
public:
	void setDMACallback(const DMACallback& callback) { mDMACallback = callback; }
private:	
	DMACallback mDMACallback = nullptr;
};

