#include "pch.h"

#include "Instruction8BitLoad.h"



Instruction8BitLoad::Instruction8BitLoad(const char* name, std::function<u8(CPU& cpu)> instruction, Registries& reg, std::shared_ptr<Bus> bus)
	:Instruction(name, instruction, reg, bus)
{
}

u8 Instruction8BitLoad::LD_pBCqcA(CPU& cpu)
{
	//				addr									value
	mBus->write((*mDoubleRegistries)[DoubleReg::BC], (*mRegistries)[Reg::A]);

	return 8;
}

u8 Instruction8BitLoad::LD_Bcd8(CPU& cpu)
{
	u8& B = (*mRegistries)[Reg::B];
	LD_Rcd8(cpu, B);

	return 8;
}

u8 Instruction8BitLoad::LD_AcpBCq(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u16& address = (*mDoubleRegistries)[DoubleReg::BC];
	A = mBus->read(address);

	return 8;
}

u8 Instruction8BitLoad::LD_Ccd8(CPU& cpu)
{
	u8& C = (*mRegistries)[Reg::C];
	LD_Rcd8(cpu, C);

	return 8;
}

u8 Instruction8BitLoad::LD_pDEqcA(CPU& cpu)
{
	//									addr				value
	mBus->write((*mDoubleRegistries)[DoubleReg::DE], (*mRegistries)[Reg::A]);

	return 8;
}

u8 Instruction8BitLoad::LD_Dcd8(CPU& cpu)
{
	u8& D = (*mRegistries)[Reg::D];
	LD_Rcd8(cpu, D);

	return 8;
}

u8 Instruction8BitLoad::LD_AcpDEq(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u16& address = (*mDoubleRegistries)[DoubleReg::DE];
	A = mBus->read(address);

	return 8;
}

u8 Instruction8BitLoad::LD_Ecd8(CPU& cpu)
{
	u8& E = (*mRegistries)[Reg::E];
	LD_Rcd8(cpu, E);

	return 8;
}

u8 Instruction8BitLoad::LDI_pHLqcA(CPU& cpu)
{
	u16& HL = (*mDoubleRegistries)[DoubleReg::HL];
	//			addr		value
	mBus->write(HL, (*mRegistries)[Reg::A]);
	HL++;

	return 8;
}

u8 Instruction8BitLoad::LD_Hcd8(CPU& cpu)
{
	u8& H = (*mRegistries)[Reg::H];
	LD_Rcd8(cpu, H);

	return 8;
}

u8 Instruction8BitLoad::LDI_AcpHLq(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u16& HL = (*mDoubleRegistries)[DoubleReg::HL];
	A = mBus->read(HL);
	HL++;

	return 8;
}

u8 Instruction8BitLoad::LD_Lcd8(CPU& cpu)
{
	u8& L = (*mRegistries)[Reg::L];
	LD_Rcd8(cpu, L);

	return 8;
}

u8 Instruction8BitLoad::LDD_pHLqcA(CPU& cpu)
{
	u16& HL = (*mDoubleRegistries)[DoubleReg::HL];
	//			addr		value
	mBus->write(HL, (*mRegistries)[Reg::A].get());
	HL--;

	return 8;
}

u8 Instruction8BitLoad::LD_pHLqcd8(CPU& cpu)
{
	u16& HL = (*mDoubleRegistries)[DoubleReg::HL];
	(*mPC)++;
	u8 data = cpu.readMemory(*mPC);
	mBus->write(HL, data);

	return 12;
}

u8 Instruction8BitLoad::LDD_AcpHLq(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u16& HL = (*mDoubleRegistries)[DoubleReg::HL];
	A = mBus->read(HL);
	HL--;

	return 8;
}

u8 Instruction8BitLoad::LD_Acd8(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	LD_Rcd8(cpu, A);

	return 8;
}

u8 Instruction8BitLoad::LD_BcB(CPU& cpu)
{
	return 4;
}

u8 Instruction8BitLoad::LD_BcC(CPU& cpu)
{
	u8 C = (*mRegistries)[Reg::C];
	(*mRegistries)[Reg::B].get() = C;

	return 4;
}

u8 Instruction8BitLoad::LD_BcD(CPU& cpu)
{
	u8 D = (*mRegistries)[Reg::D];
	(*mRegistries)[Reg::B].get() = D;

	return 4;
}

u8 Instruction8BitLoad::LD_BcE(CPU& cpu)
{
	u8 E = (*mRegistries)[Reg::E];
	(*mRegistries)[Reg::B].get() = E;

	return 4;
}

u8 Instruction8BitLoad::LD_BcH(CPU& cpu)
{
	u8 H = (*mRegistries)[Reg::H];
	(*mRegistries)[Reg::B].get() = H;

	return 4;
}

u8 Instruction8BitLoad::LD_BcL(CPU& cpu)
{
	u8 L= (*mRegistries)[Reg::L];
	(*mRegistries)[Reg::B].get() = L;

	return 4;
}

u8 Instruction8BitLoad::LD_BcpHLq(CPU& cpu)
{
	u8& B = (*mRegistries)[Reg::B];
	auto value = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	B = value;

	return 8;
}

u8 Instruction8BitLoad::LD_BcA(CPU& cpu)
{
	u8 A = (*mRegistries)[Reg::A];
	(*mRegistries)[Reg::B].get() = A;

	return 4;
}

u8 Instruction8BitLoad::LD_CcB(CPU& cpu)
{
	u8 B = (*mRegistries)[Reg::B];
	(*mRegistries)[Reg::C].get() = B;

	return 4;
}

u8 Instruction8BitLoad::LD_CcC(CPU& cpu)
{
	return 4;
}

u8 Instruction8BitLoad::LD_CcD(CPU& cpu)
{
	u8 D = (*mRegistries)[Reg::D];
	(*mRegistries)[Reg::C].get() = D;

	return 4;
}

u8 Instruction8BitLoad::LD_CcE(CPU& cpu)
{
	u8 E = (*mRegistries)[Reg::E];
	(*mRegistries)[Reg::C].get() = E;

	return 4;
}

u8 Instruction8BitLoad::LD_CcH(CPU& cpu)
{
	u8 H = (*mRegistries)[Reg::H];
	(*mRegistries)[Reg::C].get() = H;

	return 4;
}

u8 Instruction8BitLoad::LD_CcL(CPU& cpu)
{
	u8 L = (*mRegistries)[Reg::L];
	(*mRegistries)[Reg::C].get() = L;

	return 4;
}

u8 Instruction8BitLoad::LD_CcpHLq(CPU& cpu)
{
	u8& C = (*mRegistries)[Reg::C];
	auto value = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	C = value;

	return 8;
}

u8 Instruction8BitLoad::LD_CcA(CPU& cpu)
{
	u8 A = (*mRegistries)[Reg::A];
	(*mRegistries)[Reg::C].get() = A;

	return 4;
}

u8 Instruction8BitLoad::LD_DcB(CPU& cpu)
{
	u8 B = (*mRegistries)[Reg::B];
	(*mRegistries)[Reg::D].get() = B;

	return 4;
}

u8 Instruction8BitLoad::LD_DcC(CPU& cpu)
{
	u8 C = (*mRegistries)[Reg::C];
	(*mRegistries)[Reg::D].get() = C;

	return 4;
}

u8 Instruction8BitLoad::LD_DcD(CPU& cpu)
{
	u8 D = (*mRegistries)[Reg::D];
	(*mRegistries)[Reg::D].get() = D;

	return 4;
}

u8 Instruction8BitLoad::LD_DcE(CPU& cpu)
{
	u8 E = (*mRegistries)[Reg::E];
	(*mRegistries)[Reg::D].get() = E;

	return 4;
}

u8 Instruction8BitLoad::LD_DcH(CPU& cpu)
{
	u8 H = (*mRegistries)[Reg::H];
	(*mRegistries)[Reg::D].get() = H;

	return 4;
}

u8 Instruction8BitLoad::LD_DcL(CPU& cpu)
{
	u8 L = (*mRegistries)[Reg::L];
	(*mRegistries)[Reg::D].get() = L;

	return 4;
}

u8 Instruction8BitLoad::LD_DcpHLq(CPU& cpu)
{
	u8& D = (*mRegistries)[Reg::D];
	auto value = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	D = value;

	return 8;
}

u8 Instruction8BitLoad::LD_DcA(CPU& cpu)
{
	u8 A = (*mRegistries)[Reg::A];
	(*mRegistries)[Reg::D].get() = A;

	return 4;
}

u8 Instruction8BitLoad::LD_EcB(CPU& cpu)
{
	u8 B = (*mRegistries)[Reg::B];
	(*mRegistries)[Reg::E].get() = B;

	return 4;
}

u8 Instruction8BitLoad::LD_EcC(CPU& cpu)
{
	u8 C = (*mRegistries)[Reg::C];
	(*mRegistries)[Reg::E].get() = C;

	return 4;
}

u8 Instruction8BitLoad::LD_EcD(CPU& cpu)
{
	u8 D = (*mRegistries)[Reg::D];
	(*mRegistries)[Reg::E].get() = D;

	return 4;
}

u8 Instruction8BitLoad::LD_EcE(CPU& cpu)
{
	return 4;
}

u8 Instruction8BitLoad::LD_EcH(CPU& cpu)
{
	u8 H = (*mRegistries)[Reg::H];
	(*mRegistries)[Reg::E].get() = H;

	return 4;
}

u8 Instruction8BitLoad::LD_EcL(CPU& cpu)
{
	u8 L = (*mRegistries)[Reg::L];
	(*mRegistries)[Reg::E].get() = L;

	return 4;
}

u8 Instruction8BitLoad::LD_EcpHLq(CPU& cpu)
{
	u8& E = (*mRegistries)[Reg::E];
	auto value = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	E = value;

	return 8;
}

u8 Instruction8BitLoad::LD_EcA(CPU& cpu)
{
	u8 A = (*mRegistries)[Reg::A];
	(*mRegistries)[Reg::E].get() = A;

	return 4;
}

u8 Instruction8BitLoad::LD_HcB(CPU& cpu)
{
	u8 B = (*mRegistries)[Reg::B];
	(*mRegistries)[Reg::H].get() = B;

	return 4;
}

u8 Instruction8BitLoad::LD_HcC(CPU& cpu)
{
	u8 C = (*mRegistries)[Reg::C];
	(*mRegistries)[Reg::H].get() = C;

	return 4;
}

u8 Instruction8BitLoad::LD_HcD(CPU& cpu)
{
	u8 D = (*mRegistries)[Reg::D];
	(*mRegistries)[Reg::H].get() = D;

	return 4;
}

u8 Instruction8BitLoad::LD_HcE(CPU& cpu)
{
	u8 E = (*mRegistries)[Reg::E];
	(*mRegistries)[Reg::H].get() = E;

	return 4;
}

u8 Instruction8BitLoad::LD_HcH(CPU& cpu)
{
	return 4;
}

u8 Instruction8BitLoad::LD_HcL(CPU& cpu)
{
	u8 L = (*mRegistries)[Reg::L];
	(*mRegistries)[Reg::H].get() = L;

	return 4;
}

u8 Instruction8BitLoad::LD_HcpHLq(CPU& cpu)
{
	u8& H = (*mRegistries)[Reg::H];
	auto value = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	H = value;

	return 8;
}

u8 Instruction8BitLoad::LD_HcA(CPU& cpu)
{
	u8 A = (*mRegistries)[Reg::A];
	(*mRegistries)[Reg::H].get() = A;

	return 4;
}

u8 Instruction8BitLoad::LD_LcB(CPU& cpu)
{
	u8 B = (*mRegistries)[Reg::B];
	(*mRegistries)[Reg::L].get() = B;

	return 4;
}

u8 Instruction8BitLoad::LD_LcC(CPU& cpu)
{
	u8 C = (*mRegistries)[Reg::C];
	(*mRegistries)[Reg::L].get() = C;

	return 4;
}

u8 Instruction8BitLoad::LD_LcD(CPU& cpu)
{
	u8 D = (*mRegistries)[Reg::D];
	(*mRegistries)[Reg::L].get() = D;

	return 4;
}

u8 Instruction8BitLoad::LD_LcE(CPU& cpu)
{
	u8 E = (*mRegistries)[Reg::E];
	(*mRegistries)[Reg::L].get() = E;

	return 4;
}

u8 Instruction8BitLoad::LD_LcH(CPU& cpu)
{
	u8 H = (*mRegistries)[Reg::H];
	(*mRegistries)[Reg::L].get() = H;

	return 4;
}

u8 Instruction8BitLoad::LD_LcL(CPU& cpu)
{
	return 4;
}

u8 Instruction8BitLoad::LD_LcpHLq(CPU& cpu)
{
	u8& L = (*mRegistries)[Reg::L];
	auto value = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	L = value;

	return 8;
}

u8 Instruction8BitLoad::LD_LcA(CPU& cpu)
{
	u8 A = (*mRegistries)[Reg::A];
	(*mRegistries)[Reg::L].get() = A;

	return 4;
}

u8 Instruction8BitLoad::LD_pHLqcB(CPU& cpu)
{
	mBus->write((*mDoubleRegistries)[DoubleReg::HL], (*mRegistries)[Reg::B]);

	return 8;
}

u8 Instruction8BitLoad::LD_pHLqcC(CPU& cpu)
{
	mBus->write((*mDoubleRegistries)[DoubleReg::HL], (*mRegistries)[Reg::C]);

	return 8;
}

u8 Instruction8BitLoad::LD_pHLqcD(CPU& cpu)
{
	mBus->write((*mDoubleRegistries)[DoubleReg::HL], (*mRegistries)[Reg::D]);

	return 8;
}

u8 Instruction8BitLoad::LD_pHLqcE(CPU& cpu)
{
	mBus->write((*mDoubleRegistries)[DoubleReg::HL], (*mRegistries)[Reg::E]);

	return 8;
}

u8 Instruction8BitLoad::LD_pHLqcH(CPU& cpu)
{
	mBus->write((*mDoubleRegistries)[DoubleReg::HL], (*mRegistries)[Reg::H]);

	return 8;
}

u8 Instruction8BitLoad::LD_pHLqcL(CPU& cpu)
{
	mBus->write((*mDoubleRegistries)[DoubleReg::HL], (*mRegistries)[Reg::L]);

	return 8;
}

u8 Instruction8BitLoad::LD_pHLqcA(CPU& cpu)
{
	mBus->write((*mDoubleRegistries)[DoubleReg::HL], (*mRegistries)[Reg::A]);

	return 8;
}

u8 Instruction8BitLoad::LD_AcB(CPU& cpu)
{
	u8 B = (*mRegistries)[Reg::B];
	(*mRegistries)[Reg::A].get() = B;

	return 4;
}

u8 Instruction8BitLoad::LD_AcC(CPU& cpu)
{
	u8 C = (*mRegistries)[Reg::C];
	(*mRegistries)[Reg::A].get() = C;

	return 4;
}

u8 Instruction8BitLoad::LD_AcD(CPU& cpu)
{
	u8 D = (*mRegistries)[Reg::D];
	(*mRegistries)[Reg::A].get() = D;

	return 4;
}

u8 Instruction8BitLoad::LD_AcE(CPU& cpu)
{
	u8 E = (*mRegistries)[Reg::E];
	(*mRegistries)[Reg::A].get() = E;

	return 4;
}

u8 Instruction8BitLoad::LD_AcH(CPU& cpu)
{
	u8 H = (*mRegistries)[Reg::H];
	(*mRegistries)[Reg::A].get() = H;

	return 4;
}

u8 Instruction8BitLoad::LD_AcL(CPU& cpu)
{
	u8 L = (*mRegistries)[Reg::L];
	(*mRegistries)[Reg::A].get() = L;

	return 4;
}

u8 Instruction8BitLoad::LD_AcpHLq(CPU& cpu)
{

	u8& A = (*mRegistries)[Reg::A];
	auto value = mBus->read((*mDoubleRegistries)[DoubleReg::HL]);
	A = value;

	return 8;
}

u8 Instruction8BitLoad::LD_AcA(CPU& cpu)
{
	return 4;
}

u8 Instruction8BitLoad::LDH_pa8qcA(CPU& cpu)
{
	u8 addressOffset = readNextOpcode(cpu);
	u8 A = (*mRegistries)[Reg::A];
	mBus->write(0xFF00 + addressOffset, A);

	return 12;
}

u8 Instruction8BitLoad::LD_pCqcA(CPU& cpu)
{
	u8& A = (*mRegistries)[Reg::A];
	u8& C = (*mRegistries)[Reg::C];

	mBus->write(0xFF00 + C, A);

	return 8;
}

u8 Instruction8BitLoad::LD_pa16qcA(CPU& cpu)
{
	u16 address = readNextTwoOpcodes(cpu);

	u8& A = (*mRegistries)[Reg::A];
	mBus->write(address, A);

	return 16;
}

u8 Instruction8BitLoad::LDH_Acpa8q(CPU& cpu)
{
	u8 addressOffset = readNextOpcode(cpu);
	
	u8 data = mBus->read(0xFF00 + addressOffset);
	(*mRegistries)[Reg::A].get() = data;

	return 12;
}

u8 Instruction8BitLoad::LD_AcpCq(CPU& cpu)
{
	u8& C = (*mRegistries)[Reg::C];
	u8 data = mBus->read(0xFF00 + C);
	
	(*mRegistries)[Reg::A].get() = data;

	return 8;
}

u8 Instruction8BitLoad::LD_Acpa16q(CPU& cpu)
{
	u16 address = readNextTwoOpcodes(cpu);

	u8 data = mBus->read(address);
	(*mRegistries)[Reg::A].get() = data;

	return 16;
}


/// ///////////////////////

void Instruction8BitLoad::LD_Rcd8(CPU& cpu, u8& registry)
{
	registry = readNextOpcode(cpu);
}




