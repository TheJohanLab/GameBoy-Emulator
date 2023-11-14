 #pragma once

#include "../Instruction/InstructionInclude.h"
#include "../Utils/Utils.h"
#include "../Bus/Bus.h"
#include "../Clock/Clock.h"
#include "../Registries/Registries.h"
#include <array>

class CPU
{
	private:
		Bus mBus;
		Registries mRegistries;
		std::array<Instruction*, instructionAmount> mInstructionSet;
	
		void initInstructionSet();

	public:
		CPU();
		CPU(Bus const & bus);
		virtual ~CPU() = default;

		u8 executeOpcode(u16 opcode) const;
		void callInterruptHandler(u16 const &address);

		void setAF(u16 val) { mRegistries.setAF(val); }

		
};

