#pragma once
#include <iostream>
#include "../Utils/Utils.h"
#include "InstructionInclude.h"



class InstructionFactory
{
	private:

	public :
		InstructionFactory();
		virtual ~InstructionFactory() = default;
		Instruction* createInstruction(InstructionEnum instructionEnum, const char* name, u8 (*pInstruction)(CPU & cpu), u8 clockCycles) const;
};

