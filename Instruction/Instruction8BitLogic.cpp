#include "Instruction8BitLogic.h"


// Private methods
void Instruction8BitLogic::INC_R(CPU& cpu, u8* registry)
{
	setHFlag(cpu, *registry, 1, false);

	*registry += 1;

	updateZFlag(cpu, *registry);
	updateNFlag(cpu, 0);
}

void Instruction8BitLogic::DEC_R(CPU& cpu, u8* registry)
{
	setHFlag(cpu, *registry, 1, true);

	*registry -= 1;

	updateZFlag(cpu, *registry);
	updateNFlag(cpu, 1);
}

void Instruction8BitLogic::ADD_RcR(CPU& cpu, u8* srcRegistry, u8* dstRegistry)
{
	setHFlag(cpu, *dstRegistry, *srcRegistry, false);
	setCFlag(cpu, *dstRegistry, *srcRegistry, false);

	*dstRegistry += *srcRegistry;

	updateNFlag(cpu, 0);
	updateZFlag(cpu, *dstRegistry);

}

void Instruction8BitLogic::ADC_RcR(CPU& cpu, u8* srcRegistry, u8* dstRegistry)
{
	u8 carryFlag = cpu.getFlagRegistry()->flags.C;
	setHFlag(cpu, *dstRegistry, *srcRegistry + carryFlag, false);
	setCFlag(cpu, *dstRegistry, *srcRegistry + carryFlag, false);

	*dstRegistry += *srcRegistry + carryFlag;

	updateNFlag(cpu, 0);
	updateZFlag(cpu, *dstRegistry);

}

void Instruction8BitLogic::SUB_RcR(CPU& cpu, u8* srcRegistry, u8* dstRegistry)
{
	setHFlag(cpu, *dstRegistry, *srcRegistry, true);
	setCFlag(cpu, *dstRegistry, *srcRegistry, true);

	*dstRegistry -= *srcRegistry;

	updateNFlag(cpu, 0x01);
	updateZFlag(cpu, *dstRegistry);
}



// Public methods

Instruction8BitLogic::Instruction8BitLogic(std::string const & name, void (*pInstruction)(CPU & cpu), u8 ClockCycle)
{
	mName = name;
	pmInstruction = pInstruction;
	mClockCycle = ClockCycle;

}

void Instruction8BitLogic::INC_B(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	INC_R(cpu, registry);
}

void Instruction8BitLogic::DEC_B(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	DEC_R(cpu, registry);
}

void Instruction8BitLogic::INC_C(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	INC_R(cpu, registry);
}

void Instruction8BitLogic::DEC_C(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	DEC_R(cpu, registry);
}

void Instruction8BitLogic::INC_D(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	INC_R(cpu, registry);
}

void Instruction8BitLogic::DEC_D(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	DEC_R(cpu, registry);
}

void Instruction8BitLogic::INC_E(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	INC_R(cpu, registry);
}

void Instruction8BitLogic::DEC_E(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	DEC_R(cpu, registry);
}

void Instruction8BitLogic::INC_H(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	INC_R(cpu, registry);
}

void Instruction8BitLogic::DEC_H(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	DEC_R(cpu, registry);
}

void Instruction8BitLogic::DAA(CPU& cpu)
{
}

void Instruction8BitLogic::INC_L(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	INC_R(cpu, registry);
}

void Instruction8BitLogic::DEC_L(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	DEC_R(cpu, registry);
}

void Instruction8BitLogic::CPL(CPU& cpu)
{
}

void Instruction8BitLogic::INC_pHLq(CPU& cpu)
{
}

void Instruction8BitLogic::DEC_pHLq(CPU& cpu)
{
}

void Instruction8BitLogic::SCF(CPU& cpu)
{
}

void Instruction8BitLogic::INC_A(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	INC_R(cpu, registry);
}

void Instruction8BitLogic::DEC_A(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	DEC_R(cpu, registry);
}

void Instruction8BitLogic::CCF(CPU& cpu)
{
}

void Instruction8BitLogic::ADD_AcB(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("B");
	ADD_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::ADD_AcC(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("C");
	ADD_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::ADD_AcD(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("D");
	ADD_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::ADD_AcE(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("E");
	ADD_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::ADD_AcH(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("H");
	ADD_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::ADD_AcL(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("L");
	ADD_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::ADD_AcpHLq(CPU& cpu)
{
	u8* A_registry = cpu.getRegistries("A");
	combinedRegistries* HL_registry = cpu.getCombinedRegistries("HL");
	u8 addData = cpu.readMemory(*HL_registry);

	ADD_RcR(cpu, &addData, A_registry);

}

void Instruction8BitLogic::ADD_AcA(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("A");
	ADD_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::ADC_AcB(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("B");
	ADC_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::ADC_AcC(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("C");
	ADC_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::ADC_AcD(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("D");
	ADC_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::ADC_AcE(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("E");
	ADC_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::ADC_AcH(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("H");
	ADC_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::ADC_AcL(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("L");
	ADC_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::ADC_AcpHLq(CPU& cpu)
{
	u8* A_registry = cpu.getRegistries("A");
	combinedRegistries* HL_registry = cpu.getCombinedRegistries("HL");
	u8 addData = cpu.readMemory(*HL_registry);

	ADC_RcR(cpu, &addData, A_registry);
}

void Instruction8BitLogic::ADC_AcA(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("A");
	ADC_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::SUB_B(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("B");
	SUB_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::SUB_C(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("C");
	SUB_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::SUB_D(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("D");
	SUB_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::SUB_E(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("E");
	SUB_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::SUB_H(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("H");
	SUB_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::SUB_L(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("L");
	SUB_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::SUB_pHLq(CPU& cpu)
{
	u8* A_registry = cpu.getRegistries("A");
	combinedRegistries* HL_registry = cpu.getCombinedRegistries("HL");
	u8 addData = cpu.readMemory(*HL_registry);

	SUB_RcR(cpu, &addData, A_registry);
}

void Instruction8BitLogic::SUB_A(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("A");
	SUB_RcR(cpu, srcRegistry, dstRegistry);
}

void Instruction8BitLogic::SBC_AcB(CPU& cpu)
{
}

void Instruction8BitLogic::SBC_AcC(CPU& cpu)
{
}

void Instruction8BitLogic::SBC_AcD(CPU& cpu)
{
}

void Instruction8BitLogic::SBC_AcE(CPU& cpu)
{
}

void Instruction8BitLogic::SBC_AcH(CPU& cpu)
{
}

void Instruction8BitLogic::SBC_AcL(CPU& cpu)
{
}

void Instruction8BitLogic::SBC_AcpHLq(CPU& cpu)
{
}

void Instruction8BitLogic::SBC_AcA(CPU& cpu)
{
}

void Instruction8BitLogic::AND_B(CPU& cpu)
{
}

void Instruction8BitLogic::AND_C(CPU& cpu)
{
}

void Instruction8BitLogic::AND_D(CPU& cpu)
{
}

void Instruction8BitLogic::AND_E(CPU& cpu)
{
}

void Instruction8BitLogic::AND_H(CPU& cpu)
{
}

void Instruction8BitLogic::AND_L(CPU& cpu)
{
}

void Instruction8BitLogic::AND_pHLq(CPU& cpu)
{
}

void Instruction8BitLogic::AND_A(CPU& cpu)
{
}

void Instruction8BitLogic::XOR_B(CPU& cpu)
{
}

void Instruction8BitLogic::XOR_C(CPU& cpu)
{
}

void Instruction8BitLogic::XOR_D(CPU& cpu)
{
}

void Instruction8BitLogic::XOR_E(CPU& cpu)
{
}

void Instruction8BitLogic::XOR_H(CPU& cpu)
{
}

void Instruction8BitLogic::XOR_L(CPU& cpu)
{
}

void Instruction8BitLogic::XOR_pHLq(CPU& cpu)
{
}

void Instruction8BitLogic::XOR_A(CPU& cpu)
{
}

void Instruction8BitLogic::OR_B(CPU& cpu)
{
}

void Instruction8BitLogic::OR_C(CPU& cpu)
{
}

void Instruction8BitLogic::OR_D(CPU& cpu)
{
}

void Instruction8BitLogic::OR_E(CPU& cpu)
{
}

void Instruction8BitLogic::OR_H(CPU& cpu)
{
}

void Instruction8BitLogic::OR_L(CPU& cpu)
{
}

void Instruction8BitLogic::OR_pHLq(CPU& cpu)
{
}

void Instruction8BitLogic::OR_A(CPU& cpu)
{
}

void Instruction8BitLogic::CP_B(CPU& cpu)
{
}

void Instruction8BitLogic::CP_C(CPU& cpu)
{
}

void Instruction8BitLogic::CP_D(CPU& cpu)
{
}

void Instruction8BitLogic::CP_E(CPU& cpu)
{
}

void Instruction8BitLogic::CP_H(CPU& cpu)
{
}

void Instruction8BitLogic::CP_L(CPU& cpu)
{
}

void Instruction8BitLogic::CP_pHLq(CPU& cpu)
{
}

void Instruction8BitLogic::CP_A(CPU& cpu)
{
}

void Instruction8BitLogic::ADD_Acd8(CPU& cpu)
{
}

void Instruction8BitLogic::ADC_Acd8(CPU& cpu)
{
}

void Instruction8BitLogic::SUB_d8(CPU& cpu)
{
}

void Instruction8BitLogic::SBC_Acd8(CPU& cpu)
{
}

void Instruction8BitLogic::AND_d8(CPU& cpu)
{
}

void Instruction8BitLogic::XOR_d8(CPU& cpu)
{
}

void Instruction8BitLogic::OR_d8(CPU& cpu)
{
}

void Instruction8BitLogic::CP_d8(CPU& cpu)
{
}
