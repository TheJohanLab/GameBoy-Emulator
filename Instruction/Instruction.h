#pragma once
#include <string>
#include "../Utils/Utils.h"

class CPU;

class Instruction
{
protected:
	std::string mName;
	void (*pmInstruction)(CPU & cpu);
	u8 mClockCycle;
	static u8 getBit(u8 byte, u8 pos) { return (byte >> pos) & 0x01; }
	static void setBit(u8& byte, u8 pos, u8 val) { byte = (byte & ~(0x01 << pos) | (val << pos)); }

public:
	Instruction();
	virtual ~Instruction() = default;

	std::string getName() const { return mName; }
	auto getFunctionPointer() const { return pmInstruction; }
	u8 getClockCycle() const { return mClockCycle; }
};

