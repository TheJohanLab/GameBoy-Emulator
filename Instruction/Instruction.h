#pragma once
#include <string>
#include "../Utils/Utils.h"

class Instruction
{
	protected:
		std::string name;
		// Fonction ptr
		u8 clockCycle;

	public:
		Instruction();
		virtual ~Instruction() = default;
};

