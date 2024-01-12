#include "Instruction16BitLoad.h"

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

Instruction16BitLoad::Instruction16BitLoad(std::string const & name, void (*pInstruction)(CPU & cpu), u8 ClockCycle)
{
	mName = name;
	pmInstruction = pInstruction;
	mClockCycle = ClockCycle;

}

void Instruction16BitLoad::LD_BCcd16(CPU& cpu)
{
	combinedRegistries* BCRegistries = cpu.getCombinedRegistries("BC");
	LD_RRcd16(cpu, *BCRegistries);
}

void Instruction16BitLoad::LD_pa16qcSP(CPU& cpu)
{

}

void Instruction16BitLoad::LD_DEcd16(CPU& cpu)
{
	combinedRegistries* DERegistries = cpu.getCombinedRegistries("DE");
	LD_RRcd16(cpu, *DERegistries);
}

void Instruction16BitLoad::LD_HLcd16(CPU& cpu)
{
	combinedRegistries* HLRegistries = cpu.getCombinedRegistries("DE");
	LD_RRcd16(cpu, *HLRegistries);
}

void Instruction16BitLoad::LD_SPcd16(CPU& cpu)
{
	u16* SPRegistry = cpu.getSP();
	LD_RRcd16(cpu, SPRegistry);
}

void Instruction16BitLoad::POP_BC(CPU& cpu)
{
}

void Instruction16BitLoad::PUSH_BC(CPU& cpu)
{
}

void Instruction16BitLoad::POP_DE(CPU& cpu)
{
}

void Instruction16BitLoad::PUSH_DE(CPU& cpu)
{
}

void Instruction16BitLoad::POP_HL(CPU& cpu)
{
}

void Instruction16BitLoad::PUSH_HL(CPU& cpu)
{
}

void Instruction16BitLoad::POP_AF(CPU& cpu)
{
}

void Instruction16BitLoad::PUSH_AF(CPU& cpu)
{
}

void Instruction16BitLoad::LDHL_SPcr8(CPU& cpu)
{
}

void Instruction16BitLoad::LD_SPcHL(CPU& cpu)
{
}
