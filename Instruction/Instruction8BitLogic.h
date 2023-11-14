#pragma once

#include "Instruction.h"
#include "../CPU/CPU.h"

class Instruction8BitLogic : public Instruction
{
	public:
		Instruction8BitLogic(std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles);
		virtual ~Instruction8BitLogic() = default;
};

