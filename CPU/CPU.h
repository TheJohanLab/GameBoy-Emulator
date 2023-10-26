 #pragma once

#include "../Utils/Utils.h"
#include "../Bus/Bus.h"
#include "../Clock/Clock.h"
#include "../Registries/Registries.h"
#include "../Instruction/InstructionInclude.h"
#include <array>

class CPU
{
	private:
		Bus mBus;
		Registries mRegistries;
		std::array<Instruction*, instructionAmount> mInstructionSet;

	void initInstructionSet();

	public:
		CPU(Bus const & bus);
		virtual ~CPU() = default;

		void executeOpcode();
		void callInterruptHandler(u16 const &address);
		
};

