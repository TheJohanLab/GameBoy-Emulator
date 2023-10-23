#pragma once
#include <iostream>
#include "Instruction.h";
#include "../Utils/Utils.h"
#include "InstructionInclude.h"



class InstructionFactory
{
	protected :

	public :
		InstructionFactory();
		virtual ~InstructionFactory() = default;
		Instruction* createInstruction(InstructionEnum instructionEnum, std::string const& name, void (*pInstruction)(), u8 clockCycles) const;
};

