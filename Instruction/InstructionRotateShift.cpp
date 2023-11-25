#include "InstructionRotateShift.h"

InstructionRotateShift::InstructionRotateShift(std::string const & name, void (*pInstruction)(CPU & cpu), u8 ClockCycle)
{
	mName = name;
	pmInstruction = pInstruction;
	mClockCycle = ClockCycle;

}

void InstructionRotateShift::RLC_B(CPU& cpu) 
{
	u8 registry = cpu.getRegistries("B");
	flags flagRegistry = cpu.getFlagRegistry();
	RLCr(registry, flagRegistry);
}

void InstructionRotateShift::RLC_C(CPU& cpu) 
{
}

void InstructionRotateShift::RLC_D(CPU& cpu) 
{
}

void InstructionRotateShift::RLC_E(CPU& cpu) 
{
}

void InstructionRotateShift::RLC_H(CPU& cpu) 
{
}

void InstructionRotateShift::RLC_L(CPU& cpu) 
{
}

void InstructionRotateShift::RLC_pHLq(CPU& cpu) 
{
}

void InstructionRotateShift::RLC_A(CPU& cpu) 
{
}

void InstructionRotateShift::RRC_B(CPU& cpu) 
{
}

void InstructionRotateShift::RRC_C(CPU& cpu) 
{
}

void InstructionRotateShift::RRC_D(CPU& cpu) 
{
}

void InstructionRotateShift::RRC_E(CPU& cpu) 
{
}

void InstructionRotateShift::RRC_H(CPU& cpu) 
{
}

void InstructionRotateShift::RRC_L(CPU& cpu) 
{
}

void InstructionRotateShift::RRC_pHLq(CPU& cpu) 
{
}

void InstructionRotateShift::RRC_A(CPU& cpu)
{
}

void InstructionRotateShift::RL_B(CPU& cpu)
{
}

void InstructionRotateShift::RL_C(CPU& cpu)
{
}

void InstructionRotateShift::RL_D(CPU& cpu)
{
}

void InstructionRotateShift::RL_E(CPU& cpu)
{
}

void InstructionRotateShift::RL_H(CPU& cpu)
{
}

void InstructionRotateShift::RL_L(CPU& cpu)
{
}

void InstructionRotateShift::RL_pHLq(CPU& cpu)
{
}

void InstructionRotateShift::RL_A(CPU& cpu)
{
	cpu.setRegistries("A", 0x12);
	std::cout << std::hex << unsigned(cpu.getRegistries("A"));
}

void InstructionRotateShift::RR_B(CPU& cpu)
{
}

void InstructionRotateShift::RR_C(CPU& cpu)
{
}

void InstructionRotateShift::RR_D(CPU& cpu)
{
}

void InstructionRotateShift::RR_E(CPU& cpu)
{
}

void InstructionRotateShift::RR_H(CPU& cpu)
{
}

void InstructionRotateShift::RR_L(CPU& cpu)
{
}

void InstructionRotateShift::RR_pHLq(CPU& cpu)
{
}

void InstructionRotateShift::RR_A(CPU& cpu)
{
}

void InstructionRotateShift::SLA_B(CPU& cpu)
{
}

void InstructionRotateShift::SLA_C(CPU& cpu)
{
}

void InstructionRotateShift::SLA_D(CPU& cpu)
{
}

void InstructionRotateShift::SLA_E(CPU& cpu)
{
}

void InstructionRotateShift::SLA_H(CPU& cpu)
{
}

void InstructionRotateShift::SLA_L(CPU& cpu)
{
}

void InstructionRotateShift::SLA_pHLq(CPU& cpu)
{
}

void InstructionRotateShift::SLA_A(CPU& cpu)
{
}

void InstructionRotateShift::SRA_B(CPU& cpu)
{
}

void InstructionRotateShift::SRA_C(CPU& cpu)
{
}

void InstructionRotateShift::SRA_D(CPU& cpu)
{
}

void InstructionRotateShift::SRA_E(CPU& cpu)
{
}

void InstructionRotateShift::SRA_H(CPU& cpu)
{
}

void InstructionRotateShift::SRA_L(CPU& cpu)
{
}

void InstructionRotateShift::SRA_pHLq(CPU& cpu)
{
}

void InstructionRotateShift::SRA_A(CPU& cpu)
{
}

void InstructionRotateShift::RLCr(u8& registry, flags& flagRegistry)
{
	flagRegistry.flags.C = getBit(registry, 7);
	registry = registry << 1;
	setBit(registry, 0, flagRegistry.flags.C);

	flagRegistry.flags.Z = registry == 0x00;
	flagRegistry.flags.H = 0x00;
	flagRegistry.flags.N = 0x00;
}


