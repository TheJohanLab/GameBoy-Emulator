#include "InstructionRotateShift.h"

InstructionRotateShift::InstructionRotateShift(std::string const & name, void (*pInstruction)(CPU & cpu), u8 ClockCycle)
{
	mName = name;
	pmInstruction = pInstruction;
	mClockCycle = ClockCycle;

}

void InstructionRotateShift::RLCA(CPU& cpu)
{
}

void InstructionRotateShift::RRCA(CPU& cpu)
{
}

void InstructionRotateShift::RLA(CPU& cpu)
{
}

void InstructionRotateShift::RRA(CPU& cpu)
{
}

void InstructionRotateShift::RLC_B(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLCr(*registry, *flagRegistry);
}

void InstructionRotateShift::RLC_C(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLCr(*registry, *flagRegistry);
}

void InstructionRotateShift::RLC_D(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLCr(*registry, *flagRegistry);
}

void InstructionRotateShift::RLC_E(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLCr(*registry, *flagRegistry);
}

void InstructionRotateShift::RLC_H(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLCr(*registry, *flagRegistry);
}

void InstructionRotateShift::RLC_L(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLCr(*registry, *flagRegistry);
}

void InstructionRotateShift::RLC_pHLq(CPU& cpu) 
{
}

void InstructionRotateShift::RLC_A(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLCr(*registry, *flagRegistry);
}

void InstructionRotateShift::RRC_B(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRCr(*registry, *flagRegistry);
}

void InstructionRotateShift::RRC_C(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRCr(*registry, *flagRegistry);
}

void InstructionRotateShift::RRC_D(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRCr(*registry, *flagRegistry);
}

void InstructionRotateShift::RRC_E(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRCr(*registry, *flagRegistry);
}

void InstructionRotateShift::RRC_H(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRCr(*registry, *flagRegistry);
}

void InstructionRotateShift::RRC_L(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRCr(*registry, *flagRegistry);
}

void InstructionRotateShift::RRC_pHLq(CPU& cpu) 
{
}

void InstructionRotateShift::RRC_A(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRCr(*registry, *flagRegistry);
}

void InstructionRotateShift::RL_B(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLr(*registry, *flagRegistry);
}

void InstructionRotateShift::RL_C(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLr(*registry, *flagRegistry);
}

void InstructionRotateShift::RL_D(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLr(*registry, *flagRegistry);
}

void InstructionRotateShift::RL_E(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLr(*registry, *flagRegistry);
}

void InstructionRotateShift::RL_H(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLr(*registry, *flagRegistry);
}

void InstructionRotateShift::RL_L(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLr(*registry, *flagRegistry);
}

void InstructionRotateShift::RL_pHLq(CPU& cpu)
{

}

void InstructionRotateShift::RL_A(CPU& cpu)
{
	cpu.setRegistries("A", 0x12);
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLr(*registry, *flagRegistry);
}

void InstructionRotateShift::RR_B(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRr(*registry, *flagRegistry);
}

void InstructionRotateShift::RR_C(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRr(*registry, *flagRegistry);
}

void InstructionRotateShift::RR_D(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRr(*registry, *flagRegistry);
}

void InstructionRotateShift::RR_E(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRr(*registry, *flagRegistry);
}

void InstructionRotateShift::RR_H(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRr(*registry, *flagRegistry);
}

void InstructionRotateShift::RR_L(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRr(*registry, *flagRegistry);
}

void InstructionRotateShift::RR_pHLq(CPU& cpu)
{
}

void InstructionRotateShift::RR_A(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRr(*registry, *flagRegistry);
}

void InstructionRotateShift::SLA_B(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	SLAr(*registry, *flagRegistry);
}

void InstructionRotateShift::SLA_C(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	SLAr(*registry, *flagRegistry);
}

void InstructionRotateShift::SLA_D(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	SLAr(*registry, *flagRegistry);
}

void InstructionRotateShift::SLA_E(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	SLAr(*registry, *flagRegistry);
}

void InstructionRotateShift::SLA_H(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	SLAr(*registry, *flagRegistry);
}

void InstructionRotateShift::SLA_L(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	SLAr(*registry, *flagRegistry);
}

void InstructionRotateShift::SLA_pHLq(CPU& cpu)
{
}

void InstructionRotateShift::SLA_A(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	SLAr(*registry, *flagRegistry);
}

void InstructionRotateShift::SRA_B(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRAr(*registry, *flagRegistry);
}

void InstructionRotateShift::SRA_C(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRAr(*registry, *flagRegistry);
}

void InstructionRotateShift::SRA_D(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRAr(*registry, *flagRegistry);
}

void InstructionRotateShift::SRA_E(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRAr(*registry, *flagRegistry);
}

void InstructionRotateShift::SRA_H(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRAr(*registry, *flagRegistry);
}

void InstructionRotateShift::SRA_L(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRAr(*registry, *flagRegistry);
}

void InstructionRotateShift::SRA_pHLq(CPU& cpu)
{
}

void InstructionRotateShift::SRA_A(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRAr(*registry, *flagRegistry);
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

void InstructionRotateShift::RRCr(u8& registry, flags& flagRegistry)
{
	flagRegistry.flags.C = getBit(registry, 0);
	registry = registry >> 1;
	setBit(registry, 7, flagRegistry.flags.C);

	flagRegistry.flags.Z = registry == 0x00;
	flagRegistry.flags.H = 0x00;
	flagRegistry.flags.N = 0x00;
}

void InstructionRotateShift::RLr(u8& registry, flags& flagRegistry)
{
	u8 carry = flagRegistry.flags.C;
	flagRegistry.flags.C = getBit(registry, 7);
	registry = registry << 1;
	setBit(registry, 0, carry);

	flagRegistry.flags.Z = registry == 0x00;
	flagRegistry.flags.H = 0x00;
	flagRegistry.flags.N = 0x00;
}

void InstructionRotateShift::RRr(u8& registry, flags& flagRegistry)
{
	u8 carry = flagRegistry.flags.C;
	flagRegistry.flags.C = getBit(registry, 0);
	registry = registry >> 1;
	setBit(registry, 7, carry);

	flagRegistry.flags.Z = registry == 0x00;
	flagRegistry.flags.H = 0x00;
	flagRegistry.flags.N = 0x00;
}

void InstructionRotateShift::SLAr(u8& registry, flags& flagRegistry)
{
	flagRegistry.flags.C = getBit(registry, 7);
	registry = registry << 1;

	flagRegistry.flags.Z = registry == 0x00;
	flagRegistry.flags.H = 0x00;
	flagRegistry.flags.N = 0x00;
}

void InstructionRotateShift::SRAr(u8& registry, flags& flagRegistry)
{
	flagRegistry.flags.C = getBit(registry, 0);
	registry = (registry >> 1) | (registry & 0x80);

	flagRegistry.flags.Z = registry == 0x00;
	flagRegistry.flags.H = 0x00;
	flagRegistry.flags.N = 0x00;
}


