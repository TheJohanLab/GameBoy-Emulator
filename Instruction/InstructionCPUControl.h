#pragma once

#include "Instruction.h"
#include "../CPU/CPU.h"

class InstructionCPUControl : public Instruction
{
		public:
			InstructionCPUControl(std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles);
			virtual ~InstructionCPUControl() = default;

			static void nop(CPU & cpu);

};

