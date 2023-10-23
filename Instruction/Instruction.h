#pragma once
#include <string>
#include "../Utils/Utils.h"

class Instruction
{
protected:
	std::string mName;
	void (*pmInstruction)();
	u8 mClockCycle;

public:
	Instruction();
	virtual ~Instruction() = default;

	auto getFunctionPointer() const { return pmInstruction; }
};

