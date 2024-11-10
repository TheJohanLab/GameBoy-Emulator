#include "Instruction16BitLoad.h"


//// private methods ////
void Instruction16BitLoad::LD_RRcd16(CPU& cpu, combinedRegistries& registries)
{

	u16 d16 = readNextTwoOpcodes(cpu);
	registries.setValue(d16);

}

void Instruction16BitLoad::LD_RRcd16(CPU& cpu, u16* registry)
{
	u16 d16 = readNextTwoOpcodes(cpu);
	*registry = d16; 
}

void Instruction16BitLoad::PUSH_RR(CPU& cpu, combinedRegistries& registries)
{
	u16* SP = cpu.getSP();
	u8* lowRegistry = registries.getLowRegistry();
	u8* highRegistry = registries.getHighRegistry();
	*SP -= 1;
	cpu.writeMemory(*SP, *highRegistry);
	*SP -= 1;
	cpu.writeMemory(*SP, *lowRegistry);

}

void Instruction16BitLoad::POP_RR(CPU& cpu, combinedRegistries& registries)
{
	u16* SP = cpu.getSP();
	u8* lowRegistry = registries.getLowRegistry();
	u8* highRegistry = registries.getHighRegistry();
	*lowRegistry = cpu.readMemory(*SP);
	*SP += 1;
	*highRegistry = cpu.readMemory(*SP);
	*SP += 1;

}

/// Public methods ////
Instruction16BitLoad::Instruction16BitLoad(const char* name, u8(*pInstruction)(CPU& cpu), u8 ClockCycle)
	:Instruction(name, pInstruction, ClockCycle)
{
}


u8 Instruction16BitLoad::LD_BCcd16(CPU& cpu)
{
	combinedRegistries* BCRegistries = cpu.getCombinedRegistries("BC");
	LD_RRcd16(cpu, *BCRegistries);

	return 12;
}

u8 Instruction16BitLoad::LD_pa16qcSP(CPU& cpu)
{
	//TODO Verifier cette instruction
	u16* PC = cpu.getPC();
	*PC += 1;
	u16* SP = cpu.getSP();
	
	cpu.writeMemory(*PC, *SP & 0xFF);
	cpu.writeMemory((*PC) + 1, (*SP) >> 8);

	return 20;
}

u8 Instruction16BitLoad::LD_DEcd16(CPU& cpu)
{
	combinedRegistries* DERegistries = cpu.getCombinedRegistries("DE");
	LD_RRcd16(cpu, *DERegistries);

	return 12;
}

u8 Instruction16BitLoad::LD_HLcd16(CPU& cpu)
{
	combinedRegistries* HLRegistries = cpu.getCombinedRegistries("HL");
	LD_RRcd16(cpu, *HLRegistries);

	return 12;
}

u8 Instruction16BitLoad::LD_SPcd16(CPU& cpu)
{
	u16* SPRegistry = cpu.getSP();
	LD_RRcd16(cpu, SPRegistry);

	return 12;
}

u8 Instruction16BitLoad::POP_BC(CPU& cpu)
{
	combinedRegistries* BC = cpu.getCombinedRegistries("BC");
	POP_RR(cpu, *BC);

	return 12;
}

u8 Instruction16BitLoad::PUSH_BC(CPU& cpu)
{
	combinedRegistries* BC = cpu.getCombinedRegistries("BC");
	PUSH_RR(cpu, *BC);

	return 16;
}

u8 Instruction16BitLoad::POP_DE(CPU& cpu)
{
	combinedRegistries* DE = cpu.getCombinedRegistries("DE");
	POP_RR(cpu, *DE);

	return 12;
}

u8 Instruction16BitLoad::PUSH_DE(CPU& cpu)
{
	combinedRegistries* DE = cpu.getCombinedRegistries("DE");
	PUSH_RR(cpu, *DE);

	return 16;
}

u8 Instruction16BitLoad::POP_HL(CPU& cpu)
{
	combinedRegistries* HL = cpu.getCombinedRegistries("HL");
	POP_RR(cpu, *HL);

	return 12;
}

u8 Instruction16BitLoad::PUSH_HL(CPU& cpu)
{
	combinedRegistries* HL = cpu.getCombinedRegistries("HL");
	PUSH_RR(cpu, *HL);

	return 16;
}

u8 Instruction16BitLoad::POP_AF(CPU& cpu)
{
	u16* SP = cpu.getSP();
	setFlags(cpu, cpu.readMemory(*SP));
	*SP += 1;
	cpu.setRegistries("A", cpu.readMemory(*SP));
	*SP += 1;

	return 12;
}

u8 Instruction16BitLoad::PUSH_AF(CPU& cpu)
{
	u16* SP = cpu.getSP();
	*SP -= 1;
	cpu.writeMemory(*SP, *cpu.getRegistries("A"));
	*SP -= 1;
	cpu.writeMemory(*SP, cpu.getFlagRegistry()->F);

	return 16;
}

//TODO verifier cette instruction
u8 Instruction16BitLoad::LDHL_SPcr8(CPU& cpu)
{
	u16* PC = cpu.getPC();
	u16* SP = cpu.getSP();
	
	*PC += 1;
	int8_t e = static_cast<int8_t>(cpu.readMemory(*PC));
	
	clearFlag(cpu, 'Z');
	clearFlag(cpu, 'N');
	setHFlag(cpu, *SP, e, false);
	setCFlag(cpu, *SP, e, false);
	
	cpu.setCombinedRegistries("HL", (*SP) + e);

	return 12;
}

u8 Instruction16BitLoad::LD_SPcHL(CPU& cpu)
{
	combinedRegistries* HL = cpu.getCombinedRegistries("HL");
	u16* SP = cpu.getSP();

	*SP = HL->getValue();

	return 8;
}
