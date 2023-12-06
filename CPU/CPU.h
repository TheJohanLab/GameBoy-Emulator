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


		u8* getRegistries(const std::string& registry);
		u16 getCombinedRegistries(const std::string& registry);
		flags* getFlagRegistry() { return mRegistries.getF(); }

		void setRegistries(const std::string & registry, u8 value);
		void setCombinedRegistries(const std::string& registries, u16 value);
		void setFlagRegistry(u8 value) { mRegistries.setF(value); }

		void writeMemory(const u16 & address, const u8 value);
		u8 readMemory(const u16 & address) const;
};

