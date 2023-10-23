#pragma once

#include "Instruction.h"

class InstructionCPUControl : public Instruction
{
		public:
			InstructionCPUControl(std::string const& name, void (*pInstruction)(), u8 clockCycles);
			virtual ~InstructionCPUControl() = default;

};

