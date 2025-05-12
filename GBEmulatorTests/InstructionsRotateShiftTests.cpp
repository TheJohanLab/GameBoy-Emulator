#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"
#include "..\PPU\PPU.h"
#include "..\Utils\Utils.h"


#define TEST_RLCA(opcode, testName)\
TEST_METHOD(testName)\
{\
	u8& registry = cpu->getRegistriesRef().getRegistriesRef()[Reg::A]; \
	flags& f = cpu->getRegistriesRef().getFlagsRef();\
	registry = 0b11110000;\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u8>(0b11100001), registry);\
	\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b01110001;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0b11100010), registry);\
	\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b00000000;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00000000), registry);\
	\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}

#define TEST_RRCA(opcode, testName)\
TEST_METHOD(testName)\
{\
	u8& registry = cpu->getRegistriesRef().getRegistriesRef()[Reg::A]; \
	flags& f = cpu->getRegistriesRef().getFlagsRef();\
	registry = 0b11110000;\
	cpu->executeOpcode(opcode);\
	\
	Assert::AreEqual(static_cast<u8>(0b01111000), registry);\
	\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b01110001;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0b10111000), registry);\
	\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b00000000;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00000000), registry);\
	\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}


#define TEST_RLA(opcode, testName)\
TEST_METHOD(testName)\
{\
	u8& registry = cpu->getRegistriesRef().getRegistriesRef()[Reg::A]; \
	flags& f = cpu->getRegistriesRef().getFlagsRef();\
	registry = 0b11111111;\
	f.flags.C = 0x00;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0b11111110), registry);\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b00000000;\
	f.flags.C = 0x01;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00000001), registry);\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b00000000;\
	f.flags.C = 0x00;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00000000), registry);\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}

#define TEST_RRA(opcode, testName)\
TEST_METHOD(testName)\
{\
	u8& registry = cpu->getRegistriesRef().getRegistriesRef()[Reg::A]; \
	flags& f = cpu->getRegistriesRef().getFlagsRef();\
	registry = 0b11111111;\
	f.flags.C = 0x00;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0b01111111), registry);\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b00000000;\
	f.flags.C = 0x01;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0b10000000), registry);\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b00000000;\
	f.flags.C = 0x00;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00000000), registry);\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}



#define TEST_RLC_R(reg, opcode, testName)\
TEST_METHOD(testName)\
{\
	u8& registry = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg]; \
	flags& f = cpu->getRegistriesRef().getFlagsRef();\
	registry = 0b11110000;\
	cpu->executeOpcodeCB(opcode);\
	\
	Assert::AreEqual(static_cast<u8>(0b11100001), registry);\
	\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b01110001;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b11100010), registry);\
	\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b00000000;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00000000), registry);\
	\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}


#define TEST_RLC_pHLq(opcode, testName)\
TEST_METHOD(testName)\
{\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	flags& f = cpu->getRegistriesRef().getFlagsRef();\
	HL = 0xC000;\
	bus->write(HL, 0b11110000);\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b11100001), bus->read(HL));\
	\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	bus->write(HL, 0b01110001);\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b11100010), bus->read(HL));\
	\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	bus->write(HL, 0b00000000); \
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00000000), bus->read(HL));\
	\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}

#define TEST_RRC_R(reg, opcode, testName)\
TEST_METHOD(testName)\
{\
	u8& registry = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg]; \
	flags& f = cpu->getRegistriesRef().getFlagsRef();\
	registry = 0b11110000;\
	cpu->executeOpcodeCB(opcode);\
	\
	Assert::AreEqual(static_cast<u8>(0b01111000), registry);\
	\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b01110001;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b10111000), registry);\
	\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b00000000;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00000000), registry);\
	\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}

#define TEST_RRC_pHLq(opcode, testName)\
TEST_METHOD(testName)\
{\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	flags& f = cpu->getRegistriesRef().getFlagsRef();\
	HL = 0xC000;\
	bus->write(HL, 0b11110000);\
	cpu->executeOpcodeCB(opcode);\
	\
	Assert::AreEqual(static_cast<u8>(0b01111000), bus->read(HL));\
	\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	bus->write(HL, 0b01110001);\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b10111000), bus->read(HL));\
	\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	bus->write(HL, 0b00000000); \
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00000000), bus->read(HL));\
	\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}

#define TEST_RL_R(reg, opcode, testName)\
TEST_METHOD(testName)\
{\
	u8& registry = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg]; \
	flags& f = cpu->getRegistriesRef().getFlagsRef();\
	registry = 0b11111111;\
	f.flags.C = 0x00;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b11111110), registry);\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b00000000;\
	f.flags.C = 0x01;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00000001), registry);\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b00000000;\
	f.flags.C = 0x00;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00000000), registry);\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}

#define TEST_RL_pHLq(opcode, testName)\
TEST_METHOD(testName)\
{\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	flags& f = cpu->getRegistriesRef().getFlagsRef();\
	HL = 0xC000;\
	bus->write(HL, 0b11111111);\
	f.flags.C = 0x00;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b11111110), bus->read(HL));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	bus->write(HL, 0b00000000);\
	f.flags.C = 0x01;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00000001), bus->read(HL));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	bus->write(HL, 0b00000000);\
	f.flags.C = 0x00;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00000000), bus->read(HL));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}

#define TEST_RR_R(reg, opcode, testName)\
TEST_METHOD(testName)\
{\
	u8& registry = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg]; \
	flags& f = cpu->getRegistriesRef().getFlagsRef();\
	registry = 0b11111111;\
	f.flags.C = 0x00;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b01111111), registry);\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b00000000;\
	f.flags.C = 0x01;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b10000000), registry);\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b00000000;\
	f.flags.C = 0x00;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00000000), registry);\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}

#define TEST_RR_pHLq(opcode, testName)\
TEST_METHOD(testName)\
{\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	flags& f = cpu->getRegistriesRef().getFlagsRef();\
	HL = 0xC000;\
	bus->write(HL, 0b11111111);\
	f.flags.C = 0x00;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b01111111), bus->read(HL));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	bus->write(HL, 0b00000000);\
	f.flags.C = 0x01;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b10000000), bus->read(HL));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	bus->write(HL, 0b00000000);\
	f.flags.C = 0x00;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00000000), bus->read(HL));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}

#define TEST_SLA_R(reg, opcode, testName) \
TEST_METHOD(testName)\
{\
	u8& registry = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg]; \
	flags& f = cpu->getRegistriesRef().getFlagsRef(); \
	registry = 0b11111111; \
	f.flags.C = 0x00; \
	cpu->executeOpcodeCB(opcode); \
	Assert::AreEqual(static_cast<u8>(0b11111110), registry);\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b00000000; \
	f.flags.C = 0x01; \
	cpu->executeOpcodeCB(opcode); \
	Assert::AreEqual(static_cast<u8>(0b00000000), registry);\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b01111000;\
	cpu->getFlagRegistry()->flags.C = 0x00;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b11110000), registry);\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));\
}

#define TEST_SLA_pHLq(opcode, testName) \
TEST_METHOD(testName)\
{\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	flags& f = cpu->getRegistriesRef().getFlagsRef();\
	HL = 0xC000;\
	bus->write(HL, 0b11111111);\
	f.flags.C = 0x00; \
	cpu->executeOpcodeCB(opcode); \
	Assert::AreEqual(static_cast<u8>(0b11111110), bus->read(HL));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	bus->write(HL, 0b00000000);\
	f.flags.C = 0x01; \
	cpu->executeOpcodeCB(opcode); \
	Assert::AreEqual(static_cast<u8>(0b00000000), bus->read(HL));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	bus->write(HL, 0b01111000);\
	cpu->getFlagRegistry()->flags.C = 0x00;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b11110000), bus->read(HL));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}

#define TEST_SRA_R(reg, opcode, testName) \
TEST_METHOD(testName)\
{\
	u8& registry = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg]; \
	flags& f = cpu->getRegistriesRef().getFlagsRef(); \
	registry = 0b11111111; \
	f.flags.C = 0x00; \
	cpu->executeOpcodeCB(opcode); \
	Assert::AreEqual(static_cast<u8>(0b11111111), registry);\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b00000000; \
	f.flags.C = 0x01; \
	cpu->executeOpcodeCB(opcode); \
	Assert::AreEqual(static_cast<u8>(0b00000000), registry);\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b01111000;\
	cpu->getFlagRegistry()->flags.C = 0x00;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00111100), registry);\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}

#define TEST_SRA_pHLq(opcode, testName) \
TEST_METHOD(testName)\
{\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	flags& f = cpu->getRegistriesRef().getFlagsRef();\
	HL = 0xC000;\
	bus->write(HL, 0b11111111);\
	f.flags.C = 0x00; \
	cpu->executeOpcodeCB(opcode); \
	Assert::AreEqual(static_cast<u8>(0b11111111), bus->read(HL));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	bus->write(HL, 0b00000000);\
	f.flags.C = 0x01; \
	cpu->executeOpcodeCB(opcode); \
	Assert::AreEqual(static_cast<u8>(0b00000000), bus->read(HL));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	bus->write(HL, 0b01111000);\
	cpu->getFlagRegistry()->flags.C = 0x00;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00111100), bus->read(HL));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}

#define TEST_SWAP_R(reg, opcode, testName) \
TEST_METHOD(testName)\
{\
	u8& registry = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg]; \
	flags& f = cpu->getRegistriesRef().getFlagsRef(); \
	registry = 0b10010110; \
	f.flags.C = 0x00; \
	cpu->executeOpcodeCB(opcode); \
	Assert::AreEqual(static_cast<u8>(0b01101001), registry);\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b00000000; \
	f.flags.C = 0x01; \
	cpu->executeOpcodeCB(opcode); \
	Assert::AreEqual(static_cast<u8>(0b00000000), registry);\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b01111000;\
	cpu->getFlagRegistry()->flags.C = 0x00;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b10000111), registry);\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}

#define TEST_SWAP_pHLq(opcode, testName) \
TEST_METHOD(testName)\
{\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	flags& f = cpu->getRegistriesRef().getFlagsRef();\
	HL = 0xC000;\
	bus->write(HL, 0b10010110);\
	f.flags.C = 0x00; \
	cpu->executeOpcodeCB(opcode); \
	Assert::AreEqual(static_cast<u8>(0b01101001), bus->read(HL));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	bus->write(HL, 0b00000000);\
	f.flags.C = 0x01; \
	cpu->executeOpcodeCB(opcode); \
	Assert::AreEqual(static_cast<u8>(0b00000000), bus->read(HL));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	bus->write(HL, 0b01111000);\
	cpu->getFlagRegistry()->flags.C = 0x00;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b10000111), bus->read(HL));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}

#define TEST_SRL_R(reg, opcode, testName) \
TEST_METHOD(testName)\
{\
	u8& registry = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg]; \
	flags& f = cpu->getRegistriesRef().getFlagsRef(); \
	registry = 0b11111111; \
	f.flags.C = 0x00; \
	cpu->executeOpcodeCB(opcode); \
	Assert::AreEqual(static_cast<u8>(0b01111111), registry);\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b00000000; \
	f.flags.C = 0x01; \
	cpu->executeOpcodeCB(opcode); \
	Assert::AreEqual(static_cast<u8>(0b00000000), registry);\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	registry = 0b01111000;\
	cpu->getFlagRegistry()->flags.C = 0x00;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00111100), registry);\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}

#define TEST_SRL_pHLq(opcode, testName) \
TEST_METHOD(testName)\
{\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	flags& f = cpu->getRegistriesRef().getFlagsRef();\
	HL = 0xC000;\
	bus->write(HL, 0b11111111);\
	f.flags.C = 0x00; \
	cpu->executeOpcodeCB(opcode); \
	Assert::AreEqual(static_cast<u8>(0b01111111), bus->read(HL));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	bus->write(HL, 0b00000000);\
	f.flags.C = 0x01; \
	cpu->executeOpcodeCB(opcode); \
	Assert::AreEqual(static_cast<u8>(0b00000000), bus->read(HL));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
	\
	bus->write(HL, 0b01111000);\
	cpu->getFlagRegistry()->flags.C = 0x00;\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0b00111100), bus->read(HL));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.C));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(f.flags.N));\
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{
	TEST_CLASS(IRotateShiftTests)
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

		TEST_RLCA(	  0x07, RLCA)
		TEST_RRCA(	  0x0F, RRCA)
		TEST_RLA(	  0x17, RLA)
		TEST_RRA(	  0x1F, RRA)

		TEST_RLC_R(B, 0x00, RLC_B)
		TEST_RLC_R(C, 0x01, RLC_C)
		TEST_RLC_R(D, 0x02, RLC_D)
		TEST_RLC_R(E, 0x03, RLC_E)
		TEST_RLC_R(H, 0x04, RLC_H)
		TEST_RLC_R(L, 0x05, RLC_L)
		TEST_RLC_pHLq(0x06, RLC_pHLq)
		TEST_RLC_R(A, 0x07, RLC_A)

		TEST_RRC_R(B, 0x08, RRC_B)
		TEST_RRC_R(C, 0x09, RRC_C)
		TEST_RRC_R(D, 0x0A, RRC_D)
		TEST_RRC_R(E, 0x0B, RRC_E)
		TEST_RRC_R(H, 0x0C, RRC_H)
		TEST_RRC_R(L, 0x0D, RRC_L)
		TEST_RRC_pHLq(0x0E, RRC_pHLq)
		TEST_RRC_R(A, 0x0F, RRC_A)

		TEST_RL_R(B, 0x10, RL_B)
		TEST_RL_R(C, 0x11, RL_C)
		TEST_RL_R(D, 0x12, RL_D)
		TEST_RL_R(E, 0x13, RL_E)
		TEST_RL_R(H, 0x14, RL_H)
		TEST_RL_R(L, 0x15, RL_L)
		TEST_RL_pHLq(0x16, RL_pHLq)
		TEST_RL_R(A, 0x17, RL_A)

		TEST_RR_R(B, 0x18, Rr_B)
		TEST_RR_R(C, 0x19, Rr_C)
		TEST_RR_R(D, 0x1A, Rr_D)
		TEST_RR_R(E, 0x1B, Rr_E)
		TEST_RR_R(H, 0x1C, Rr_H)
		TEST_RR_R(L, 0x1D, Rr_L)
		TEST_RR_pHLq(0x1E, RR_pHLq)
		TEST_RR_R(A, 0x1F, RR_A)

		TEST_SLA_R(B, 0x20, SLA_B)
		TEST_SLA_R(C, 0x21, SLA_C)
		TEST_SLA_R(D, 0x22, SLA_D)
		TEST_SLA_R(E, 0x23, SLA_E)
		TEST_SLA_R(H, 0x24, SLA_H)
		TEST_SLA_R(L, 0x25, SLA_L)
		TEST_SLA_pHLq(0x26, SLA_pHLq)
		TEST_SLA_R(A, 0x27, SLA_A)
		
		TEST_SRA_R(B, 0x28, SRA_B)
		TEST_SRA_R(C, 0x29, SRA_C)
		TEST_SRA_R(D, 0x2A, SRA_D)
		TEST_SRA_R(E, 0x2B, SRA_E)
		TEST_SRA_R(H, 0x2C, SRA_H)
		TEST_SRA_R(L, 0x2D, SRA_L)
		TEST_SRA_pHLq(0x2E, SRA_pHLq)
		TEST_SRA_R(A, 0x2F, SRA_A)

		TEST_SWAP_R(B, 0x30, SWAP_B)
		TEST_SWAP_R(C, 0x31, SWAP_C)
		TEST_SWAP_R(D, 0x32, SWAP_D)
		TEST_SWAP_R(E, 0x33, SWAP_E)
		TEST_SWAP_R(H, 0x34, SWAP_H)
		TEST_SWAP_R(L, 0x35, SWAP_L)
		TEST_SWAP_pHLq(0x36, SWAP_pHLq)
		TEST_SWAP_R(A, 0x37, SWAP_A)

		TEST_SRL_R(B, 0x38, SRL_B)
		TEST_SRL_R(C, 0x39, SRL_C)
		TEST_SRL_R(D, 0x3A, SRL_D)
		TEST_SRL_R(E, 0x3B, SRL_E)
		TEST_SRL_R(H, 0x3C, SRL_H)
		TEST_SRL_R(L, 0x3D, SRL_L)
		TEST_SRL_pHLq(0x3E, SRL_pHLq)
		TEST_SRL_R(A, 0x3F, SRL_A)

	};

	std::shared_ptr<Memory> IRotateShiftTests::memory = nullptr;
	std::shared_ptr<Cartridge> IRotateShiftTests::cartridge = nullptr;
	std::shared_ptr<Bus> IRotateShiftTests::bus = nullptr;
	std::shared_ptr<CPU> IRotateShiftTests::cpu = nullptr;
	std::shared_ptr<PPU> IRotateShiftTests::ppu = nullptr;
}