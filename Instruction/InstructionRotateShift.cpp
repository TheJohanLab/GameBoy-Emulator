#include "pch.h"

#include "InstructionRotateShift.h"

InstructionRotateShift::InstructionRotateShift(const char* name, std::function<u8(CPU& cpu)> instruction, Registries& reg, std::shared_ptr<Bus> bus)
	:Instruction(name, instruction, reg, bus)
{
}

u8 InstructionRotateShift::RLCA(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	setCFlag(cpu, BIT(A, 7));

	A = (A << 1) | (A >> 7);

	setZFlag(cpu, 0);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);

	return 4;
}

u8 InstructionRotateShift::RRCA(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	setCFlag(cpu, BIT(A, 0));

	A = (A >> 1) | (A << 7);

	setZFlag(cpu, 0);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);

	return 4;
}

u8 InstructionRotateShift::RLA(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8 carry = mFlags->flags.C;

	setCFlag(cpu, BIT(A, 7));

	A = (A << 1) | carry;

	setZFlag(cpu, 0);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);

	return 4;
}

u8 InstructionRotateShift::RRA(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8 carry = mFlags->flags.C;

	setCFlag(cpu, BIT(A, 0));

	A = (A >> 1) | (carry << 7);

	setZFlag(cpu, 0);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);

	return 4;
}

u8 InstructionRotateShift::RLC_B(CPU& cpu) 
{
	u8& B = (*mRegistries)[Reg::B];
	RLCr(cpu, B);

	return 8;
}

u8 InstructionRotateShift::RLC_C(CPU& cpu) 
{
	u8& C = (*mRegistries)[Reg::C];
	RLCr(cpu, C);

	return 8;
}

u8 InstructionRotateShift::RLC_D(CPU& cpu) 
{
	u8& D = (*mRegistries)[Reg::D];
	RLCr(cpu, D);

	return 8;
}

u8 InstructionRotateShift::RLC_E(CPU& cpu) 
{
	u8& E = (*mRegistries)[Reg::E];
	RLCr(cpu, E);

	return 8;
}

u8 InstructionRotateShift::RLC_H(CPU& cpu) 
{
	u8& H = (*mRegistries)[Reg::H];
	RLCr(cpu, H);

	return 8;
}

u8 InstructionRotateShift::RLC_L(CPU& cpu) 
{
	u8& L = (*mRegistries)[Reg::L];
	RLCr(cpu, L);

	return 8;
}

u8 InstructionRotateShift::RLC_pHLq(CPU& cpu) 
{
	u8& data = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	RLCr(cpu, data);

	return 16;
}

u8 InstructionRotateShift::RLC_A(CPU& cpu) 
{
	u8& A = (*mRegistries)[Reg::A];
	RLCr(cpu, A);

	return 8;
}

u8 InstructionRotateShift::RRC_B(CPU& cpu) 
{

	u8& B = (*mRegistries)[Reg::B];
	RRCr(cpu, B);

	return 8;
}

u8 InstructionRotateShift::RRC_C(CPU& cpu) 
{
	u8& C = (*mRegistries)[Reg::C];
	RRCr(cpu, C);

	return 8;
}

u8 InstructionRotateShift::RRC_D(CPU& cpu) 
{
	u8& D = (*mRegistries)[Reg::D];
	RRCr(cpu, D);

	return 8;
}

u8 InstructionRotateShift::RRC_E(CPU& cpu) 
{
	u8& E = (*mRegistries)[Reg::E];
	RRCr(cpu, E);

	return 8;
}

u8 InstructionRotateShift::RRC_H(CPU& cpu) 
{
	u8& H = (*mRegistries)[Reg::H];
	RRCr(cpu, H);

	return 8;
}

u8 InstructionRotateShift::RRC_L(CPU& cpu) 
{
	u8& L = (*mRegistries)[Reg::L];
	RRCr(cpu, L);

	return 8;
}

u8 InstructionRotateShift::RRC_pHLq(CPU& cpu) 
{
	u8& data = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	RRCr(cpu, data);

	return 16;
}

u8 InstructionRotateShift::RRC_A(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	RRCr(cpu, A);

	return 8;
}

u8 InstructionRotateShift::RL_B(CPU& cpu)
{
	u8& B = (*mRegistries)[Reg::B];
	RLr(cpu, B);

	return 8;
}

u8 InstructionRotateShift::RL_C(CPU& cpu)
{
	u8& C = (*mRegistries)[Reg::C];
	RLr(cpu, C);

	return 8;
}

u8 InstructionRotateShift::RL_D(CPU& cpu)
{
	u8& D = (*mRegistries)[Reg::D];
	RLr(cpu, D);

	return 8;
}

u8 InstructionRotateShift::RL_E(CPU& cpu)
{
	u8& E = (*mRegistries)[Reg::E];
	RLr(cpu, E);

	return 8;
}

u8 InstructionRotateShift::RL_H(CPU& cpu)
{
	u8& H = (*mRegistries)[Reg::H];
	RLr(cpu, H);

	return 8;
}

u8 InstructionRotateShift::RL_L(CPU& cpu)
{
	u8& L = (*mRegistries)[Reg::L];
	RLr(cpu, L);

	return 8;
}

u8 InstructionRotateShift::RL_pHLq(CPU& cpu)
{
	u8& data = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	RLr(cpu, data);

	return 16;
}

u8 InstructionRotateShift::RL_A(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	RLr(cpu, A);

	return 8;
}

u8 InstructionRotateShift::RR_B(CPU& cpu)
{
	u8& B = (*mRegistries)[Reg::B];
	RRr(cpu, B);

	return 8;
}

u8 InstructionRotateShift::RR_C(CPU& cpu)
{
	u8& C = (*mRegistries)[Reg::C];
	RRr(cpu, C);

	return 8;
}

u8 InstructionRotateShift::RR_D(CPU& cpu)
{
	u8& D = (*mRegistries)[Reg::D];
	RRr(cpu, D);

	return 8;
}

u8 InstructionRotateShift::RR_E(CPU& cpu)
{
	u8& E = (*mRegistries)[Reg::E];
	RRr(cpu, E);

	return 8;
}

u8 InstructionRotateShift::RR_H(CPU& cpu)
{
	u8& H = (*mRegistries)[Reg::H];
	RRr(cpu, H);

	return 8;
}

u8 InstructionRotateShift::RR_L(CPU& cpu)
{
	u8& L = (*mRegistries)[Reg::L];
	RRr(cpu, L);

	return 8;
}

u8 InstructionRotateShift::RR_pHLq(CPU& cpu)
{
	u8& data = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	RRr(cpu, data);

	return 16;
}

u8 InstructionRotateShift::RR_A(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	RRr(cpu, A);

	return 8;
}

u8 InstructionRotateShift::SLA_B(CPU& cpu)
{
	u8& B = (*mRegistries)[Reg::B];
	SLAr(cpu, B);

	return 8;
}

u8 InstructionRotateShift::SLA_C(CPU& cpu)
{
	u8& C = (*mRegistries)[Reg::C];
	SLAr(cpu, C);

	return 8;
}

u8 InstructionRotateShift::SLA_D(CPU& cpu)
{
	u8& D = (*mRegistries)[Reg::D];
	SLAr(cpu, D);

	return 8;
}

u8 InstructionRotateShift::SLA_E(CPU& cpu)
{
	u8& E = (*mRegistries)[Reg::E];
	SLAr(cpu, E);

	return 8;
}

u8 InstructionRotateShift::SLA_H(CPU& cpu)
{
	u8& H = (*mRegistries)[Reg::H];
	SLAr(cpu, H);

	return 8;
}

u8 InstructionRotateShift::SLA_L(CPU& cpu)
{
	u8& L = (*mRegistries)[Reg::L];
	SLAr(cpu, L);

	return 8;
}

u8 InstructionRotateShift::SLA_pHLq(CPU& cpu)
{
	u8& data = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	SLAr(cpu, data);


	return 16;
}

u8 InstructionRotateShift::SLA_A(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	SLAr(cpu, A);

	return 8;
}

u8 InstructionRotateShift::SRA_B(CPU& cpu)
{
	u8& B = (*mRegistries)[Reg::B];
	SRAr(cpu, B);

	return 8;
}

u8 InstructionRotateShift::SRA_C(CPU& cpu)
{
	u8& C = (*mRegistries)[Reg::C];
	SRAr(cpu, C);

	return 8;
}

u8 InstructionRotateShift::SRA_D(CPU& cpu)
{
	u8& D = (*mRegistries)[Reg::D];
	SRAr(cpu, D);

	return 8;
}

u8 InstructionRotateShift::SRA_E(CPU& cpu)
{
	u8& E = (*mRegistries)[Reg::E];
	SRAr(cpu, E);

	return 8;
}

u8 InstructionRotateShift::SRA_H(CPU& cpu)
{
	u8& H = (*mRegistries)[Reg::H];
	SRAr(cpu, H);

	return 8;
}

u8 InstructionRotateShift::SRA_L(CPU& cpu)
{
	u8& L = (*mRegistries)[Reg::L];
	SRAr(cpu, L);

	return 8;
}

u8 InstructionRotateShift::SRA_pHLq(CPU& cpu)
{
	u8& data = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	SRAr(cpu, data);

	return 16;
}

u8 InstructionRotateShift::SRA_A(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	SRAr(cpu, A);

	return 8;
}

u8 InstructionRotateShift::SWAP_B(CPU& cpu)
{
	u8& B = (*mRegistries)[Reg::B];
	SWAPr(cpu, B);

	return 8;
}

u8 InstructionRotateShift::SWAP_C(CPU& cpu)
{
	u8& C = (*mRegistries)[Reg::C];
	SWAPr(cpu, C);

	return 8;
}

u8 InstructionRotateShift::SWAP_D(CPU& cpu)
{
	u8& D = (*mRegistries)[Reg::D];
	SWAPr(cpu, D);

	return 8;
}

u8 InstructionRotateShift::SWAP_E(CPU& cpu)
{
	u8& E = (*mRegistries)[Reg::E];
	SWAPr(cpu, E);

	return 8;
}

u8 InstructionRotateShift::SWAP_H(CPU& cpu)
{
	u8& H = (*mRegistries)[Reg::H];
	SWAPr(cpu, H);

	return 8;
}

u8 InstructionRotateShift::SWAP_L(CPU& cpu)
{
	u8& L = (*mRegistries)[Reg::L];
	SWAPr(cpu, L);

	return 8;
}

u8 InstructionRotateShift::SWAP_pHLq(CPU& cpu)
{
	u8& data = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	SWAPr(cpu, data);

	return 16;
}

u8 InstructionRotateShift::SWAP_A(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	SWAPr(cpu, A);

	return 8;
}

u8 InstructionRotateShift::SRL_B(CPU& cpu)
{
	u8& B = (*mRegistries)[Reg::B];
	SRLr(cpu, B);

	return 8;
}

u8 InstructionRotateShift::SRL_C(CPU& cpu)
{
	u8& C = (*mRegistries)[Reg::C];
	SRLr(cpu, C);

	return 8;
}

u8 InstructionRotateShift::SRL_D(CPU& cpu)
{
	u8& D = (*mRegistries)[Reg::D];
	SRLr(cpu, D);

	return 8;
}

u8 InstructionRotateShift::SRL_E(CPU& cpu)
{
	u8& E = (*mRegistries)[Reg::E];
	SRLr(cpu, E);

	return 8;
}

u8 InstructionRotateShift::SRL_H(CPU& cpu)
{
	u8& H = (*mRegistries)[Reg::H];
	SRLr(cpu, H);

	return 8;
}

u8 InstructionRotateShift::SRL_L(CPU& cpu)
{
	u8& L = (*mRegistries)[Reg::L];
	SRLr(cpu, L);

	return 8;
}

u8 InstructionRotateShift::SRL_pHLq(CPU& cpu)
{
	u8& data = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	SRLr(cpu, data);

	return 16;
}

u8 InstructionRotateShift::SRL_A(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	SRLr(cpu, A);

	return 8;
}



void InstructionRotateShift::RLCr(CPU& cpu, u8& registry)
{
	setCFlag(cpu, BIT(registry, 7));

	registry = (registry << 1) | (registry >> 7);

	setZFlag(cpu, registry == 0);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::RRCr(CPU& cpu, u8& registry)
{
	setCFlag(cpu, BIT(registry, 0));

	registry = (registry >> 1) | (registry << 7);

	setZFlag(cpu, registry == 0);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::RLr(CPU& cpu, u8& registry)
{
	u8 carry = mFlags->flags.C;

	setCFlag(cpu, BIT(registry, 7));

	registry = (registry << 1) | carry;

	setZFlag(cpu, registry == 0);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::RRr(CPU& cpu, u8& registry)
{
	u8 carry = mFlags->flags.C;

	setCFlag(cpu, BIT(registry, 0));

	registry = (registry >> 1) | (carry << 7);

	setZFlag(cpu, registry == 0);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::SLAr(CPU& cpu, u8& registry)
{
	setCFlag(cpu, BIT(registry, 7));

	registry = registry << 1;

	setZFlag(cpu, registry == 0);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::SRAr(CPU& cpu, u8& registry)
{
	setCFlag(cpu, BIT(registry, 0));

	registry = (registry >> 1) | (registry & 0x80); // used for keeping a negative value after the shift

	setZFlag(cpu, registry == 0);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}

void InstructionRotateShift::SWAPr(CPU& cpu, u8& registry)
{
	// Exchange low and high nibble (4bits)
	u8 lowNibble = registry & 0x0F;
	u8 highNibble = registry & 0xF0;

	registry = (lowNibble << 4) | (highNibble >> 4);

	setZFlag(cpu, registry == 0);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
	setCFlag(cpu, 0);
}

void InstructionRotateShift::SRLr(CPU& cpu, u8& registry)
{
	// Right shift logical (bit 7 = 0)
	setCFlag(cpu, BIT(registry, 0));

	registry = registry >> 1;

	setZFlag(cpu, registry == 0);
	setHFlag(cpu, 0);
	setNFlag(cpu, 0);
}


