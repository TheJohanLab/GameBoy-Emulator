#pragma once
#include <iostream>
#include "Instruction.h"
#include "../CPU/CPU.h"

class Instruction1BitOperation : public Instruction
{
	public:
		Instruction1BitOperation(std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles);
		virtual ~Instruction1BitOperation() = default;
		
		static void bit_0cB(CPU & cpu);  //BIT 0, B


	private:

};

