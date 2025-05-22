#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"
#include "..\PPU\PPU.h"
#include "..\Utils\Utils.h"


#define TEST_JR_a16(opcode)\
TEST_METHOD(JR_a16)\
{\
	u16& PC = cpu->getRegistriesRef().getPCRef();\
	flags& f = cpu->getRegistriesRef().getFlagsRef();\
	PC = 0xC000;\
	cpu->writeMemory(PC + 1, 0x32);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u16>(0xC034), PC);\
	\
	PC = 0xC064; /*3172*/ \
	cpu->writeMemory(PC + 1, 0xCE); /*-50*/\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u16>(0xC034), PC); /*3122*/\
	\
	PC = 0xC078;\
	cpu->writeMemory(PC + 1, 0x9C); /*-100*/\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u16>(0xC016), PC); /*3122*/\
}

#define TEST_JR_CC_a16(flag, condition, opcode, testName)\
TEST_METHOD(testName)\
{\
	u16& PC = cpu->getRegistriesRef().getPCRef();\
	flags& f = cpu->getRegistriesRef().getFlagsRef();\
	PC = 0xC000;\
	f.flags.flag = condition;\
	cpu->writeMemory(PC + 1, 0x32);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u16>(0xC002), PC);\
	\
	PC = 0xC000; \
	f.flags.flag = !condition;\
	cpu->writeMemory(PC + 1, 0x32);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u16>(0xC034), PC);\
}

#define TEST_RET(opcode)\
TEST_METHOD(RET)\
{\
	u16& SP = cpu->getRegistriesRef().getSPRef(); \
	u16& PC = cpu->getRegistriesRef().getPCRef(); \
	\
	SP = 0xC000; \
	PC = 0x0000; \
	bus->write(0xC000, 0x12); \
	bus->write(0xC001, 0x34); \
	\
	cpu->executeOpcode(opcode); \
	\
	Assert::AreEqual(static_cast<u16>(0xC002), SP); \
	Assert::AreEqual(static_cast<u16>(0x3412), PC); \
}

#define TEST_RET_CC(flag, condition, opcode, testName)\
TEST_METHOD(testName)\
{\
	u16& SP = cpu->getRegistriesRef().getSPRef(); \
	u16& PC = cpu->getRegistriesRef().getPCRef(); \
	flags& f = cpu->getRegistriesRef().getFlagsRef(); \
	f.flags.flag = condition;\
	\
	SP = 0xC000;\
	PC = 0x0000;\
	bus->write(0xC000, 0x12);\
	bus->write(0xC001, 0x34);\
	\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u16>(0xC000), SP);\
	Assert::AreEqual(static_cast<u16>(0x0001), PC);\
	\
	f.flags.flag = !condition;\
	SP = 0xC000;\
	PC = 0x0000;\
	bus->write(0xC000, 0x12);\
	bus->write(0xC001, 0x34);\
	\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u16>(0xC002), SP);\
	Assert::AreEqual(static_cast<u16>(0x3412), PC);\
}

#define TEST_RETI(opcode)\
TEST_METHOD(RETI)\
{\
	u16& SP = cpu->getRegistriesRef().getSPRef(); \
	u16& PC = cpu->getRegistriesRef().getPCRef(); \
	u8& IME = cpu->getRegistriesRef().getIMERef(); \
	\
	SP = 0xC000; \
	PC = 0x0000; \
	IME = 0; \
	bus->write(0xC000, 0x12); \
	bus->write(0xC001, 0x34); \
	\
	cpu->executeOpcode(opcode); \
	\
	Assert::AreEqual(static_cast<u16>(0xC002), SP); \
	Assert::AreEqual(static_cast<u16>(0x3412), PC); \
	Assert::AreEqual(static_cast<u8>(0x01), IME); \
	\
	IME = 1; \
	cpu->executeOpcode(opcode); \
	Assert::AreEqual(static_cast<u8>(0x01), IME); \
}

#define TEST_JP_a16(opcode)\
TEST_METHOD(JP_a16)\
{\
	u16& PC = cpu->getRegistriesRef().getPCRef(); \
	PC = 0xC000;\
	bus->write((PC + 1), 0x05);\
	bus->write((PC + 2), 0xC0);\
	\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u16>(0xC005), PC);\
}

#define TEST_JP_CC_a16(flag, condition, opcode, testName)\
TEST_METHOD(testName)\
{\
	u16& PC = cpu->getRegistriesRef().getPCRef(); \
	flags& f = cpu->getRegistriesRef().getFlagsRef(); \
	f.flags.flag = condition; \
	PC = 0xC000;\
	\
	bus->write((PC + 1), 0x07);\
	bus->write((PC + 2), 0xC0);\
	\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u16>(0xC003), PC);\
	\
	PC = 0xC000;\
	f.flags.flag = !condition;\
	\
	bus->write((PC + 1), 0x07);\
	bus->write((PC + 2), 0xC0);\
	\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u16>(0xC007), PC);\
}

#define TEST_JP_pHLq(opcode)\
TEST_METHOD(JP_pHLq)\
{\
	u16& PC = cpu->getRegistriesRef().getPCRef(); \
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	PC = 0xC000;\
	HL = 0xC006;\
	\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u16>(0xC006), PC);\
}

#define TEST_CALL_a16(opcode)\
TEST_METHOD(CALL_a16)\
{\
	u16& SP = cpu->getRegistriesRef().getSPRef(); \
	u16& PC = cpu->getRegistriesRef().getPCRef(); \
	\
	SP = 0xC002;\
	PC = 0xC00A;\
	bus->write(0xC001, 0x12);\
	bus->write(0xC000, 0x34);\
	bus->write((PC + 1), 0x56);\
	bus->write((PC + 2), 0x78);\
	\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u16>(0xC000), SP);\
	Assert::AreEqual(static_cast<u16>(0x7856), PC);\
	Assert::AreEqual(static_cast<u8>(0xC0), bus->read(0xC001));\
	Assert::AreEqual(static_cast<u8>(0x0D), bus->read(0xC000));\
}

#define TEST_CALL_CC_a16(flag, condition, opcode, testName)\
TEST_METHOD(testName)\
{\
	u16& SP = cpu->getRegistriesRef().getSPRef(); \
	u16& PC = cpu->getRegistriesRef().getPCRef(); \
	flags& f = cpu->getRegistriesRef().getFlagsRef(); \
	f.flags.flag = condition; \
	\
	SP = 0xC002;\
	PC = 0xC00A;\
	bus->write(0xC001, 0x12);\
	bus->write(0xC000, 0x34);\
	bus->write((PC + 1), 0x56);\
	bus->write((PC + 2), 0x78);\
	\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u16>(0xC002), SP);\
	Assert::AreEqual(static_cast<u16>(0xC00D), PC);\
	Assert::AreEqual(static_cast<u8>(0x12), bus->read(0xC001));\
	Assert::AreEqual(static_cast<u8>(0x34), bus->read(0xC000));\
	\
	f.flags.flag = !condition; \
	\
	SP = 0xC002; \
	PC = 0xC00A; \
	bus->write(0xC001, 0x12); \
	bus->write(0xC000, 0x34); \
	bus->write((PC + 1), 0x56); \
	bus->write((PC + 2), 0x78); \
	\
	cpu->executeOpcode(opcode); \
	\
	Assert::AreEqual(static_cast<u16>(0xC000), SP); \
	Assert::AreEqual(static_cast<u16>(0x7856), PC); \
	Assert::AreEqual(static_cast<u8>(0xC0), bus->read(0xC001)); \
	Assert::AreEqual(static_cast<u8>(0x0D), bus->read(0xC000)); \
}

#define TEST_RST_VEC(vec, opcode, testName)\
TEST_METHOD(testName)\
{\
	u16& SP = cpu->getRegistriesRef().getSPRef(); \
	u16& PC = cpu->getRegistriesRef().getPCRef(); \
	\
	SP = 0xC002;\
	PC = 0xC00A;\
	bus->write(0xC001, 0x12);\
	bus->write(0xC000, 0x34);\
	bus->write(0xC00B, 0x56);\
	bus->write(0xC00C, 0x78);\
	\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u16>(0xC000), SP);\
	Assert::AreEqual(static_cast<u16>(0x##vec),PC);\
	Assert::AreEqual(static_cast<u8>(0xC0), bus->read(0xC001));\
	Assert::AreEqual(static_cast<u8>(0x0B), bus->read(0xC000));\
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{

	TEST_CLASS(IJumpTests)
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

		TEST_JR_a16(			0x18)
		TEST_JR_CC_a16(Z, false,0x20, JR_NZ_a16)
		TEST_JR_CC_a16(Z, true, 0x28, JR_Z_a16)
		TEST_JR_CC_a16(C, false,0x30, JR_NC_a16)
		TEST_JR_CC_a16(C, true,	0x38, JR_C_a16)

		TEST_RET_CC(Z, false,	0xC0, RET_NZ)
		TEST_RET_CC(Z, true,	0xC8, RET_Z)
		TEST_RET(				0xC9)
		TEST_RET_CC(C, false,	0xD0, RET_NC)
		TEST_RET_CC(C, true,	0xD8, RET_C)
		TEST_RETI(				0xD9)


		TEST_JP_CC_a16(Z, false,0xC2, JP_NZ_a16)
		TEST_JP_a16(		    0xC3)
		TEST_JP_CC_a16(Z, true, 0xCA, JP_Z_a16)
		TEST_JP_CC_a16(C, false,0xD2, JP_NC_a16)
		TEST_JP_CC_a16(C, true, 0xDA, JP_C_a16)
		TEST_JP_pHLq(			0xE9)

		TEST_CALL_CC_a16(Z, false,	0xC4, CALL_NZ_a16)
		TEST_CALL_CC_a16(Z, true,	0xCC, CALL_Z_a16)
		TEST_CALL_a16(				0xCD)
		TEST_CALL_CC_a16(C, false,	0xD4, CALL_NC_a16)
		TEST_CALL_CC_a16(C, true,	0xDC, CALL_C_a16)

		TEST_RST_VEC(00, 0xC7, RST_00H)
		TEST_RST_VEC(08, 0xCF, RST_08H)
		TEST_RST_VEC(10, 0xD7, RST_10H)
		TEST_RST_VEC(18, 0xDF, RST_18H)
		TEST_RST_VEC(20, 0xE7, RST_20H)
		TEST_RST_VEC(28, 0xEF, RST_28H)
		TEST_RST_VEC(30, 0xF7, RST_30H)
		TEST_RST_VEC(38, 0xFF, RST_38H)

	};

	std::shared_ptr<Memory> IJumpTests::memory = nullptr;
	std::shared_ptr<Cartridge> IJumpTests::cartridge = nullptr;
	std::shared_ptr<Bus> IJumpTests::bus = nullptr;
	std::shared_ptr<CPU> IJumpTests::cpu = nullptr;
	std::shared_ptr<PPU> IJumpTests::ppu = nullptr;
}