#pragma once

#include "Instruction.h"
#include "../CPU/CPU.h"

class InstructionJump : public Instruction
{
			public:
				InstructionJump(std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles);
				virtual ~InstructionJump() = default;
};

