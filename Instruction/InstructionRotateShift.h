#pragma once
#include "Instruction.h"
#include "../CPU/CPU.h"

class InstructionRotateShift : public Instruction
{
			public:
				InstructionRotateShift(std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles);
				virtual ~InstructionRotateShift() = default;
};

