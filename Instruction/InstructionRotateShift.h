#pragma once
#include "Instruction.h"

class InstructionRotateShift : public Instruction
{
			public:
				InstructionRotateShift(std::string const& name, void (*pInstruction)(), u8 clockCycles);
				virtual ~InstructionRotateShift() = default;
};

