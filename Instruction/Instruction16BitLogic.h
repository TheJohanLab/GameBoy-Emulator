#pragma once

#include "Instruction.h"

class Instruction16BitLogic : public Instruction
{
	public:
		Instruction16BitLogic(std::string const& name, void (*pInstruction)(), u8 clockCycles);
		virtual ~Instruction16BitLogic() = default;
};

