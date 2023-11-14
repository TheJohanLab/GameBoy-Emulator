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
		Instruction* createInstruction(InstructionEnum instructionEnum, std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles) const;
};

