#include "pch.h"

#include "Instruction16BitLogic.h"

void Instruction16BitLogic::INC_RR(CPU& cpu, u16& doubleRegistry)
{
	doubleRegistry++;
}

void Instruction16BitLogic::DEC_RR(CPU& cpu, u16& doubleRegistry)
{
	doubleRegistry--;
}


void Instruction16BitLogic::ADD_HLcRR(CPU& cpu, const u16& doubleRegistry)
{
	u16& HL = (*mDoubleRegistries)[DoubleReg::HL];
	u32 result = HL + doubleRegistry;
	u16 prevHL = HL;
	HL = static_cast<u16>(result);

	setNFlag(cpu, 0x00);
	setHFlag(cpu, ((prevHL & 0x0FFF) + (doubleRegistry & 0x0FFF)) > 0x0FFF); 
	setCFlag(cpu, (result & 0xFF0000) > 0);
	
}

Instruction16BitLogic::Instruction16BitLogic(const char* name, std::function<u8(CPU& cpu)> instruction, Registries& reg, std::shared_ptr<Bus> bus)
	:Instruction(name, instruction, reg, bus)
{
}

u8 Instruction16BitLogic::INC_BC(CPU& cpu)
{
	auto& BC = (*mDoubleRegistries)[DoubleReg::BC];
	INC_RR(cpu, BC);

	return 8;
}

u8 Instruction16BitLogic::ADD_HLcBC(CPU& cpu)
{
	u16& BC = (*mDoubleRegistries)[DoubleReg::BC];
	ADD_HLcRR(cpu, BC);

	return 8;
}

u8 Instruction16BitLogic::DEC_BC(CPU& cpu)
{
	auto& BC = (*mDoubleRegistries)[DoubleReg::BC];
	DEC_RR(cpu, BC);

	return 8;
}

u8 Instruction16BitLogic::INC_DE(CPU& cpu)
{
	auto& DE = (*mDoubleRegistries)[DoubleReg::DE];
	INC_RR(cpu, DE);

	return 8;
}

u8 Instruction16BitLogic::ADD_HLcDE(CPU& cpu)
{
	u16& DE = (*mDoubleRegistries)[DoubleReg::DE];
	ADD_HLcRR(cpu, DE);

	return 8;
}

u8 Instruction16BitLogic::DEC_DE(CPU& cpu)
{
	auto& DE = (*mDoubleRegistries)[DoubleReg::DE];
	DEC_RR(cpu, DE);

	return 8;
}

u8 Instruction16BitLogic::INC_HL(CPU& cpu)
{
	auto& HL = (*mDoubleRegistries)[DoubleReg::HL];
	INC_RR(cpu, HL);

	return 8;
}

u8 Instruction16BitLogic::ADD_HLcHL(CPU& cpu)
{
	u16& HL = (*mDoubleRegistries)[DoubleReg::HL];
	ADD_HLcRR(cpu, HL);

	return 8;
}

u8 Instruction16BitLogic::DEC_HL(CPU& cpu)
{
	auto& HL = (*mDoubleRegistries)[DoubleReg::HL];
	DEC_RR(cpu, HL);

	return 8;
}

u8 Instruction16BitLogic::INC_SP(CPU& cpu)
{
	(*mSP)++;

	return 8;
}

u8 Instruction16BitLogic::ADD_HLcSP(CPU& cpu)
{
	ADD_HLcRR(cpu, *mSP);

	return 8;
}

u8 Instruction16BitLogic::DEC_SP(CPU& cpu)
{
	(*mSP)--;

	return 8;
}

u8 Instruction16BitLogic::ADD_SPcr8(CPU& cpu)
{

	return 16;
}
