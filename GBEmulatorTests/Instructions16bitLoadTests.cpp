#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"
#include "..\PPU\PPU.h"
#include "..\Utils\Utils.h"


#define TEST_LD_RR_d16(highReg, lowReg, opcode) \
TEST_METHOD(LD_##highReg##lowReg##_d16) \
{ \
	u16& doubleReg = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::##highReg##lowReg].get();\
	u8& highReg = cpu->getRegistriesRef().getRegistriesRef()[Reg::##highReg].get(); \
	u8& lowReg = cpu->getRegistriesRef().getRegistriesRef()[Reg::##lowReg].get(); \
	u16& PC = cpu->getRegistriesRef().getPCRef();\
	\
	PC = 0xC000;\
	doubleReg = 0x0000;\
	bus->write(0xC001, 0x34);\
	bus->write(0xC002, 0x12);\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u16>(0x1234), doubleReg);\
	Assert::AreEqual(static_cast<u8>(0x12), highReg);\
	Assert::AreEqual(static_cast<u8>(0x34), lowReg);\
}

#define TEST_LD_SP_d16(opcode) \
TEST_METHOD(LD_SP_d16) \
{ \
	u16& SP = cpu->getRegistriesRef().getSPRef();\
	u16& PC = cpu->getRegistriesRef().getPCRef();\
	\
	PC = 0xC000;\
	SP = 0x0000;\
	bus->write(0xC001, 0x34);\
	bus->write(0xC002, 0x12);\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u16>(0x1234), SP);\
}


#define TEST_LD_pa16q_SP(opcode) \
TEST_METHOD(LD_pa16q_SP) \
{ \
	u16& SP = cpu->getRegistriesRef().getSPRef();\
	u16& PC = cpu->getRegistriesRef().getPCRef();\
	\
	PC = 0xC000;\
	SP = 0x3456;\
	bus->write(0xC001, 0x12);\
	bus->write(0xC002, 0xC0);\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x56), bus->read(0xC012));\
	Assert::AreEqual(static_cast<u8>(0x34), bus->read(0xC013));\
}

#define TEST_POP_RR(doubleReg, opcode)\
TEST_METHOD(POP_##doubleReg)\
{\
	u16& SP = cpu->getRegistriesRef().getSPRef(); \
	u16& doubleReg = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::##doubleReg].get(); \
	\
	doubleReg = 0x0000;\
	SP = 0xC000;\
	bus->write(0xC000, 0x34);\
	bus->write(0xC001, 0x12);\
	doubleReg = 0x0000;\
	\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u16>(0xC002), SP);\
	Assert::AreEqual(static_cast<u16>(0x1234), doubleReg);\
}

#define TEST_PUSH_RR(doubleReg, opcode)\
TEST_METHOD(PUSH_##doubleReg)\
{\
	u16& SP = cpu->getRegistriesRef().getSPRef(); \
	u16& doubleReg = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::##doubleReg].get(); \
	doubleReg = 0x5678;\
	\
	SP = 0xFFFE;\
	bus->write(0xC000, 0x00); \
	bus->write(0xC001, 0x00); \
	\
	cpu->executeOpcode(opcode); \
	\
	Assert::AreEqual(static_cast<u16>(0xFFFC), SP); \
	Assert::AreEqual(static_cast<u8>(0x78), bus->read(SP)); \
	Assert::AreEqual(static_cast<u8>(0x56), bus->read(SP + 1)); \
}


#define TEST_POP_AF(opcode)\
TEST_METHOD(POP_AF)\
{\
	u16& SP = cpu->getRegistriesRef().getSPRef(); \
	u16& AF = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::AF].get(); \
	u8& A = cpu->getRegistriesRef().getRegistriesRef()[Reg::A].get(); \
	flags& F = cpu->getRegistriesRef().getFlagsRef(); \
	\
	AF = 0x0000;\
	SP = 0xC000;\
	bus->write(0xC000, 0xF0); \
	bus->write(0xC001, 0x34);  \
	\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u16>(0xC002), SP);\
	Assert::AreEqual(static_cast<u16>(0x34F0), AF);\
	Assert::AreEqual(static_cast<u8>(0x34), A);\
	Assert::AreEqual(static_cast<u8>(0xF0), F.F);\
	Assert::AreEqual(static_cast<u8>(0x01), F.flags.C);\
	Assert::AreEqual(static_cast<u8>(0x01), F.flags.H);\
	Assert::AreEqual(static_cast<u8>(0x01), F.flags.N);\
	Assert::AreEqual(static_cast<u8>(0x01), F.flags.Z);\
}


#define TEST_LDHL_SP_e8(opcode) \
TEST_METHOD(LDHL_SP_e8) \
{ \
	u16& SP = cpu->getRegistriesRef().getSPRef(); \
	u16& PC = cpu->getRegistriesRef().getPCRef(); \
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL]; \
	flags& flagsRef = cpu->getRegistriesRef().getFlagsRef(); \
	\
	HL = 0x00; \
	PC = 0xC000; \
	SP = 0x0000; \
	flagsRef.F = 0x00; \
	bus->write(0xC001, 0x12); \
	\
	cpu->executeOpcode(0xF8); \
	Assert::AreEqual(static_cast<u16>(0x0012), HL); \
	Assert::AreEqual(static_cast<u16>(0x0000), SP); \
	Assert::AreEqual(static_cast <u8>(0x00), flagsRef.flags.Z); \
	Assert::AreEqual(static_cast <u8>(0x00), flagsRef.flags.N); \
	Assert::AreEqual(static_cast <u8>(0x00), flagsRef.flags.H); \
	Assert::AreEqual(static_cast <u8>(0x00), flagsRef.flags.C); \
	\
	HL = 0x00; \
	PC = 0xC000; \
	SP = 0x0001; \
	flagsRef.F = 0x00; \
	bus->write(0xC001, 0x01); \
	\
	cpu->executeOpcode(0xF8); \
	Assert::AreEqual(static_cast<u16>(0x0002), HL); \
	Assert::AreEqual(static_cast <u8>(0x00), flagsRef.flags.Z); \
	Assert::AreEqual(static_cast <u8>(0x00), flagsRef.flags.N); \
	Assert::AreEqual(static_cast <u8>(0x00), flagsRef.flags.H); \
	Assert::AreEqual(static_cast <u8>(0x00), flagsRef.flags.C); \
	\
	HL = 0x00; \
	PC = 0xC000; \
	SP = 0x0009; \
	flagsRef.F = 0x00; \
	bus->write(0xC001, 0xF8); \
	\
	cpu->executeOpcode(0xF8); \
	Assert::AreEqual(static_cast<u16>(0x0001), HL); \
	Assert::AreEqual(static_cast <u8>(0x00), flagsRef.flags.Z); \
	Assert::AreEqual(static_cast <u8>(0x00), flagsRef.flags.N); \
	Assert::AreEqual(static_cast <u8>(0x01), flagsRef.flags.H); \
	Assert::AreEqual(static_cast <u8>(0x01), flagsRef.flags.C); \
	\
	HL = 0x00; \
	PC = 0xC000; \
	SP = 0x0001; \
	flagsRef.F = 0x00; \
	bus->write(0xC001, 0x0F); \
	\
	cpu->executeOpcode(0xF8); \
	Assert::AreEqual(static_cast<u16>(0x0010), HL); \
	Assert::AreEqual(static_cast <u8>(0x00), flagsRef.flags.Z); \
	Assert::AreEqual(static_cast <u8>(0x00), flagsRef.flags.N); \
	Assert::AreEqual(static_cast <u8>(0x01), flagsRef.flags.H); \
	Assert::AreEqual(static_cast <u8>(0x00), flagsRef.flags.C); \
	\
	HL = 0x00; \
	PC = 0xC000; \
	SP = 0x0002; \
	flagsRef.F = 0x00; \
	bus->write(0xC001, 0xFF); \
	\
	cpu->executeOpcode(0xF8); \
	Assert::AreEqual(static_cast<u16>(0x0001), HL); \
	Assert::AreEqual(static_cast <u8>(0x00), flagsRef.flags.Z); \
	Assert::AreEqual(static_cast <u8>(0x00), flagsRef.flags.N); \
	Assert::AreEqual(static_cast <u8>(0x01), flagsRef.flags.H);	\
	Assert::AreEqual(static_cast <u8>(0x01), flagsRef.flags.C);	\
	\
}

#define TEST_LD_SP_HL(opcode) \
TEST_METHOD(LD_SP_HL) \
{ \
	u16& SP = cpu->getRegistriesRef().getSPRef();\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL].get(); \
	\
	SP = 0x0000;\
	HL = 0x1234;\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u16>(0x1234), SP);\
}



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{

	TEST_CLASS(I16BitLoadTests)
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

		TEST_LD_RR_d16(B, C, 0x01);
		TEST_LD_RR_d16(D, E, 0x11);
		TEST_LD_RR_d16(H, L, 0x21);
		TEST_LD_SP_d16(      0x31);
		TEST_LD_pa16q_SP(    0x08);


		TEST_POP_RR( BC, 0xC1);
		TEST_PUSH_RR(BC, 0xC5);

		TEST_POP_RR( DE, 0xD1);
		TEST_PUSH_RR(DE, 0xD5);

		TEST_POP_RR( HL, 0xE1);
		TEST_PUSH_RR(HL, 0xE5);

		TEST_POP_AF(	 0xF1);
		TEST_PUSH_RR(AF, 0xF5);


		TEST_LDHL_SP_e8( 0xF8);

		TEST_LD_SP_HL(	 0xF9);
	};

	std::shared_ptr<Memory> I16BitLoadTests::memory = nullptr;
	std::shared_ptr<Cartridge> I16BitLoadTests::cartridge = nullptr;
	std::shared_ptr<Bus> I16BitLoadTests::bus = nullptr;
	std::shared_ptr<CPU> I16BitLoadTests::cpu = nullptr;
	std::shared_ptr<PPU> I16BitLoadTests::ppu = nullptr;
}
