#include "Instruction16BitLogic.h"

void Instruction16BitLogic::INC_RR(CPU& cpu, combinedRegistries* registries)
{
	(*registries)++;
}

void Instruction16BitLogic::DEC_RR(CPU& cpu, combinedRegistries* registries)
{
	(*registries)--;
}

void Instruction16BitLogic::ADD_HLcRR(CPU& cpu, combinedRegistries* registries)
{
	combinedRegistries* HLRegistries = cpu.getCombinedRegistries("HL");
	
	//*HLRegistries += registries->getValue();

	clearFlag(cpu, 'N');

}

void Instruction16BitLogic::ADD_HLcRR(CPU& cpu, u16* registries)
{
}

Instruction16BitLogic::Instruction16BitLogic(std::string const & name, void (*pInstruction)(CPU & cpu), u8 ClockCycle)
{
	mName = name;
	pmInstruction = pInstruction;
	mClockCycle = ClockCycle;

}

void Instruction16BitLogic::INC_BC(CPU& cpu)
{
	combinedRegistries* BCRegistries = cpu.getCombinedRegistries("BC");
	INC_RR(cpu, BCRegistries);
}

void Instruction16BitLogic::ADD_HLcBC(CPU& cpu)
{

}

void Instruction16BitLogic::DEC_BC(CPU& cpu)
{
	combinedRegistries* BCRegistries = cpu.getCombinedRegistries("BC");
	DEC_RR(cpu, BCRegistries);
}

void Instruction16BitLogic::INC_DE(CPU& cpu)
{
	combinedRegistries* DERegistries = cpu.getCombinedRegistries("DE");
	INC_RR(cpu, DERegistries);
}

void Instruction16BitLogic::ADD_HLcDE(CPU& cpu)
{
}

void Instruction16BitLogic::DEC_DE(CPU& cpu)
{
	combinedRegistries* DERegistries = cpu.getCombinedRegistries("DE");
	DEC_RR(cpu, DERegistries);
}

void Instruction16BitLogic::INC_HL(CPU& cpu)
{
	combinedRegistries* BCRegistries = cpu.getCombinedRegistries("HL");
	INC_RR(cpu, BCRegistries);
}

void Instruction16BitLogic::ADD_HLcHL(CPU& cpu)
{
}

void Instruction16BitLogic::DEC_HL(CPU& cpu)
{
	combinedRegistries* HLRegistries = cpu.getCombinedRegistries("HL");
	DEC_RR(cpu, HLRegistries);
}

void Instruction16BitLogic::INC_SP(CPU& cpu)
{
	u16* SPRegistries = cpu.getSP();
	*SPRegistries += 1;
}

void Instruction16BitLogic::ADD_HLcSP(CPU& cpu)
{
}

void Instruction16BitLogic::DEC_SP(CPU& cpu)
{
	u16* SPRegistries = cpu.getSP();
	*SPRegistries -= 1;
}

void Instruction16BitLogic::ADD_SPcr8(CPU& cpu)
{
}
