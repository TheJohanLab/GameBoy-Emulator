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

public:
	Instruction();
	virtual ~Instruction() = default;

	std::string getName() const { return mName; }
	auto getFunctionPointer() const { return pmInstruction; }
	u8 getClockCycle() const { return mClockCycle; }
};

