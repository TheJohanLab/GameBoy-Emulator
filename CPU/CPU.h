 #pragma once

#include "Instruction/InstructionInclude.h"
//#include "Utils/Utils.h"
#include "Bus/Bus.h"
#include "Clock/Clock.h"
#include "Registries/Registries.h"
//#include <array>
//#include <map>
//#include <functional>
//#include <memory>

class PPU;
class BootRom;
class InterruptsManager;

class CPU : std::enable_shared_from_this<CPU>
{
	private:
		static u16 mPC;

		std::shared_ptr<Bus> mBus;
		std::shared_ptr<PPU> mPPU;
		Registries mRegistries;

		std::array<std::unique_ptr<Instruction>, instructionAmount> mInstructionSet;

		std::shared_ptr<BootRom> mBootRom{ nullptr };
		std::shared_ptr<InterruptsManager> mInterruptsManager{ nullptr };
		
		bool mIsCPUStopped{ false };
		std::string mNextOpcodes;

		void initInstructionSet();

	public:
		CPU();
		CPU(std::shared_ptr<Bus> bus, std::shared_ptr<PPU> ppu);
		virtual ~CPU() = default;

		u8 executeOpcode(const u16 opcode);
		u8 executeOpcodeCB(const u16 opcodeCB);
		//void callInterruptHandler();

		u8* getRegistries(const std::string& registry);
		combinedRegistries* getCombinedRegistries(const std::string& registry);
		flags* getFlagRegistry() { return mRegistries.getF(); }
		u16  readPC() const { return mRegistries.getPC(); }
		u16* getPC() { return mRegistries.getPC(); }
		u16* getSP() { return mRegistries.getSP(); }

		void incPC() { *(mRegistries.getPC())+=1; }


		void setRegistries(const std::string & registry, u8 value);
		void setCombinedRegistries(const std::string& registries, u16 value);
		void setFlagRegistry(u8 value) { mRegistries.setF(value); }

		void writeMemory(const u16 & address, const u8 value);
		void writeMemory(const combinedRegistries& address, const u8 value);

		u8 getOpcode();
		u8 getNextOpcodePreview() const;
		u8 readMemory(const u16 & address) const;
		u8 readMemory(const combinedRegistries& address) const;
		u8* getMemoryDataPtr(const combinedRegistries& address);
		u8* getMemoryDataPtr(const u16& address);

		void setIMEFlag();
		void clearIMEFlag();
		u8 getIMEFlag() const;

		
		std::pair<interrupt_flag, interrupt_flag> getInterruptFlags() const;
		void setInterruptFlag(const u8 flags);
		void setInterruptEnable(const u8 flags);

		std::shared_ptr<BootRom> getBootRom();
		std::shared_ptr<InterruptsManager> getInterruptsManager();

		void createInternalComponents(std::weak_ptr<CPU> cpu_weak);

		void stopCPU();
		void resumeCPUFromInterrupt();

		//std::shared_ptr<Registries> getRegistriesRef() { return std::shared_ptr<Registries>(&mRegistries); } //TODO make mRegistries shared_ptr

		void resetMemory();

		void logRegistries();
		void logOpcodesInfos(u8 opcode);

		const std::string getNextOpcodesValue() { return mNextOpcodes; }
		void setNextOpcodesValue(const std::string& opcodes) { mNextOpcodes = opcodes; }

		//New approch
		Registries& getRegistriesRef() { return mRegistries; }




public:
	static u16 getCurrPC() { return mPC; }
};



