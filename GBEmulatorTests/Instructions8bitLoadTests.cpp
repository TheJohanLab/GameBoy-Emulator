#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"
#include "..\PPU\PPU.h"
#include "..\Utils\Utils.h"

#define TEST_LD_pRRq_A(reg, opcode) \
TEST_METHOD(LD_p##reg##q_A) \
{ \
    cpu->getRegistriesRef().getRegistriesRef()[Reg::A].get() = 0x0F; \
	u16& reg = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::##reg##].get();\
	reg = 0xC002;\
	bus->write(0xC002, 0x00);\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0F), bus->read(reg));\
}

#define TEST_LDI_pHLq_A(opcode) \
TEST_METHOD(LDI_pHLq_A) \
{ \
    cpu->getRegistriesRef().getRegistriesRef()[Reg::A].get() = 0x0A; \
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL].get();\
	HL = 0xC002;\
	bus->write(0xC002, 0x00);\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0A), bus->read(HL-1));\
	Assert::AreEqual(static_cast<u16>(0xC002+1), HL);\
}

#define TEST_LDD_pHLq_A(opcode) \
TEST_METHOD(LDD_pHLq_A) \
{ \
    cpu->getRegistriesRef().getRegistriesRef()[Reg::A].get() = 0x0A; \
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL].get();\
	HL = 0xC002;\
	bus->write(0xC002, 0x00);\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0A), bus->read(HL+1));\
	Assert::AreEqual(static_cast<u16>(0xC002-1), HL);\
}

#define TEST_LD_R_pHLq(reg, opcode) \
TEST_METHOD(LD_##reg##_pHLq) \
{ \
	bus->write(0xC000, 0x0A);\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
    u8& ##reg## = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg##].get();\
	##reg## = 0x00;\
	HL = 0xC000;\
	u8 data = bus->read(HL);\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0A), ##reg##);\
}

#define TEST_LD_pHLq_R(reg, opcode) \
TEST_METHOD(LD_pHLq_##reg##) \
{ \
	cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg##].get() = 0x0A;\
	bus->write(0xC000, 0x00);\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	HL = 0xC000;\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0A), bus->read(HL));\
}

#define TEST_LD_pHLq_H(opcode) \
TEST_METHOD(LD_pHLq_H) \
{ \
	bus->write(0xC123, 0x00);\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	HL = 0xC123;\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0xC1), bus->read(HL));\
}

#define TEST_LD_pHLq_L(opcode) \
TEST_METHOD(LD_pHLq_L) \
{ \
	bus->write(0xC123, 0x00);\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	HL = 0xC123;\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x23), bus->read(HL));\
}

#define TEST_LD_R_d8(reg, opcode) \
TEST_METHOD(LD_##reg##_d8) \
{ \
	u8& ##reg## = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg##].get();\
	##reg## = 0x00;\
	\
	u16& PC = cpu->getRegistriesRef().getPCRef();\
	PC = 0xC000;\
	bus->write(0xC001, 0x0A);\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0A), ##reg##);\
}

#define TEST_LD_A_pRRq(doubleReg, opcode) \
TEST_METHOD(LD_A_p##doubleReg##) \
{ \
	u8& A = cpu->getRegistriesRef().getRegistriesRef()[Reg::A].get();\
	A = 0x00;\
	\
	u16& ##doubleReg## = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::##doubleReg##].get();\
	##doubleReg## = 0xC000;\
	bus->write(0xC000, 0x0A);\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0A), A);\
}

#define TEST_LDI_A_pHLq(doubleReg, opcode) \
TEST_METHOD(LDI_A_p##doubleReg##) \
{ \
	u8& A = cpu->getRegistriesRef().getRegistriesRef()[Reg::A].get();\
	A = 0x00;\
	\
	u16& ##doubleReg## = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::##doubleReg##].get();\
	##doubleReg## = 0xC000;\
	bus->write(0xC000, 0x0A);\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0A), A);\
	Assert::AreEqual(static_cast<u16>(0xC001), ##doubleReg##);\
}

#define TEST_LDD_A_pHLq(doubleReg, opcode) \
TEST_METHOD(LDD_A_p##doubleReg##) \
{ \
	u8& A = cpu->getRegistriesRef().getRegistriesRef()[Reg::A].get();\
	A = 0x00;\
	\
	u16& ##doubleReg## = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::##doubleReg##].get();\
	##doubleReg## = 0xC001;\
	bus->write(0xC001, 0x0A);\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0A), A);\
	Assert::AreEqual(static_cast<u16>(0xC000), ##doubleReg##);\
}

#define TEST_LD_pHLq_d8(doubleReg, opcode) \
TEST_METHOD(LD_pHLq_d8) \
{ \
	bus->write(0xC000, 0x00);\
	cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::##doubleReg##].get() = 0xC000;\
	\
	u16& PC = cpu->getRegistriesRef().getPCRef();\
	PC = 0xC000;\
	bus->write(0xC001, 0x0A);\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0A), bus->read(0xC000));\
}

#define TEST_LD_R_R(regDst, regSrc, opcode) \
TEST_METHOD(LD_##regDst##_##regSrc##) \
{ \
	u8& dst = cpu->getRegistriesRef().getRegistriesRef()[Reg::##regDst##].get();\
	u8& src = cpu->getRegistriesRef().getRegistriesRef()[Reg::##regSrc##].get();\
	\
	dst = 0x00;\
	src = 0x0A;\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0A), dst);\
}

#define TEST_LDH_pn16q_A(opcode) \
TEST_METHOD(LDH_pn16q_A) \
{ \
	cpu->getRegistriesRef().getRegistriesRef()[Reg::A].get() = 0x0A;\
	bus->write(0xFF05, 0x00);\
	\
	u16& PC = cpu->getRegistriesRef().getPCRef(); \
	PC = 0xC000; \
	bus->write(0xC001, 0x05); \
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0A), bus->read(0xFF05));\
}

#define TEST_LD_pCq_A(opcode) \
TEST_METHOD(LD_pCq_A) \
{ \
	cpu->getRegistriesRef().getRegistriesRef()[Reg::A].get() = 0x0A;\
	cpu->getRegistriesRef().getRegistriesRef()[Reg::C].get() = 0x05;\
	bus->write(0xFF05, 0x00);\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0A), bus->read(0xFF05));\
}


#define TEST_LD_pn16q_A(opcode) \
TEST_METHOD(LD_pn16q_A) \
{ \
	cpu->getRegistriesRef().getRegistriesRef()[Reg::A].get() = 0x0A;\
	bus->write(0xFF05, 0x00);\
	\
	u16& PC = cpu->getRegistriesRef().getPCRef(); \
	PC = 0xC000; \
	bus->write(0xC001, 0x05); \
	bus->write(0xC002, 0xFF); \
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0A), bus->read(0xFF05));\
}

#define TEST_LDH_A_pn16q(opcode) \
TEST_METHOD(LDH_A_pn16q) \
{ \
	u8& A = cpu->getRegistriesRef().getRegistriesRef()[Reg::A].get();\
	A = 0x00;\
	bus->write(0xFF05, 0x0A);\
	\
	u16& PC = cpu->getRegistriesRef().getPCRef(); \
	PC = 0xC000; \
	bus->write(0xC001, 0x05); \
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0A), A);\
}

#define TEST_LDH_A_pCq(opcode) \
TEST_METHOD(LDH_A_pCq) \
{ \
	u8& A = cpu->getRegistriesRef().getRegistriesRef()[Reg::A].get();\
	A = 0x00;\
	bus->write(0xFF05, 0x0A);\
	cpu->getRegistriesRef().getRegistriesRef()[Reg::C].get() = 0x05;\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0A), A);\
}

#define TEST_LD_A_pn16q(opcode) \
TEST_METHOD(LD_A_pn16q) \
{ \
	u8& A = cpu->getRegistriesRef().getRegistriesRef()[Reg::A].get();\
	A = 0x00;\
	bus->write(0xFF05, 0x0A);\
	\
	u16& PC = cpu->getRegistriesRef().getPCRef(); \
	PC = 0xC000; \
	bus->write(0xC001, 0x05); \
	bus->write(0xC002, 0xFF); \
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0A), A);\
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{

	TEST_CLASS(I8BitLoadTests)
	{
	private:
		static std::shared_ptr <Memory> memory;
		static std::shared_ptr <Cartridge> cartridge;
		static std::shared_ptr <Bus> bus;
		static std::shared_ptr <PPU> ppu;
		static std::shared_ptr<CPU> cpu;

	public:

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			memory = std::make_shared<Memory>();
			cartridge = std::make_shared<Cartridge>();
			bus = std::make_shared<Bus>(memory, cartridge);
			ppu = std::make_shared<PPU>(bus, nullptr);
			cpu = std::make_shared<CPU>(bus, ppu);
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{

		}

		TEST_LD_pRRq_A(BC,	0x02);
		TEST_LD_pRRq_A(DE,	0x12);
		TEST_LDI_pHLq_A(	0x22);
		TEST_LDD_pHLq_A(	0x32);
		TEST_LD_R_pHLq(B,	0x46);
		TEST_LD_R_pHLq(C,	0x4E);
		TEST_LD_R_pHLq(D,	0x56);
		TEST_LD_R_pHLq(E,	0x5E);
		TEST_LD_R_pHLq(H,	0x66);


		TEST_LD_R_pHLq(L,	0x6E);
		TEST_LD_R_pHLq(A,	0x7E);

		TEST_LD_pHLq_R(B, 0x70);
		TEST_LD_pHLq_R(C, 0x71);
		TEST_LD_pHLq_R(D, 0x72);
		TEST_LD_pHLq_R(E, 0x73);
		TEST_LD_pHLq_H(   0x74);
		TEST_LD_pHLq_L(   0x75);
		TEST_LD_pHLq_R(A, 0x77);

		TEST_LD_R_d8(B,	  0x06);
		TEST_LD_R_d8(C,	  0x0E);
		TEST_LD_R_d8(D,	  0x16);
		TEST_LD_R_d8(E,	  0x1E);
		TEST_LD_R_d8(H,	  0x26);
		TEST_LD_R_d8(L,	  0x2E);
		TEST_LD_R_d8(A,	  0x3E);

		TEST_LD_A_pRRq(BC, 0x0A);
		TEST_LD_A_pRRq(DE, 0x1A);
		TEST_LDI_A_pHLq(HL, 0x2A);
		TEST_LDD_A_pHLq(HL, 0x3A);

		TEST_LD_pHLq_d8(HL, 0x36);

		TEST_LD_R_R(B, B, 0x40);
		TEST_LD_R_R(B, C, 0x41);
		TEST_LD_R_R(B, D, 0x42);
		TEST_LD_R_R(B, E, 0x43);
		TEST_LD_R_R(B, H, 0x44);
		TEST_LD_R_R(B, L, 0x45);
		TEST_LD_R_R(B, A, 0x47);

		TEST_LD_R_R(C, B, 0x48);
		TEST_LD_R_R(C, C, 0x49);
		TEST_LD_R_R(C, D, 0x4A);
		TEST_LD_R_R(C, E, 0x4B);
		TEST_LD_R_R(C, H, 0x4C);
		TEST_LD_R_R(C, L, 0x4D);
		TEST_LD_R_R(C, A, 0x4F);

		TEST_LD_R_R(D, B, 0x50);
		TEST_LD_R_R(D, C, 0x51);
		TEST_LD_R_R(D, D, 0x52);
		TEST_LD_R_R(D, E, 0x53);
		TEST_LD_R_R(D, H, 0x54);
		TEST_LD_R_R(D, L, 0x55);
		TEST_LD_R_R(D, A, 0x57);

		TEST_LD_R_R(E, B, 0x58);
		TEST_LD_R_R(E, C, 0x59);
		TEST_LD_R_R(E, D, 0x5A);
		TEST_LD_R_R(E, E, 0x5B);
		TEST_LD_R_R(E, H, 0x5C);
		TEST_LD_R_R(E, L, 0x5D);
		TEST_LD_R_R(E, A, 0x5F);

		TEST_LD_R_R(H, B, 0x60);
		TEST_LD_R_R(H, C, 0x61);
		TEST_LD_R_R(H, D, 0x62);
		TEST_LD_R_R(H, E, 0x63);
		TEST_LD_R_R(H, H, 0x64);
		TEST_LD_R_R(H, L, 0x65);
		TEST_LD_R_R(H, A, 0x67);

		TEST_LD_R_R(L, B, 0x68);
		TEST_LD_R_R(L, C, 0x69);
		TEST_LD_R_R(L, D, 0x6A);
		TEST_LD_R_R(L, E, 0x6B);
		TEST_LD_R_R(L, H, 0x6C);
		TEST_LD_R_R(L, L, 0x6D);
		TEST_LD_R_R(L, A, 0x6F);

		TEST_LD_R_R(A, B, 0x78);
		TEST_LD_R_R(A, C, 0x79);
		TEST_LD_R_R(A, D, 0x7A);
		TEST_LD_R_R(A, E, 0x7B);
		TEST_LD_R_R(A, H, 0x7C);
		TEST_LD_R_R(A, L, 0x7D);
		TEST_LD_R_R(A, A, 0x7F);

		TEST_LDH_pn16q_A( 0xE0);
		TEST_LD_pCq_A(	  0xE2);
		TEST_LD_pn16q_A(  0xEA);
		TEST_LDH_A_pn16q( 0xF0);
		TEST_LDH_A_pCq(   0xF2);
		TEST_LD_A_pn16q(  0xFA);


	};
	
	std::shared_ptr<Memory> I8BitLoadTests::memory = nullptr;
	std::shared_ptr<Cartridge> I8BitLoadTests::cartridge = nullptr;
	std::shared_ptr<Bus> I8BitLoadTests::bus = nullptr;
	std::shared_ptr<CPU> I8BitLoadTests::cpu = nullptr;
	std::shared_ptr<PPU> I8BitLoadTests::ppu = nullptr;
}
