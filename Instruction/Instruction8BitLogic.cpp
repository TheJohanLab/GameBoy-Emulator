#include "Instruction8BitLogic.h"

Instruction8BitLogic::Instruction8BitLogic(std::string const & name, void (*pInstruction)(CPU & cpu), u8 ClockCycle)
{
	mName = name;
	pmInstruction = pInstruction;
	mClockCycle = ClockCycle;

}

void Instruction8BitLogic::INC_B(CPU& cpu)
{
}

void Instruction8BitLogic::DEC_B(CPU& cpu)
{
}

void Instruction8BitLogic::INC_C(CPU& cpu)
{
}

void Instruction8BitLogic::DEC_C(CPU& cpu)
{
}

void Instruction8BitLogic::INC_D(CPU& cpu)
{
}

void Instruction8BitLogic::DEC_D(CPU& cpu)
{
}

void Instruction8BitLogic::INC_E(CPU& cpu)
{
}

void Instruction8BitLogic::DEC_E(CPU& cpu)
{
}

void Instruction8BitLogic::INC_H(CPU& cpu)
{
}

void Instruction8BitLogic::DEC_H(CPU& cpu)
{
}

void Instruction8BitLogic::DAA(CPU& cpu)
{
}

void Instruction8BitLogic::INC_L(CPU& cpu)
{
}

void Instruction8BitLogic::DEC_L(CPU& cpu)
{
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
}

void Instruction8BitLogic::DEC_A(CPU& cpu)
{
}

void Instruction8BitLogic::CCF(CPU& cpu)
{
}

void Instruction8BitLogic::ADD_AcB(CPU& cpu)
{
}

void Instruction8BitLogic::ADD_AcC(CPU& cpu)
{
}

void Instruction8BitLogic::ADD_AcD(CPU& cpu)
{
}

void Instruction8BitLogic::ADD_AcE(CPU& cpu)
{
}

void Instruction8BitLogic::ADD_AcH(CPU& cpu)
{
}

void Instruction8BitLogic::ADD_AcL(CPU& cpu)
{
}

void Instruction8BitLogic::ADD_AcpHLq(CPU& cpu)
{
}

void Instruction8BitLogic::ADD_AcA(CPU& cpu)
{
}

void Instruction8BitLogic::ADC_AcB(CPU& cpu)
{
}

void Instruction8BitLogic::ADC_AcC(CPU& cpu)
{
}

void Instruction8BitLogic::ADC_AcD(CPU& cpu)
{
}

void Instruction8BitLogic::ADC_AcE(CPU& cpu)
{
}

void Instruction8BitLogic::ADC_AcH(CPU& cpu)
{
}

void Instruction8BitLogic::ADC_AcL(CPU& cpu)
{
}

void Instruction8BitLogic::ADC_AcpHLq(CPU& cpu)
{
}

void Instruction8BitLogic::ADC_AcA(CPU& cpu)
{
}

void Instruction8BitLogic::SUB_B(CPU& cpu)
{
}

void Instruction8BitLogic::SUB_C(CPU& cpu)
{
}

void Instruction8BitLogic::SUB_D(CPU& cpu)
{
}

void Instruction8BitLogic::SUB_E(CPU& cpu)
{
}

void Instruction8BitLogic::SUB_H(CPU& cpu)
{
}

void Instruction8BitLogic::SUB_L(CPU& cpu)
{
}

void Instruction8BitLogic::SUB_pHLq(CPU& cpu)
{
}

void Instruction8BitLogic::SUB_A(CPU& cpu)
{
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
