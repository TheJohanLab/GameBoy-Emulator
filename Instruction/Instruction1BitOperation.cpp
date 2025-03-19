#include "pch.h"

#include "Instruction1BitOperation.h"

//Instruction1BitOperation::Instruction1BitOperation(const char* name, u8 (*pInstruction)(CPU & cpu), u8 ClockCycle)
//	:Instruction(name, pInstruction, ClockCycle)
//{
//}

Instruction1BitOperation::Instruction1BitOperation(const char* name, std::function<u8(CPU& cpu)> instruction, Registries& reg, std::shared_ptr<Bus> bus)
	:Instruction(name, instruction, reg, bus)
{
}


u8 Instruction1BitOperation::BIT_0cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];	
	BIT_bcr(B, 0x00, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_0cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	BIT_bcr(C, 0x00, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_0cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	BIT_bcr(D, 0x00, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_0cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	BIT_bcr(E, 0x00, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_0cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	BIT_bcr(H, 0x00, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_0cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	BIT_bcr(L, 0x00, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_0cpHLq(CPU& cpu)
{
	auto HLByte = mBus->read(*mHL);
	BIT_bcr(HLByte, 0x00, cpu);

	return 16;
}

u8 Instruction1BitOperation::BIT_0cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	BIT_bcr(A, 0x00, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_1cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	BIT_bcr(B, 0x01, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_1cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	BIT_bcr(C, 0x01, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_1cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	BIT_bcr(D, 0x01, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_1cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	BIT_bcr(E, 0x01, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_1cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	BIT_bcr(H, 0x01, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_1cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	BIT_bcr(L, 0x01, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_1cpHLq(CPU& cpu)
{
	auto HLByte = mBus->read(*mHL);
	BIT_bcr(HLByte, 0x01, cpu);

	return 16;
}

u8 Instruction1BitOperation::BIT_1cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	BIT_bcr(A, 0x01, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_2cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	BIT_bcr(B, 0x02, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_2cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	BIT_bcr(C, 0x02, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_2cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	BIT_bcr(D, 0x02, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_2cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	BIT_bcr(E, 0x02, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_2cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	BIT_bcr(H, 0x02, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_2cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	BIT_bcr(L, 0x02, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_2cpHLq(CPU& cpu)
{
	auto HLByte = mBus->read(*mHL);
	BIT_bcr(HLByte, 0x02, cpu);

	return 16;
}

u8 Instruction1BitOperation::BIT_2cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	BIT_bcr(A, 0x02, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_3cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	BIT_bcr(B, 0x03, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_3cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	BIT_bcr(C, 0x03, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_3cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	BIT_bcr(D, 0x03, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_3cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	BIT_bcr(E, 0x03, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_3cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	BIT_bcr(H, 0x03, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_3cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	BIT_bcr(L, 0x03, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_3cpHLq(CPU& cpu)
{
	auto HLByte = mBus->read(*mHL);
	BIT_bcr(HLByte, 0x03, cpu);

	return 16;
}

u8 Instruction1BitOperation::BIT_3cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	BIT_bcr(A, 0x03, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_4cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	BIT_bcr(B, 0x04, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_4cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	BIT_bcr(C, 0x04, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_4cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	BIT_bcr(D, 0x04, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_4cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	BIT_bcr(E, 0x04, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_4cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	BIT_bcr(H, 0x04, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_4cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	BIT_bcr(L, 0x04, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_4cpHLq(CPU& cpu)
{
	auto HLByte = mBus->read(*mHL);
	BIT_bcr(HLByte, 0x04, cpu);

	return 16;
}

u8 Instruction1BitOperation::BIT_4cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	BIT_bcr(A, 0x04, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_5cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	BIT_bcr(B, 0x05, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_5cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	BIT_bcr(C, 0x05, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_5cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	BIT_bcr(D, 0x05, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_5cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	BIT_bcr(E, 0x05, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_5cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	BIT_bcr(H, 0x05, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_5cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	BIT_bcr(L, 0x05, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_5cpHLq(CPU& cpu)
{
	auto HLByte = mBus->read(*mHL);
	BIT_bcr(HLByte, 0x05, cpu);

	return 16;
}

u8 Instruction1BitOperation::BIT_5cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	BIT_bcr(A, 0x05, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_6cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	BIT_bcr(B, 0x06, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_6cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	BIT_bcr(C, 0x06, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_6cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	BIT_bcr(D, 0x06, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_6cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	BIT_bcr(E, 0x06, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_6cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	BIT_bcr(H, 0x06, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_6cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	BIT_bcr(L, 0x06, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_6cpHLq(CPU& cpu)
{
	auto HLByte = mBus->read(*mHL);
	BIT_bcr(HLByte, 0x06, cpu);

	return 16;
}

u8 Instruction1BitOperation::BIT_6cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	BIT_bcr(A, 0x06, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_7cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	BIT_bcr(B, 0x07, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_7cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	BIT_bcr(C, 0x07, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_7cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	BIT_bcr(D, 0x07, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_7cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	BIT_bcr(E, 0x07, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_7cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	BIT_bcr(H, 0x07, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_7cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	BIT_bcr(L, 0x07, cpu);

	return 8;
}

u8 Instruction1BitOperation::BIT_7cpHLq(CPU& cpu)
{
	auto HLByte = mBus->read(*mHL);
	BIT_bcr(HLByte, 0x07, cpu);

	return 16;
}

u8 Instruction1BitOperation::BIT_7cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	BIT_bcr(A, 0x07, cpu);

	return 8;
}

// Instructions reset bit
// TODO : refactor ?
u8 Instruction1BitOperation::RES_0cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	RES_bcr(B, 0x00);

	return 8;
}

u8 Instruction1BitOperation::RES_0cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::B];
	RES_bcr(C, 0x00);

	return 8;
}

u8 Instruction1BitOperation::RES_0cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	RES_bcr(D, 0x00);

	return 8;
}

u8 Instruction1BitOperation::RES_0cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	RES_bcr(E, 0x00);

	return 8;
}

u8 Instruction1BitOperation::RES_0cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	RES_bcr(H, 0x00);

	return 8;
}

u8 Instruction1BitOperation::RES_0cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	RES_bcr(L, 0x00);

	return 8;
}

u8 Instruction1BitOperation::RES_0cpHLq(CPU& cpu)
{
	auto& data = mBus->read(*mHL);
	RES_bcpHLq(data, 0x00, cpu);

	return 16;
}

u8 Instruction1BitOperation::RES_0cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	RES_bcr(A, 0x00);

	return 8;
}

u8 Instruction1BitOperation::RES_1cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	RES_bcr(B, 0x01);

	return 8;
}

u8 Instruction1BitOperation::RES_1cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	RES_bcr(C, 0x01);

	return 8;
}

u8 Instruction1BitOperation::RES_1cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	RES_bcr(D, 0x01);

	return 8;
}

u8 Instruction1BitOperation::RES_1cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	RES_bcr(E, 0x01);

	return 8;
}

u8 Instruction1BitOperation::RES_1cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	RES_bcr(H, 0x01);

	return 8;
}

u8 Instruction1BitOperation::RES_1cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	RES_bcr(L, 0x01);

	return 8;
}

u8 Instruction1BitOperation::RES_1cpHLq(CPU& cpu)
{
	auto& data = mBus->read(*mHL);
	RES_bcpHLq(data, 0x01, cpu);

	return 16;
}

u8 Instruction1BitOperation::RES_1cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	RES_bcr(A, 0x01);

	return 8;
}

u8 Instruction1BitOperation::RES_2cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	RES_bcr(B, 0x02);

	return 8;
}

u8 Instruction1BitOperation::RES_2cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	RES_bcr(C, 0x02);

	return 8;
}

u8 Instruction1BitOperation::RES_2cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	RES_bcr(D, 0x02);

	return 8;
}

u8 Instruction1BitOperation::RES_2cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	RES_bcr(E, 0x02);

	return 8;
}

u8 Instruction1BitOperation::RES_2cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	RES_bcr(H, 0x02);

	return 8;
}

u8 Instruction1BitOperation::RES_2cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	RES_bcr(L, 0x02);

	return 8;
}

u8 Instruction1BitOperation::RES_2cpHLq(CPU& cpu)
{
	auto& data = mBus->read(*mHL);
	RES_bcpHLq(data, 0x02, cpu);

	return 16;
}

u8 Instruction1BitOperation::RES_2cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	RES_bcr(A, 0x02);

	return 8;
}

u8 Instruction1BitOperation::RES_3cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	RES_bcr(B, 0x03);

	return 8;
}

u8 Instruction1BitOperation::RES_3cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	RES_bcr(C, 0x03);

	return 8;
}

u8 Instruction1BitOperation::RES_3cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	RES_bcr(D, 0x03);

	return 8;
}

u8 Instruction1BitOperation::RES_3cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	RES_bcr(E, 0x03);

	return 8;
}

u8 Instruction1BitOperation::RES_3cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	RES_bcr(H, 0x03);

	return 8;
}

u8 Instruction1BitOperation::RES_3cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	RES_bcr(L, 0x03);

	return 8;
}

u8 Instruction1BitOperation::RES_3cpHLq(CPU& cpu)
{
	auto& data = mBus->read(*mHL);
	RES_bcpHLq(data, 0x03, cpu);

	return 16;
}

u8 Instruction1BitOperation::RES_3cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	RES_bcr(A, 0x03);

	return 8;
}

u8 Instruction1BitOperation::RES_4cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	RES_bcr(B, 0x04);

	return 8;
}

u8 Instruction1BitOperation::RES_4cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	RES_bcr(C, 0x04);

	return 8;
}

u8 Instruction1BitOperation::RES_4cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	RES_bcr(D, 0x04);

	return 8;
}

u8 Instruction1BitOperation::RES_4cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	RES_bcr(E, 0x04);

	return 8;
}

u8 Instruction1BitOperation::RES_4cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	RES_bcr(H, 0x04);

	return 8;
}

u8 Instruction1BitOperation::RES_4cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	RES_bcr(L, 0x04);

	return 8;
}

u8 Instruction1BitOperation::RES_4cpHLq(CPU& cpu)
{
	auto& data = mBus->read(*mHL);
	RES_bcpHLq(data, 0x04, cpu);

	return 16;
}

u8 Instruction1BitOperation::RES_4cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	RES_bcr(A, 0x04);

	return 8;
}

u8 Instruction1BitOperation::RES_5cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	RES_bcr(B, 0x05);

	return 8;
}

u8 Instruction1BitOperation::RES_5cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	RES_bcr(C, 0x05);

	return 8;
}

u8 Instruction1BitOperation::RES_5cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	RES_bcr(D, 0x05);

	return 8;
}

u8 Instruction1BitOperation::RES_5cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	RES_bcr(E, 0x05);

	return 8;
}

u8 Instruction1BitOperation::RES_5cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	RES_bcr(H, 0x05);

	return 8;
}

u8 Instruction1BitOperation::RES_5cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	RES_bcr(L, 0x05);

	return 8;
}

u8 Instruction1BitOperation::RES_5cpHLq(CPU& cpu)
{
	auto& data = mBus->read(*mHL);
	RES_bcpHLq(data, 0x05, cpu);

	return 16;
}

u8 Instruction1BitOperation::RES_5cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	RES_bcr(A, 0x05);

	return 8;
}

u8 Instruction1BitOperation::RES_6cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	RES_bcr(B, 0x06);

	return 8;
}

u8 Instruction1BitOperation::RES_6cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	RES_bcr(C, 0x06);

	return 8;
}

u8 Instruction1BitOperation::RES_6cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	RES_bcr(D, 0x06);

	return 8;
}

u8 Instruction1BitOperation::RES_6cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	RES_bcr(E, 0x06);

	return 8;
}

u8 Instruction1BitOperation::RES_6cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	RES_bcr(H, 0x06);

	return 8;
}

u8 Instruction1BitOperation::RES_6cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	RES_bcr(L, 0x06);

	return 8;
}

u8 Instruction1BitOperation::RES_6cpHLq(CPU& cpu)
{
	auto& data = mBus->read(*mHL);
	RES_bcpHLq(data, 0x06, cpu);

	return 16;
}

u8 Instruction1BitOperation::RES_6cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	RES_bcr(A, 0x06);

	return 8;
}

u8 Instruction1BitOperation::RES_7cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	RES_bcr(B, 0x07);

	return 8;
}

u8 Instruction1BitOperation::RES_7cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	RES_bcr(C, 0x07);

	return 8;
}

u8 Instruction1BitOperation::RES_7cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	RES_bcr(D, 0x07);

	return 8;
}

u8 Instruction1BitOperation::RES_7cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	RES_bcr(E, 0x07);

	return 8;
}

u8 Instruction1BitOperation::RES_7cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	RES_bcr(H, 0x07);

	return 8;
}

u8 Instruction1BitOperation::RES_7cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	RES_bcr(L, 0x07);

	return 8;
}

u8 Instruction1BitOperation::RES_7cpHLq(CPU& cpu)
{
	auto& data = mBus->read(*mHL);
	RES_bcpHLq(data, 0x07, cpu);

	return 16;
}

u8 Instruction1BitOperation::RES_7cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	RES_bcr(A, 0x07);

	return 8;
}


u8 Instruction1BitOperation::SET_0cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	SET_bcr(B, 0x00);

	return 8;
}

u8 Instruction1BitOperation::SET_0cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	SET_bcr(C, 0x00);

	return 8;
}

u8 Instruction1BitOperation::SET_0cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	SET_bcr(D, 0x00);

	return 8;
}

u8 Instruction1BitOperation::SET_0cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	SET_bcr(E, 0x00);

	return 8;
}

u8 Instruction1BitOperation::SET_0cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	SET_bcr(H, 0x00);

	return 8;
}

u8 Instruction1BitOperation::SET_0cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	SET_bcr(L, 0x00);

	return 8;
}

u8 Instruction1BitOperation::SET_0cpHLq(CPU& cpu)
{
	u8& data = mBus->read(*mHL);
	SET_bcpHLq(data, 0x00, cpu);

	return 16;
}

u8 Instruction1BitOperation::SET_0cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	SET_bcr(A, 0x00);

	return 8;
}

u8 Instruction1BitOperation::SET_1cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	SET_bcr(B, 0x01);

	return 8;
}

u8 Instruction1BitOperation::SET_1cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	SET_bcr(C, 0x01);

	return 8;
}

u8 Instruction1BitOperation::SET_1cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	SET_bcr(D, 0x01);

	return 8;
}

u8 Instruction1BitOperation::SET_1cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	SET_bcr(E, 0x01);

	return 8;
}

u8 Instruction1BitOperation::SET_1cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	SET_bcr(H, 0x01);

	return 8;
}

u8 Instruction1BitOperation::SET_1cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	SET_bcr(L, 0x01);

	return 8;
}

u8 Instruction1BitOperation::SET_1cpHLq(CPU& cpu)
{
	u8& data = mBus->read(*mHL);
	SET_bcpHLq(data, 0x01, cpu);

	return 16;
}

u8 Instruction1BitOperation::SET_1cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	SET_bcr(A, 0x01);

	return 8;
}

u8 Instruction1BitOperation::SET_2cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	SET_bcr(B, 0x02);

	return 8;
}

u8 Instruction1BitOperation::SET_2cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	SET_bcr(C, 0x02);

	return 8;
}

u8 Instruction1BitOperation::SET_2cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	SET_bcr(D, 0x02);

	return 8;
}

u8 Instruction1BitOperation::SET_2cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	SET_bcr(E, 0x02);

	return 8;
}

u8 Instruction1BitOperation::SET_2cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	SET_bcr(H, 0x02);

	return 8;
}

u8 Instruction1BitOperation::SET_2cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	SET_bcr(L, 0x02);

	return 8;
}

u8 Instruction1BitOperation::SET_2cpHLq(CPU& cpu)
{
	u8& data = mBus->read(*mHL);
	SET_bcpHLq(data, 0x02, cpu);

	return 16;
}

u8 Instruction1BitOperation::SET_2cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	SET_bcr(A, 0x02);

	return 8;
}

u8 Instruction1BitOperation::SET_3cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	SET_bcr(B, 0x03);

	return 8;
}

u8 Instruction1BitOperation::SET_3cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	SET_bcr(C, 0x03);

	return 8;
}

u8 Instruction1BitOperation::SET_3cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	SET_bcr(D, 0x03);

	return 8;
}

u8 Instruction1BitOperation::SET_3cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	SET_bcr(E, 0x03);

	return 8;
}

u8 Instruction1BitOperation::SET_3cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	SET_bcr(H, 0x03);

	return 8;
}

u8 Instruction1BitOperation::SET_3cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	SET_bcr(L, 0x03);

	return 8;
}

u8 Instruction1BitOperation::SET_3cpHLq(CPU& cpu)
{
	u8& data = mBus->read(*mHL);
	SET_bcpHLq(data, 0x03, cpu);

	return 16;
}

u8 Instruction1BitOperation::SET_3cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	SET_bcr(A, 0x03);

	return 8;
}

u8 Instruction1BitOperation::SET_4cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	SET_bcr(B, 0x04);

	return 8;
}

u8 Instruction1BitOperation::SET_4cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	SET_bcr(C, 0x04);

	return 8;
}

u8 Instruction1BitOperation::SET_4cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	SET_bcr(D, 0x04);

	return 8;
}

u8 Instruction1BitOperation::SET_4cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	SET_bcr(E, 0x04);

	return 8;
}

u8 Instruction1BitOperation::SET_4cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	SET_bcr(H, 0x04);

	return 8;
}

u8 Instruction1BitOperation::SET_4cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	SET_bcr(L, 0x04);

	return 8;
}

u8 Instruction1BitOperation::SET_4cpHLq(CPU& cpu)
{
	u8& data = mBus->read(*mHL);
	SET_bcpHLq(data, 0x04, cpu);

	return 16;
}

u8 Instruction1BitOperation::SET_4cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	SET_bcr(A, 0x04);

	return 8;
}

u8 Instruction1BitOperation::SET_5cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	SET_bcr(B, 0x05);

	return 8;
}

u8 Instruction1BitOperation::SET_5cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	SET_bcr(C, 0x05);

	return 8;
}

u8 Instruction1BitOperation::SET_5cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	SET_bcr(D, 0x05);

	return 8;
}

u8 Instruction1BitOperation::SET_5cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	SET_bcr(E, 0x05);

	return 8;
}

u8 Instruction1BitOperation::SET_5cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	SET_bcr(H, 0x05);

	return 8;
}

u8 Instruction1BitOperation::SET_5cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	SET_bcr(L, 0x05);

	return 8;
}

u8 Instruction1BitOperation::SET_5cpHLq(CPU& cpu)
{
	u8& data = mBus->read(*mHL);
	SET_bcpHLq(data, 0x05, cpu);

	return 16;
}

u8 Instruction1BitOperation::SET_5cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	SET_bcr(A, 0x05);

	return 8;
}

u8 Instruction1BitOperation::SET_6cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	SET_bcr(B, 0x06);

	return 8;
}

u8 Instruction1BitOperation::SET_6cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	SET_bcr(C, 0x06);

	return 8;
}

u8 Instruction1BitOperation::SET_6cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	SET_bcr(D, 0x06);

	return 8;
}

u8 Instruction1BitOperation::SET_6cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	SET_bcr(E, 0x06);

	return 8;
}

u8 Instruction1BitOperation::SET_6cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	SET_bcr(H, 0x06);

	return 8;
}

u8 Instruction1BitOperation::SET_6cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	SET_bcr(L, 0x06);

	return 8;
}

u8 Instruction1BitOperation::SET_6cpHLq(CPU& cpu)
{
	u8& data = mBus->read(*mHL);
	SET_bcpHLq(data, 0x06, cpu);

	return 16;
}

u8 Instruction1BitOperation::SET_6cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	SET_bcr(A, 0x06);

	return 8;
}

u8 Instruction1BitOperation::SET_7cB(CPU& cpu)
{
	auto& B = (*mRegistries)[Reg::B];
	SET_bcr(B, 0x07);

	return 8;
}

u8 Instruction1BitOperation::SET_7cC(CPU& cpu)
{
	auto& C = (*mRegistries)[Reg::C];
	SET_bcr(C, 0x07);

	return 8;
}

u8 Instruction1BitOperation::SET_7cD(CPU& cpu)
{
	auto& D = (*mRegistries)[Reg::D];
	SET_bcr(D, 0x07);

	return 8;
}

u8 Instruction1BitOperation::SET_7cE(CPU& cpu)
{
	auto& E = (*mRegistries)[Reg::E];
	SET_bcr(E, 0x07);

	return 8;
}

u8 Instruction1BitOperation::SET_7cH(CPU& cpu)
{
	auto& H = (*mRegistries)[Reg::H];
	SET_bcr(H, 0x07);

	return 8;
}

u8 Instruction1BitOperation::SET_7cL(CPU& cpu)
{
	auto& L = (*mRegistries)[Reg::L];
	SET_bcr(L, 0x07);

	return 8;
}

u8 Instruction1BitOperation::SET_7cpHLq(CPU& cpu)
{
	u8& data = mBus->read(*mHL);
	SET_bcpHLq(data, 0x07, cpu);

	return 16;
}

u8 Instruction1BitOperation::SET_7cA(CPU& cpu)
{
	auto& A = (*mRegistries)[Reg::A];
	SET_bcr(A, 0x07);

	return 8;
}

void Instruction1BitOperation::BIT_bcr(const u8& registry, const u8 bit, CPU& cpu)
{
	setZFlag(cpu, BIT(registry, bit) == 0);
	setHFlag(cpu, 1);
	setNFlag(cpu, 0);
}

void Instruction1BitOperation::RES_bcr(u8& registry, u8 bit)
{
	SET_BIT(registry, bit, 0x00);
}

void Instruction1BitOperation::RES_bcpHLq(u8& registry, u8 bit, CPU& cpu)
{
	SET_BIT(registry, bit, 0x00);
	cpu.writeMemory(*cpu.getCombinedRegistries("HL"), registry);
}

void Instruction1BitOperation::SET_bcr(u8& registry, u8 bit)
{
	SET_BIT(registry, bit, 0x01);
}

void Instruction1BitOperation::SET_bcpHLq(u8& registry, u8 bit, CPU& cpu)
{
	SET_BIT(registry, bit, 0x01);
	cpu.writeMemory(*cpu.getCombinedRegistries("HL"), registry);
}