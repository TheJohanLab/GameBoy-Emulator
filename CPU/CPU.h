 #pragma once

#include "../Instruction/InstructionInclude.h"
#include "../Utils/Utils.h"
#include "../Bus/Bus.h"
#include "../Clock/Clock.h"
#include "../Registries/Registries.h"
#include "BootRom/BootRom.h"
#include <array>
#include <map>
#include <functional>
#include <memory>

class CPU
{
	private:
		std::shared_ptr<Bus> mBus;
		Registries mRegistries = Registries(*this);
		std::array<Instruction*, instructionAmount> mInstructionSet;
		
		void initInstructionSet();

	public:
		CPU();
		CPU(std::shared_ptr<Bus> bus);
		virtual ~CPU() = default;

		u8 executeOpcode(u16 opcode);
		u8 executeOpcodeCB(u16 opcodeCB);
		void callInterruptHandler();

		u8* getRegistries(const std::string& registry);
		combinedRegistries* getCombinedRegistries(const std::string& registry);
		flags* getFlagRegistry() { return mRegistries.getF(); }
		u16* getPC() { return mRegistries.getPC(); }
		u16* getSP() { return mRegistries.getSP(); }

		void setRegistries(const std::string & registry, u8 value);
		void setCombinedRegistries(const std::string& registries, u16 value);
		//void setFlagRegistry(u8 value) { mRegistries.setF(value); }

		void writeMemory(const u16 & address, const u8 value);
		void writeMemory(const combinedRegistries& address, const u8 value);
		u8 readMemory(const u16 & address) const;
		u8 readMemory(const combinedRegistries& address) const;
		u8* getMemoryDataPtr(const combinedRegistries& address);
		u8* getMemoryDataPtr(const u16& address);

		void setIMEFlag();
		void clearIMEFlag();
		inline u8 getIMEFlag() const;

		
		std::pair<interrupt_flag, interrupt_flag> getInterruptFlags() const;
		void setInterruptFlag(const u8& flags);


};

