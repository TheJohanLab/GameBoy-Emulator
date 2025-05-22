#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"
#include "..\PPU\PPU.h"
#include "..\Utils\Utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


#define TEST_INC_RR(highReg, lowReg, opcode) \
TEST_METHOD(INC_##highReg##lowReg)\
{\
	u16& doubleRegistry = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::##highReg##lowReg];\
	u8& highReg = cpu->getRegistriesRef().getRegistriesRef()[Reg::##highReg]; \
	u8& lowReg = cpu->getRegistriesRef().getRegistriesRef()[Reg::##lowReg]; \
	\
	doubleRegistry = 0x1234;\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u8>(0x12), highReg);\
	Assert::AreEqual(static_cast <u8>(0x35), lowReg);\
	Assert::AreEqual(static_cast <u16>(0x1235), doubleRegistry);\
	\
	doubleRegistry = 0x12FF;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x13), highReg);\
	Assert::AreEqual(static_cast <u8>(0x00), lowReg);\
	Assert::AreEqual(static_cast <u16>(0x1300), doubleRegistry); \
	\
	doubleRegistry = 0xFFFF;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), highReg);\
	Assert::AreEqual(static_cast <u8>(0x00), lowReg);\
	Assert::AreEqual(static_cast <u16>(0x0000), doubleRegistry); \
}

#define TEST_INC_SP(opcode) \
TEST_METHOD(INC_SP)\
{\
	u16& SP = cpu->getRegistriesRef().getSPRef();\
	SP = 0x1234;\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast <u16>(0x1235), SP);\
	\
	SP = 0xFFFF;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast <u16>(0x0000), SP); \
}

#define TEST_DEC_RR(highReg, lowReg, opcode) \
TEST_METHOD(DEC_##highReg##lowReg)\
{\
	u16& doubleRegistry = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::##highReg##lowReg];\
	u8& highReg = cpu->getRegistriesRef().getRegistriesRef()[Reg::##highReg]; \
	u8& lowReg = cpu->getRegistriesRef().getRegistriesRef()[Reg::##lowReg]; \
	\
	doubleRegistry = 0x1234;\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u8>(0x12), highReg);\
	Assert::AreEqual(static_cast <u8>(0x33), lowReg);\
	Assert::AreEqual(static_cast <u16>(0x1233), doubleRegistry);\
	\
	doubleRegistry = 0x1200;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x11), highReg);\
	Assert::AreEqual(static_cast <u8>(0xFF), lowReg);\
	Assert::AreEqual(static_cast <u16>(0x11FF), doubleRegistry); \
	\
	doubleRegistry = 0x0000;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0xFF), highReg);\
	Assert::AreEqual(static_cast <u8>(0xFF), lowReg);\
	Assert::AreEqual(static_cast <u16>(0xFFFF), doubleRegistry); \
}

#define TEST_DEC_SP(opcode) \
TEST_METHOD(DEC_SP)\
{\
	u16& SP = cpu->getRegistriesRef().getSPRef();\
	\
	SP = 0x1234;\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast <u16>(0x1233), SP);\
	\
	SP = 0x0000;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast <u16>(0xFFFF), SP); \
}

#define TEST_ADD_HL_RR(highReg, lowReg, opcode) \
TEST_METHOD(ADD_HL_##highReg##lowReg)\
{\
	u16& doubleRegistry = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::##highReg##lowReg]; \
	u8& highReg = cpu->getRegistriesRef().getRegistriesRef()[Reg::##highReg]; \
	u8& lowReg = cpu->getRegistriesRef().getRegistriesRef()[Reg::##lowReg]; \
	u16& HLReg = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL]; \
	u8& HReg = cpu->getRegistriesRef().getRegistriesRef()[Reg::H]; \
	u8& LReg = cpu->getRegistriesRef().getRegistriesRef()[Reg::L]; \
	\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	flags.flags.Z = 1;\
	flags.flags.N = 1;\
	flags.flags.H = 0;\
	flags.flags.C = 0;\
	\
	doubleRegistry = 0x0002;\
	HLReg = 0x0008;\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u8>(0x00), highReg);\
	Assert::AreEqual(static_cast<u8>(0x02), lowReg);\
	Assert::AreEqual(static_cast<u16>(0x0002), doubleRegistry);\
	Assert::AreEqual(static_cast<u16>(0x000A), HLReg);\
	Assert::AreEqual(static_cast<u8>(0x00), HReg);\
	Assert::AreEqual(static_cast<u8>(0x0A), LReg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	doubleRegistry = 0x0005;\
	HLReg = 0x0FFB;\
	flags.flags.Z = 0;\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u8>(0x00), highReg);\
	Assert::AreEqual(static_cast<u8>(0x05), lowReg);\
	Assert::AreEqual(static_cast<u16>(0x0005), doubleRegistry); \
	Assert::AreEqual(static_cast<u16>(0x1000), HLReg);\
	Assert::AreEqual(static_cast<u8>(0x10), HReg);\
	Assert::AreEqual(static_cast<u8>(0x00), LReg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	doubleRegistry = 0x0002;\
	HLReg = 0xFFFE;\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u16>(0x0000), HLReg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);\
}

#define TEST_ADD_HL_HL(opcode) \
TEST_METHOD(ADD_HL_HL)\
{\
u16& HLReg = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL]; \
u8& highReg = cpu->getRegistriesRef().getRegistriesRef()[Reg::H]; \
u8& lowReg = cpu->getRegistriesRef().getRegistriesRef()[Reg::L]; \
\
flags& flags = cpu->getRegistriesRef().getFlagsRef(); \
flags.flags.Z = 1; \
flags.flags.N = 1; \
flags.flags.H = 0; \
flags.flags.C = 0; \
\
HLReg = 0x0008; \
cpu->executeOpcode(opcode); \
\
Assert::AreEqual(static_cast<u8>(0x00), highReg); \
Assert::AreEqual(static_cast<u8>(0x10), lowReg); \
Assert::AreEqual(static_cast<u16>(0x0010), HLReg); \
Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z); \
Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N); \
Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H); \
Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C); \
\
HLReg = 0x0FFB; \
flags.flags.Z = 0; \
cpu->executeOpcode(opcode); \
\
Assert::AreEqual(static_cast<u16>(0x1FF6), HLReg); \
Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z); \
Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H); \
Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C); \
\
HLReg = 0xFFFE; \
cpu->executeOpcode(opcode); \
\
Assert::AreEqual(static_cast<u16>(0xFFFC), HLReg); \
Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H); \
Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C); \
}

#define TEST_ADD_HL_SP(opcode) \
TEST_METHOD(ADD_HL_SP)\
{\
	u16& SP = cpu->getRegistriesRef().getSPRef();\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL]; \
	u8& H = cpu->getRegistriesRef().getRegistriesRef()[Reg::H]; \
	u8& L = cpu->getRegistriesRef().getRegistriesRef()[Reg::L]; \
	\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	flags.flags.Z = 1;\
	flags.flags.N = 1;\
	flags.flags.H = 0;\
	flags.flags.C = 0;\
	\
	SP = 0x0002;\
	HL = 0x0008;\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u16>(0x0002), SP);\
	Assert::AreEqual(static_cast<u16>(0x000A), HL);\
	Assert::AreEqual(static_cast<u8>(0x00), H);\
	Assert::AreEqual(static_cast<u8>(0x0A), L);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	SP = 0x0005;\
	HL = 0x0FFB;\
	flags.flags.Z = 0;\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u16>(0x0005), SP); \
	Assert::AreEqual(static_cast<u16>(0x1000), HL);\
	Assert::AreEqual(static_cast<u8>(0x10), H);\
	Assert::AreEqual(static_cast<u8>(0x00), L);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	SP = 0x0002;\
	HL = 0xFFFE;\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u16>(0x0000), HL);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);\
}

namespace Instructions_tests
{

	TEST_CLASS(I16BitLogicTests)
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

		TEST_INC_RR(B, C,	0x03);
		TEST_ADD_HL_RR(B, C,0x09);
		TEST_DEC_RR(B, C,	0x0B);
		TEST_INC_RR(D, E,	0x13);
		TEST_ADD_HL_RR(D, E,0x19);
		TEST_DEC_RR(D, E,	0x1B);
		TEST_INC_RR(H, L,	0x23);
		TEST_ADD_HL_HL(		0x29);
		TEST_DEC_RR(H, L,	0x2B);
		TEST_INC_SP(		0x33);
		TEST_ADD_HL_SP(		0x39);
		TEST_DEC_SP(		0x3B);


	};
	std::shared_ptr<Memory> I16BitLogicTests::memory = nullptr;
	std::shared_ptr<Cartridge> I16BitLogicTests::cartridge = nullptr;
	std::shared_ptr<Bus> I16BitLogicTests::bus = nullptr;
	std::shared_ptr<CPU> I16BitLogicTests::cpu = nullptr;
	std::shared_ptr<PPU> I16BitLogicTests::ppu = nullptr;
}