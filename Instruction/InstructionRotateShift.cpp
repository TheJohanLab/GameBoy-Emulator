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
	RLCr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RLC_C(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLCr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RLC_D(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLCr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RLC_E(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLCr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RLC_H(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLCr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RLC_L(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLCr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RLC_pHLq(CPU& cpu) 
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8 data = cpu.readMemory(*cpu.getCombinedRegistries("HL"));
	setCFlag(cpu, getBit(data, 7));
	data = data << 1;
	setBit(data, 0, flagRegistry->flags.C);
	cpu.writeMemory(*cpu.getCombinedRegistries("HL"), data);

	setZFlag(cpu, data);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::RLC_A(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLCr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RRC_B(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRCr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RRC_C(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRCr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RRC_D(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRCr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RRC_E(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRCr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RRC_H(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRCr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RRC_L(CPU& cpu) 
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRCr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RRC_pHLq(CPU& cpu) 
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8 data = cpu.readMemory(*cpu.getCombinedRegistries("HL"));
	setCFlag(cpu, getBit(data, 0));
	data = data >> 1;
	setBit(data, 7, flagRegistry->flags.C);
	cpu.writeMemory(*cpu.getCombinedRegistries("HL"), data);

	setZFlag(cpu, data);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::RRC_A(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRCr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RL_B(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RL_C(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RL_D(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RL_E(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RL_H(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RL_L(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RL_pHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8 carry = flagRegistry->flags.C;
	u8 data = cpu.readMemory(*cpu.getCombinedRegistries("HL"));
	setCFlag(cpu, getBit(data, 7));
	data = data << 1;
	setBit(data, 0, carry);
	cpu.writeMemory(*cpu.getCombinedRegistries("HL"), data);

	setZFlag(cpu, data);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::RL_A(CPU& cpu)
{
	cpu.setRegistries("A", 0x12);
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	RLr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RR_B(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RR_C(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RR_D(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RR_E(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RR_H(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RR_L(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::RR_pHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8 carry = flagRegistry->flags.C;
	u8 data = cpu.readMemory(*cpu.getCombinedRegistries("HL"));
	setCFlag(cpu, getBit(data, 0));
	data = data >> 1;
	setBit(data, 7, carry);
	cpu.writeMemory(*cpu.getCombinedRegistries("HL"), data);

	setZFlag(cpu, data);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::RR_A(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	RRr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SLA_B(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	SLAr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SLA_C(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	SLAr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SLA_D(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	SLAr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SLA_E(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	SLAr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SLA_H(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	SLAr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SLA_L(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	SLAr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SLA_pHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8 data = cpu.readMemory(*cpu.getCombinedRegistries("HL"));
	setCFlag(cpu, getBit(data, 7));
	data = data << 1;
	cpu.writeMemory(*cpu.getCombinedRegistries("HL"), data);

	setZFlag(cpu, data);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::SLA_A(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	SLAr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SRA_B(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRAr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SRA_C(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRAr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SRA_D(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRAr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SRA_E(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRAr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SRA_H(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRAr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SRA_L(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRAr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SRA_pHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8 data = cpu.readMemory(*cpu.getCombinedRegistries("HL"));
	setCFlag(cpu, getBit(data, 0));
	data = (data >> 1) | (data & 0x80);
	cpu.writeMemory(*cpu.getCombinedRegistries("HL"), data);

	setZFlag(cpu, data);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::SRA_A(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRAr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SWAP_B(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	SWAPr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SWAP_C(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	SWAPr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SWAP_D(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	SWAPr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SWAP_E(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	SWAPr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SWAP_H(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	SWAPr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SWAP_L(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	SWAPr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SWAP_pHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8 data = cpu.readMemory(*cpu.getCombinedRegistries("HL"));
	
	u8 lowNibble = data & 0x0F;
	u8 highNibble = data & 0xF0;

	data = (lowNibble << 4) | (highNibble >> 4);

	cpu.writeMemory(*cpu.getCombinedRegistries("HL"), data);

	setZFlag(cpu, data);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
	setCFlag(cpu, 0);

}

void InstructionRotateShift::SWAP_A(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	SWAPr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SRL_B(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRLr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SRL_C(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRLr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SRL_D(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRLr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SRL_E(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRLr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SRL_H(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRLr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SRL_L(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRLr(*registry, *flagRegistry, cpu);
}

void InstructionRotateShift::SRL_pHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8 data = cpu.readMemory(*cpu.getCombinedRegistries("HL"));
	setCFlag(cpu, getBit(data, 0));
	data = data >> 1;
	setBit(data, 7, 0x00);
	cpu.writeMemory(*cpu.getCombinedRegistries("HL"), data);

	setZFlag(cpu, data);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::SRL_A(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	SRLr(*registry, *flagRegistry, cpu);
}



void InstructionRotateShift::RLCr(u8& registry, flags& flagRegistry, CPU& cpu)
{
	setCFlag(cpu, getBit(registry, 7));
	registry = registry << 1;
	setBit(registry, 0, flagRegistry.flags.C);

	setZFlag(cpu, registry);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::RRCr(u8& registry, flags& flagRegistry, CPU& cpu)
{
	setCFlag(cpu, getBit(registry, 0));
	registry = registry >> 1;
	setBit(registry, 7, flagRegistry.flags.C);

	setZFlag(cpu, registry);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::RLr(u8& registry, flags& flagRegistry, CPU& cpu)
{
	u8 carry = flagRegistry.flags.C;
	setCFlag(cpu, getBit(registry, 7));
	registry = registry << 1;
	setBit(registry, 0, carry);

	setZFlag(cpu, registry);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::RRr(u8& registry, flags& flagRegistry, CPU& cpu)
{
	u8 carry = flagRegistry.flags.C;
	setCFlag(cpu, getBit(registry, 0));
	registry = registry >> 1;
	setBit(registry, 7, carry);

	setZFlag(cpu, registry);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::SLAr(u8& registry, flags& flagRegistry, CPU& cpu)
{
	setCFlag(cpu, getBit(registry, 7));
	registry = registry << 1;

	setZFlag(cpu, registry);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::SRAr(u8& registry, flags& flagRegistry, CPU& cpu)
{
	setCFlag(cpu, getBit(registry, 0));
	registry = (registry >> 1) | (registry & 0x80);

	setZFlag(cpu, registry);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::SWAPr(u8& registry, flags& flagRegistry, CPU& cpu)
{
	// Exchange low and high nibble (4bits)
	u8 lowNibble = registry & 0x0F;
	u8 highNibble = registry & 0xF0;

	registry = (lowNibble << 4) | (highNibble >> 4);

	setZFlag(cpu, registry);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
	setCFlag(cpu, 0);
}

void InstructionRotateShift::SRLr(u8& registry, flags& flagRegistry, CPU& cpu)
{
	// Right shift logical (bit 7 = 0)
	setCFlag(cpu, getBit(registry, 0));

	registry = registry >> 1;
	setBit(registry, 7, 0x00);

	setZFlag(cpu, registry);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}


