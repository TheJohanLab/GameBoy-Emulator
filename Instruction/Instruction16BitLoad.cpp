#include "pch.h"

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

void Instruction16BitLoad::PUSH_RR(CPU& cpu, u16& doubleRegistry)
{
	u8& lowRegistry = GET_LOW_REG(doubleRegistry);
	u8& highRegistry = GET_HIGH_REG(doubleRegistry);
	(*mSP)--;
	mBus->write(*mSP, highRegistry);
	(*mSP)--;
	cpu.writeMemory(*mSP, lowRegistry);

}

void Instruction16BitLoad::POP_RR(CPU& cpu, u16& doubleRegistry)
{
	
	u8& lowRegistry = GET_LOW_REG(doubleRegistry);
	u8& highRegistry = GET_HIGH_REG(doubleRegistry);

	lowRegistry = mBus->read((*mSP)++);
	highRegistry = mBus->read((*mSP)++);

	doubleRegistry;

}

/// Public methods ////
Instruction16BitLoad::Instruction16BitLoad(const char* name, std::function<u8(CPU& cpu)> instruction, Registries& reg, std::shared_ptr<Bus> bus)
	:Instruction(name, instruction, reg, bus)
{
}


u8 Instruction16BitLoad::LD_BCcd16(CPU& cpu)
{
	(*mDoubleRegistries)[DoubleReg::BC].get() = readNextTwoOpcodes(cpu);

	return 12;
}

u8 Instruction16BitLoad::LD_pa16qcSP(CPU& cpu)
{

	u16 address = readNextTwoOpcodes(cpu);
		
	mBus->write(address, *mSP & 0xFF);
	mBus->write(address + 1 , *mSP >> 8);

	return 20;
}

u8 Instruction16BitLoad::LD_DEcd16(CPU& cpu)
{
	(*mDoubleRegistries)[DoubleReg::DE].get() = readNextTwoOpcodes(cpu);

	return 12;
}

u8 Instruction16BitLoad::LD_HLcd16(CPU& cpu)
{
	(*mDoubleRegistries)[DoubleReg::HL].get() = readNextTwoOpcodes(cpu);

	return 12;
}

u8 Instruction16BitLoad::LD_SPcd16(CPU& cpu)
{
	*mSP = readNextTwoOpcodes(cpu);

	return 12;
}

u8 Instruction16BitLoad::POP_BC(CPU& cpu)
{
	u16& BC = (*mDoubleRegistries)[DoubleReg::BC];
	POP_RR(cpu, BC);

	return 12;
}

u8 Instruction16BitLoad::PUSH_BC(CPU& cpu)
{
	u16 & BC = (*mDoubleRegistries)[DoubleReg::BC];
	PUSH_RR(cpu, BC);

	return 16;
}

u8 Instruction16BitLoad::POP_DE(CPU& cpu)
{
	u16& DE = (*mDoubleRegistries)[DoubleReg::DE];
	POP_RR(cpu, DE);

	return 12;
}

u8 Instruction16BitLoad::PUSH_DE(CPU& cpu)
{
	u16& DE = (*mDoubleRegistries)[DoubleReg::DE];
	PUSH_RR(cpu, DE);

	return 16;
}

u8 Instruction16BitLoad::POP_HL(CPU& cpu)
{
	u16& HL = (*mDoubleRegistries)[DoubleReg::HL];
	POP_RR(cpu, HL);

	return 12;
}

u8 Instruction16BitLoad::PUSH_HL(CPU& cpu)
{
	u16& HL = (*mDoubleRegistries)[DoubleReg::HL];
	PUSH_RR(cpu, HL);

	return 16;
}

u8 Instruction16BitLoad::POP_AF(CPU& cpu)
{

	u16& AF = (*mDoubleRegistries)[DoubleReg::AF];
	POP_RR(cpu, AF);

	return 12;
}

u8 Instruction16BitLoad::PUSH_AF(CPU& cpu)
{
	u16& AF = (*mDoubleRegistries)[DoubleReg::AF];
	PUSH_RR(cpu, AF);

	return 16;
}


u8 Instruction16BitLoad::LDHL_SPcr8(CPU& cpu)
{
	int8_t e = static_cast<int8_t>(readNextOpcode(cpu));
	u16 result = *mSP + e;
	*mSP = result;
	(*mDoubleRegistries)[DoubleReg::HL].get() = *mSP;
	
	setZFlag(cpu, 0x0);
	setNFlag(cpu, 0x0);
	
	//TODO verifier ces flags
	setHFlag(cpu, ((*mSP & 0x0F) + (e & 0x0F)) > 0x0F);
	setCFlag(cpu, ( result & 0xFF00) > 0);

	return 12;
}

u8 Instruction16BitLoad::LD_SPcHL(CPU& cpu)
{
	u16 HL = (*mDoubleRegistries)[DoubleReg::HL];
	*mSP = HL;

	return 8;
}
