#pragma once

#include "Instruction.h"

class Instruction8BitLogic : public Instruction
{
	public:
		Instruction8BitLogic(std::string const& name, void (*pInstruction)(), u8 clockCycles);
		virtual ~Instruction8BitLogic() = default;
};

