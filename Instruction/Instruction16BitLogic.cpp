#include "pch.h"

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
	ADD_HLcRR(cpu, registries->getValue());
}

void Instruction16BitLogic::ADD_HLcRR(CPU& cpu, u16 registriesValue)
{
	combinedRegistries* HLRegistries = cpu.getCombinedRegistries("HL");

	u16 result = HLRegistries->getValue() + registriesValue;

	flags* f = cpu.getFlagRegistry();

	f->flags.H = isHalfOverflow(HLRegistries->getValue(), registriesValue) ? 1 : 0;
	f->flags.C = isOverflow(HLRegistries->getValue(), registriesValue) ? 1 : 0;
	clearFlag(cpu, 'N');

	HLRegistries->setValue(result);
}

Instruction16BitLogic::Instruction16BitLogic(const char* name, std::function<u8(CPU& cpu)> instruction, Registries& reg, std::shared_ptr<Bus> bus)
	:Instruction(name, instruction, reg, bus)
{
}

u8 Instruction16BitLogic::INC_BC(CPU& cpu)
{
	combinedRegistries* BCRegistries = cpu.getCombinedRegistries("BC");
	INC_RR(cpu, BCRegistries);

	return 8;
}

u8 Instruction16BitLogic::ADD_HLcBC(CPU& cpu)
{
	combinedRegistries* BC = cpu.getCombinedRegistries("BC");
	ADD_HLcRR(cpu, BC);

	return 8;
}

u8 Instruction16BitLogic::DEC_BC(CPU& cpu)
{
	combinedRegistries* BCRegistries = cpu.getCombinedRegistries("BC");
	DEC_RR(cpu, BCRegistries);

	return 8;
}

u8 Instruction16BitLogic::INC_DE(CPU& cpu)
{
	combinedRegistries* DERegistries = cpu.getCombinedRegistries("DE");
	INC_RR(cpu, DERegistries);

	return 8;
}

u8 Instruction16BitLogic::ADD_HLcDE(CPU& cpu)
{
	combinedRegistries* DE = cpu.getCombinedRegistries("DE");
	ADD_HLcRR(cpu, DE);

	return 8;
}

u8 Instruction16BitLogic::DEC_DE(CPU& cpu)
{
	combinedRegistries* DERegistries = cpu.getCombinedRegistries("DE");
	DEC_RR(cpu, DERegistries);

	return 8;
}

u8 Instruction16BitLogic::INC_HL(CPU& cpu)
{
	combinedRegistries* BCRegistries = cpu.getCombinedRegistries("HL");
	INC_RR(cpu, BCRegistries);

	return 8;
}

u8 Instruction16BitLogic::ADD_HLcHL(CPU& cpu)
{
	combinedRegistries* HL = cpu.getCombinedRegistries("HL");
	ADD_HLcRR(cpu, HL);

	return 8;
}

u8 Instruction16BitLogic::DEC_HL(CPU& cpu)
{
	combinedRegistries* HLRegistries = cpu.getCombinedRegistries("HL");
	DEC_RR(cpu, HLRegistries);

	return 8;
}

u8 Instruction16BitLogic::INC_SP(CPU& cpu)
{
	u16* SPRegistries = cpu.getSP();
	*SPRegistries += 1;

	return 8;
}

u8 Instruction16BitLogic::ADD_HLcSP(CPU& cpu)
{
	u16* SP = cpu.getSP();
	ADD_HLcRR(cpu, *SP);

	return 8;
}

u8 Instruction16BitLogic::DEC_SP(CPU& cpu)
{
	u16* SPRegistries = cpu.getSP();
	*SPRegistries -= 1;

	return 8;
}

u8 Instruction16BitLogic::ADD_SPcr8(CPU& cpu)
{

	return 16;
}
