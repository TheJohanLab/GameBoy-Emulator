#include "pch.h"

#include "Instruction8BitLogic.h"


// Private methods
void Instruction8BitLogic::INC_R(CPU& cpu, u8& registry)
{
	registry++;

	//setHFlag(cpu, isHalfOverflow(registry, 1));
	setHFlag(cpu, (registry & 0x0F) == 0x00);
	setZFlag(cpu, registry == 0);
	setNFlag(cpu, 0x00);
}

void Instruction8BitLogic::DEC_R(CPU& cpu, u8& registry)
{

	registry--;

	setHFlag(cpu, (registry & 0x0F) == 0x0F); //TODO check if the unit case DEC 0 set the H flag or not
	setZFlag(cpu, registry == 0);
	setNFlag(cpu, 0x01);
}

void Instruction8BitLogic::ADD_RcR(CPU& cpu, u8& registry, const u8 additionalValue)
{
	u16 result = registry + additionalValue;
	registry = result;

	setHFlag(cpu, ((registry & 0x0F) + (additionalValue & 0x0F)) > 0x0F);
	setCFlag(cpu, (result & 0xFF00) > 0);
	setNFlag(cpu, 0x00);
	setZFlag(cpu, registry == 0);

}


//void Instruction8BitLogic::ADC_RcR(CPU& cpu, u8* additionalValue, u8* dstRegistry)
//{
//	u8 carryFlag = cpu.getFlagRegistry()->flags.C;
//	setHFlag(cpu, *dstRegistry, *additionalValue + carryFlag, false);
//	setCFlag(cpu, *dstRegistry, *additionalValue + carryFlag, false);
//
//	*dstRegistry += *additionalValue + carryFlag;
//
//	setNFlag(cpu, 0x00);
//	setZFlag(cpu, *dstRegistry == 0);
//
//}


void Instruction8BitLogic::SUB_RcR(CPU& cpu, u8& registry, const u8 additionalValue)
{
	u8 result = registry - additionalValue;

	registry = result;

	setHFlag(cpu, ((registry & 0x0F) - (additionalValue & 0x0F)) < 0);
	setCFlag(cpu, additionalValue > registry );
	setNFlag(cpu, 0x01);
	setZFlag(cpu, registry == 0);
}

//void Instruction8BitLogic::SBC_RcR(CPU& cpu, u8* additionalValue, u8* dstRegistry)
//{
//	u8 carryFlag = cpu.getFlagRegistry()->flags.C;
//	setHFlag(cpu, *dstRegistry, *additionalValue + carryFlag, true);
//	setCFlag(cpu, *dstRegistry, *additionalValue + carryFlag, true);
//
//	*dstRegistry -= (*additionalValue + carryFlag);
//
//	setNFlag(cpu, 0x01);
//	setZFlag(cpu, *dstRegistry == 0);
//}


void Instruction8BitLogic::AND_R(CPU& cpu, u8& registry, const u8 additionalValue)
{
	registry = registry & additionalValue;

	setZFlag(cpu, registry == 0);
	setHFlag(cpu, 0x01);
	setNFlag(cpu, 0x00);
	setCFlag(cpu, 0x00);
}

void Instruction8BitLogic::XOR_R(CPU& cpu, u8& registry, const u8 additionalValue)
{
	registry = registry ^ additionalValue;

	setZFlag(cpu, registry == 0);
	setHFlag(cpu, 0x00);
	setNFlag(cpu, 0x00);
	setCFlag(cpu, 0x00);
}

void Instruction8BitLogic::OR_R(CPU& cpu, u8& registry, const u8 additionalValue)
{
	registry = registry | additionalValue;

	setZFlag(cpu, registry == 0);
	setHFlag(cpu, 0x00);
	setNFlag(cpu, 0x00);
	setCFlag(cpu, 0x00);
}

void Instruction8BitLogic::CP_R(CPU& cpu, u8& registry, const u8 compareValue)
{
	u8 result = registry - compareValue;

	setZFlag(cpu, result == 0);
	setNFlag(cpu, 0x01);
	setHFlag(cpu, ((registry & 0xf) - (compareValue & 0xf)) < 0);
	setCFlag(cpu, registry < compareValue);
	
}


// Public methods
Instruction8BitLogic::Instruction8BitLogic(const char* name, std::function<u8(CPU& cpu)> instruction, Registries& reg, std::shared_ptr<Bus> bus)
	:Instruction(name, instruction, reg, bus)
{
}

u8 Instruction8BitLogic::INC_B(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	INC_R(cpu, B);

	return 4;
}

u8 Instruction8BitLogic::DEC_B(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	DEC_R(cpu, B);

	return 4;
}

u8 Instruction8BitLogic::INC_C(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	INC_R(cpu, C);

	return 4;
}

u8 Instruction8BitLogic::DEC_C(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	DEC_R(cpu, C);

	return 4;
}

u8 Instruction8BitLogic::INC_D(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	INC_R(cpu, D);

	return 4;
}

u8 Instruction8BitLogic::DEC_D(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	DEC_R(cpu, D);

	return 4;
}

u8 Instruction8BitLogic::INC_E(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	INC_R(cpu, E);

	return 4;
}

u8 Instruction8BitLogic::DEC_E(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	DEC_R(cpu, E);

	return 4;
}

u8 Instruction8BitLogic::INC_H(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	INC_R(cpu, H);

	return 4;
}

u8 Instruction8BitLogic::DEC_H(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	DEC_R(cpu, H);

	return 4;
}

u8 Instruction8BitLogic::DAA(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];

	u16 correction = 0x00;

	if (mFlags->flags.H || (!mFlags->flags.N && (A & 0x0F) > 9))
		correction |= 0x06;
	
	if (mFlags->flags.C || (!mFlags->flags.N && A > 99))
	{
		correction |= 0x60;
		mFlags->flags.C = 1;
	}

	A += mFlags->flags.N ? -correction : correction;

	//if (((correction << 2) & 0x100) != 0) 
	//	mFlags->flags.C = 1;


	setHFlag(cpu, 0);
	setZFlag(cpu, A == 0);

	return 4;
}

u8 Instruction8BitLogic::INC_L(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	INC_R(cpu, L);

	return 4;
}

u8 Instruction8BitLogic::DEC_L(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	DEC_R(cpu, L);

	return 4;
}

u8 Instruction8BitLogic::CPL(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	A = ~A;
	setNFlag(cpu, 0x01);
	setHFlag(cpu, 0x01);

	return 4;
}

u8 Instruction8BitLogic::INC_pHLq(CPU& cpu)
{
	auto& data = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	INC_R(cpu, data);

	return 12;
}

u8 Instruction8BitLogic::DEC_pHLq(CPU& cpu)
{
	auto& data = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	DEC_R(cpu, data);

	return 12;
}

u8 Instruction8BitLogic::SCF(CPU& cpu)
{
	setCFlag(cpu, 0x01);
	setNFlag(cpu, 0x00);
	setHFlag(cpu, 0x00);

	return 4;
}

u8 Instruction8BitLogic::INC_A(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	INC_R(cpu, A);

	return 4;
}

u8 Instruction8BitLogic::DEC_A(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	DEC_R(cpu, A);

	return 4;
}

u8 Instruction8BitLogic::CCF(CPU& cpu)
{
	(*mFlags).flags.C = ~(*mFlags).flags.C;
	setNFlag(cpu, 0x00);
	setHFlag(cpu, 0x00);

	return 4;
}

u8 Instruction8BitLogic::ADD_AcB(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& B = (*mRegistries)[Reg::B];
	ADD_RcR(cpu, A, B);

	return 4;
}

u8 Instruction8BitLogic::ADD_AcC(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& C = (*mRegistries)[Reg::C];
	ADD_RcR(cpu, A, C);

	return 4;
}

u8 Instruction8BitLogic::ADD_AcD(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& D = (*mRegistries)[Reg::D];
	ADD_RcR(cpu, A, D);

	return 4;
}

u8 Instruction8BitLogic::ADD_AcE(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& E = (*mRegistries)[Reg::E];
	ADD_RcR(cpu, A, E);

	return 4;
}

u8 Instruction8BitLogic::ADD_AcH(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& H = (*mRegistries)[Reg::B];
	ADD_RcR(cpu, A, H);

	return 4;
}

u8 Instruction8BitLogic::ADD_AcL(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& L = (*mRegistries)[Reg::L];
	ADD_RcR(cpu, A, L);

	return 4;
}

u8 Instruction8BitLogic::ADD_AcpHLq(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8 additionalValue = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);

	ADD_RcR(cpu, A, additionalValue);

	return 8;
}

u8 Instruction8BitLogic::ADD_AcA(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	ADD_RcR(cpu, A, A);

	return 4;
}

u8 Instruction8BitLogic::ADC_AcB(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& B = (*mRegistries)[Reg::B];
	ADD_RcR(cpu, A, B + mFlags->flags.C);

	return 4;
}

u8 Instruction8BitLogic::ADC_AcC(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& C = (*mRegistries)[Reg::C];
	ADD_RcR(cpu, A, C + mFlags->flags.C);

	return 4;
}

u8 Instruction8BitLogic::ADC_AcD(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& D = (*mRegistries)[Reg::D];
	ADD_RcR(cpu, A, D + mFlags->flags.C);

	return 4;
}

u8 Instruction8BitLogic::ADC_AcE(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& E = (*mRegistries)[Reg::E];
	ADD_RcR(cpu, A, E + mFlags->flags.C);

	return 4;
}

u8 Instruction8BitLogic::ADC_AcH(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& H = (*mRegistries)[Reg::H];
	ADD_RcR(cpu, A, H + mFlags->flags.C);

	return 4;
}

u8 Instruction8BitLogic::ADC_AcL(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& L = (*mRegistries)[Reg::L];
	ADD_RcR(cpu, A, L + mFlags->flags.C);

	return 4;
}

u8 Instruction8BitLogic::ADC_AcpHLq(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8 additionalValue = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);

	ADD_RcR(cpu, A, additionalValue + mFlags->flags.C);

	return 8;
}

u8 Instruction8BitLogic::ADC_AcA(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	ADD_RcR(cpu, A, A + mFlags->flags.C);

	return 4;
}

u8 Instruction8BitLogic::SUB_B(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& B = (*mRegistries)[Reg::B];
	SUB_RcR(cpu, A, B);

	return 4;
}

u8 Instruction8BitLogic::SUB_C(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& C = (*mRegistries)[Reg::C];
	SUB_RcR(cpu, A, C);

	return 4;
}

u8 Instruction8BitLogic::SUB_D(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& D = (*mRegistries)[Reg::D];
	SUB_RcR(cpu, A, D);

	return 4;
}

u8 Instruction8BitLogic::SUB_E(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& E = (*mRegistries)[Reg::E];
	SUB_RcR(cpu, A, E);

	return 4;
}

u8 Instruction8BitLogic::SUB_H(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& H = (*mRegistries)[Reg::H];
	SUB_RcR(cpu, A, H);

	return 4;
}

u8 Instruction8BitLogic::SUB_L(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& L = (*mRegistries)[Reg::L];
	SUB_RcR(cpu, A, L);

	return 4;
}

u8 Instruction8BitLogic::SUB_pHLq(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8 additionalValue = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);

	SUB_RcR(cpu, A, additionalValue);

	return 8;
}

u8 Instruction8BitLogic::SUB_A(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	SUB_RcR(cpu, A, A);

	return 4;
}

u8 Instruction8BitLogic::SBC_AcB(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& B = (*mRegistries)[Reg::B];
	SUB_RcR(cpu, A, B + mFlags->flags.C);

	return 4;
}

u8 Instruction8BitLogic::SBC_AcC(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& C = (*mRegistries)[Reg::C];
	SUB_RcR(cpu, A, C + mFlags->flags.C);

	return 4;
}

u8 Instruction8BitLogic::SBC_AcD(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& D = (*mRegistries)[Reg::D];
	SUB_RcR(cpu, A, D + mFlags->flags.C);

	return 4;
}

u8 Instruction8BitLogic::SBC_AcE(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& E = (*mRegistries)[Reg::E];
	SUB_RcR(cpu, A, E + mFlags->flags.C);

	return 4;
}

u8 Instruction8BitLogic::SBC_AcH(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& H = (*mRegistries)[Reg::H];
	SUB_RcR(cpu, A, H + mFlags->flags.C);

	return 4;
}

u8 Instruction8BitLogic::SBC_AcL(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& L = (*mRegistries)[Reg::L];
	SUB_RcR(cpu, A, L + mFlags->flags.C);

	return 4;
}

u8 Instruction8BitLogic::SBC_AcpHLq(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8 additionalValue = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);

	SUB_RcR(cpu, A, additionalValue + mFlags->flags.C);

	return 8;
}

u8 Instruction8BitLogic::SBC_AcA(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	SUB_RcR(cpu, A, A + mFlags->flags.C);

	return 4;
}

u8 Instruction8BitLogic::AND_B(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& B = (*mRegistries)[Reg::B];
	AND_R(cpu, A, B);

	return 4;
}

u8 Instruction8BitLogic::AND_C(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& C = (*mRegistries)[Reg::C];
	AND_R(cpu, A, C);

	return 4;
}

u8 Instruction8BitLogic::AND_D(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& D = (*mRegistries)[Reg::D];
	AND_R(cpu, A, D);

	return 4;
}

u8 Instruction8BitLogic::AND_E(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& E = (*mRegistries)[Reg::E];
	AND_R(cpu, A, E);

	return 4;
}

u8 Instruction8BitLogic::AND_H(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& H = (*mRegistries)[Reg::H];
	AND_R(cpu, A, H);

	return 4;
}

u8 Instruction8BitLogic::AND_L(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& L = (*mRegistries)[Reg::L];
	AND_R(cpu, A, L);

	return 4;
}

u8 Instruction8BitLogic::AND_pHLq(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8 additionalValue = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	AND_R(cpu, A, additionalValue);

	return 8;

}

u8 Instruction8BitLogic::AND_A(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	AND_R(cpu, A, A);

	return 4;
}

u8 Instruction8BitLogic::XOR_B(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& B = (*mRegistries)[Reg::B];
	XOR_R(cpu, A, B);

	return 4;
}

u8 Instruction8BitLogic::XOR_C(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& C = (*mRegistries)[Reg::C];
	XOR_R(cpu, A, C);

	return 4;
}

u8 Instruction8BitLogic::XOR_D(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& D = (*mRegistries)[Reg::D];
	XOR_R(cpu, A, D);

	return 4;
}

u8 Instruction8BitLogic::XOR_E(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& E = (*mRegistries)[Reg::E];
	XOR_R(cpu, A, E);

	return 4;
}

u8 Instruction8BitLogic::XOR_H(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& H = (*mRegistries)[Reg::H];
	XOR_R(cpu, A, H);

	return 4;
}

u8 Instruction8BitLogic::XOR_L(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& L = (*mRegistries)[Reg::L];
	XOR_R(cpu, A, L);

	return 4;
}

u8 Instruction8BitLogic::XOR_pHLq(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8 additionalValue = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	XOR_R(cpu, A, additionalValue);

	return 8;
}

u8 Instruction8BitLogic::XOR_A(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	XOR_R(cpu, A, A);

	return 4;
}

u8 Instruction8BitLogic::OR_B(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& B = (*mRegistries)[Reg::B];
	OR_R(cpu, A, B);

	return 4;
}

u8 Instruction8BitLogic::OR_C(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& C = (*mRegistries)[Reg::C];
	OR_R(cpu, A, C);

	return 4;
}

u8 Instruction8BitLogic::OR_D(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& D = (*mRegistries)[Reg::D];
	OR_R(cpu, A, D);

	return 4;
}

u8 Instruction8BitLogic::OR_E(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& E= (*mRegistries)[Reg::E];
	OR_R(cpu, A, E);

	return 4;
}

u8 Instruction8BitLogic::OR_H(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& H = (*mRegistries)[Reg::H];
	OR_R(cpu, A, H);

	return 4;
}

u8 Instruction8BitLogic::OR_L(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& L = (*mRegistries)[Reg::L];
	OR_R(cpu, A, L);

	return 4;
}

u8 Instruction8BitLogic::OR_pHLq(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8 additionalValue = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	OR_R(cpu, A, additionalValue);

	return 8;
}

u8 Instruction8BitLogic::OR_A(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	OR_R(cpu, A, A);

	return 4;
}

u8 Instruction8BitLogic::CP_B(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& B = (*mRegistries)[Reg::B];
	CP_R(cpu, A, B);

	return 4;
}

u8 Instruction8BitLogic::CP_C(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& C = (*mRegistries)[Reg::C];
	CP_R(cpu, A, C);

	return 4;
}

u8 Instruction8BitLogic::CP_D(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& D = (*mRegistries)[Reg::D];
	CP_R(cpu, A, D);

	return 4;
}

u8 Instruction8BitLogic::CP_E(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& E = (*mRegistries)[Reg::E];
	CP_R(cpu, A, E);

	return 4;
}

u8 Instruction8BitLogic::CP_H(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& H = (*mRegistries)[Reg::H];
	CP_R(cpu, A, H);

	return 4;
}

u8 Instruction8BitLogic::CP_L(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& L = (*mRegistries)[Reg::L];
	CP_R(cpu, A, L);

	return 4;
}

u8 Instruction8BitLogic::CP_pHLq(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8 compareValue = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	CP_R(cpu, A, compareValue);

	return 8;
}

u8 Instruction8BitLogic::CP_A(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	CP_R(cpu, A, A);

	return 4;
}

u8 Instruction8BitLogic::ADD_Acd8(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8 additionalValue = readNextOpcode(cpu);
	ADD_RcR(cpu, A, additionalValue);

	return 8;
}

u8 Instruction8BitLogic::ADC_Acd8(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8 additionalValue = readNextOpcode(cpu);

	ADD_RcR(cpu, A, additionalValue + (*mFlags).flags.C);

	return 8;
}

u8 Instruction8BitLogic::SUB_d8(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8 additionalValue = readNextOpcode(cpu);
	SUB_RcR(cpu, A, additionalValue);

	return 8;
}

u8 Instruction8BitLogic::SBC_Acd8(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8 additionalValue = readNextOpcode(cpu);

	SUB_RcR(cpu, A, additionalValue + (*mFlags).flags.C);

	return 8;
}

u8 Instruction8BitLogic::AND_d8(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8 additionalValue = readNextOpcode(cpu);
	AND_R(cpu, A, additionalValue);

	return 8;
}

u8 Instruction8BitLogic::XOR_d8(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8 additionalValue = readNextOpcode(cpu);
	XOR_R(cpu, A, additionalValue);

	return 8;
}

u8 Instruction8BitLogic::OR_d8(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8 additionalValue = readNextOpcode(cpu);
	OR_R(cpu, A, additionalValue);

	return 8;
}

u8 Instruction8BitLogic::CP_d8(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8 compareValue = readNextOpcode(cpu);
	CP_R(cpu, A, compareValue);

	return 8;
}
