 #pragma once

#include "../Instruction/InstructionInclude.h"
#include "../Utils/Utils.h"
#include "../Bus/Bus.h"
#include "../Clock/Clock.h"
#include "../Registries/Registries.h"
#include <array>
#include <map>
#include <functional>

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
		u8 executeOpcodeCB(CPU &cpu) const;
		void callInterruptHandler(u16 const &address);

		void setAF(u16 val) { mRegistries.setAF(val); }

		u8 getRegistries(std::string registry);
		void setRegistries(std::string registry, u8 value);

		
};

