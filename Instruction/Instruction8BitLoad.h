#pragma once

#include "Instruction.h"
#include "../CPU/CPU.h"

class Instruction8BitLoad : public Instruction
{
	public:
		Instruction8BitLoad(std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles);
		virtual ~Instruction8BitLoad() = default;
	
};

