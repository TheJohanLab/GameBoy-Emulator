#pragma once

#include "../Utils/Utils.h"
#include "../Bus/Bus.h"
#include "../Clock/Clock.h"
#include "../Registries/Registries.h"
#include "../Instruction/Instruction.h"
#include <array>

class CPU
{
	private:

	Bus mBus;
	Registries mRegistries;
	std::array<Instruction, instructionAmount> mInstructionSet;

	public:
	CPU(Bus const & bus);
	virtual ~CPU() = default;

	void executeOpcode(u8 const & opcode, Clock & clock);
	void callInterruptHandler(u16 const &address);

};

