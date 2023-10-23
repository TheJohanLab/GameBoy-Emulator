#pragma once

#include "Instruction.h"

class Instruction16BitLoad : public Instruction
{
public:
	Instruction16BitLoad(std::string const& name, void (*pInstruction)(), u8 clockCycles);
	virtual ~Instruction16BitLoad() = default;
};

