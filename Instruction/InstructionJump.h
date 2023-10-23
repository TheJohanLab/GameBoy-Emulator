#pragma once

#include "Instruction.h"

class InstructionJump : public Instruction
{
			public:
				InstructionJump(std::string const& name, void (*pInstruction)(), u8 clockCycles);
				virtual ~InstructionJump() = default;
};

