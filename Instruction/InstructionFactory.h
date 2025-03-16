#pragma once
#include <iostream>
//#include "../Utils/Utils.h"
#include "InstructionInclude.h"


class Registries;
class Bus;

class InstructionFactory
{
	private:
		Registries& mRegistriesRef;
		std::shared_ptr<Bus> mBusRef;

	public :
		InstructionFactory(Registries&, std::shared_ptr<Bus>);
		virtual ~InstructionFactory() = default;
		//Instruction* createInstruction(InstructionEnum instructionEnum, const char* name, u8 (*pInstruction)(CPU & cpu), u8 clockCycles) const;
		//New approch
		std::unique_ptr<Instruction> createInstruction(InstructionEnum instructionEnum, const char* name, std::function<u8(CPU& cpu)>) const;
};

