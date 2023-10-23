#pragma once

#include "Instruction.h"

class Instruction8BitLoad : public Instruction
{
	public:
		Instruction8BitLoad(std::string const& name, void (*pInstruction)(), u8 clockCycles);
		virtual ~Instruction8BitLoad() = default;
	
};

