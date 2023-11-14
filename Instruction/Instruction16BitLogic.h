#pragma once

#include "Instruction.h"
#include "../CPU/CPU.h"

class Instruction16BitLogic : public Instruction
{
	public:
		Instruction16BitLogic(std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles);
		virtual ~Instruction16BitLogic() = default;
};

