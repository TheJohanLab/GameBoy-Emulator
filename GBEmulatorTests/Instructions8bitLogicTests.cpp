#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"
#include "..\PPU\PPU.h"
#include "..\Utils\Utils.h"


#define TEST_INC_R(reg, opcode) \
TEST_METHOD(INC_##reg) \
{ \
    u8& reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg]; \
    flags& flags = cpu->getRegistriesRef().getFlagsRef(); \
    \
    reg = 0x03; \
    cpu->executeOpcode(opcode); \
    Assert::AreEqual(static_cast<u8>(0x04), reg); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.Z); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.N); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.H); \
    \
    reg = 0x1F; \
    cpu->executeOpcode(opcode); \
    Assert::AreEqual(static_cast<u8>(0x20), reg); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.Z); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.N); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.H); \
    \
    reg = 0xFF; \
    cpu->executeOpcode(opcode); \
    Assert::AreEqual(static_cast<u8>(0x00), reg); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.H); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.Z); \
}

#define TEST_DEC_R(reg, opcode) \
TEST_METHOD(DEC_##reg) \
{ \
    u8& reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg]; \
    flags& flags = cpu->getRegistriesRef().getFlagsRef(); \
    \
    reg = 0x03; \
    cpu->executeOpcode(opcode); \
    Assert::AreEqual(static_cast<u8>(0x02), reg); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.Z); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.N); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.H); \
    \
    reg = 0x10; \
    cpu->executeOpcode(opcode); \
    Assert::AreEqual(static_cast<u8>(0x0F), reg); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.Z); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.N); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.H); \
    \
    reg = 0x01; \
    cpu->executeOpcode(opcode); \
    Assert::AreEqual(static_cast<u8>(0x00), reg); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.Z); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.N); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.H); \
    \
    reg = 0x00; \
    cpu->executeOpcode(opcode); \
    Assert::AreEqual(static_cast<u8>(0xFF), reg); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.Z); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.N); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.H); \
}

#define TEST_DAA(initialA, expectedA, expectedZ, expectedH, expectedC, ...) \
    A = initialA; \
    __VA_ARGS__; \
    cpu->executeOpcode(0x27); /* DAA */ \
    Assert::AreEqual(static_cast<u8>(expectedA), A); \
    Assert::AreEqual(static_cast<u8>(expectedZ), flags.flags.Z); \
    Assert::AreEqual(static_cast<u8>(expectedH), flags.flags.H); \
    Assert::AreEqual(static_cast<u8>(expectedC), flags.flags.C);

#define TEST_CPL(opcode) \
TEST_METHOD(CPL)\
{\
u8& A = cpu->getRegistriesRef().getRegistriesRef()[Reg::A]; \
flags& flags = cpu->getRegistriesRef().getFlagsRef(); \
\
A = 0b00100110; \
flags.flags.H = 0; \
flags.flags.N = 0; \
cpu->executeOpcode(opcode); \
\
Assert::AreEqual(static_cast<u8>(0b11011001), A); \
Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H); \
Assert::AreEqual(static_cast <u8>(0x01), flags.flags.N); \
}

#define TEST_INC_pHLq( opcode) \
TEST_METHOD(INC_pHLq) \
{ \
    u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL]; \
    flags& flags = cpu->getRegistriesRef().getFlagsRef(); \
    \
    HL = 0xC000; \
	bus->write(0xC000, 0x0A);\
    cpu->executeOpcode(opcode); \
    Assert::AreEqual(static_cast<u8>(0x0B), bus->read(HL)); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.Z); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.N); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.H); \
    \
    bus->write(0xC000, 0x1F);\
    cpu->executeOpcode(opcode); \
    Assert::AreEqual(static_cast<u8>(0x20), bus->read(HL)); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.Z); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.N); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.H); \
    \
    bus->write(0xC000, 0xFF);\
    cpu->executeOpcode(opcode); \
    Assert::AreEqual(static_cast<u8>(0x00), bus->read(HL)); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.H); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.Z); \
}

#define TEST_DEC_pHLq(opcode) \
TEST_METHOD(DEC_pHLq) \
{ \
    u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL]; \
    flags& flags = cpu->getRegistriesRef().getFlagsRef(); \
    \
    HL = 0xC000; \
	bus->write(0xC000, 0x03);\
    cpu->executeOpcode(opcode); \
    Assert::AreEqual(static_cast<u8>(0x02), bus->read(HL)); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.Z); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.N); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.H); \
    \
	bus->write(0xC000, 0x10);\
    cpu->executeOpcode(opcode); \
    Assert::AreEqual(static_cast<u8>(0x0F), bus->read(HL)); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.Z); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.N); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.H); \
    \
    bus->write(0xC000, 0x01);\
    cpu->executeOpcode(opcode); \
    Assert::AreEqual(static_cast<u8>(0x00), bus->read(HL)); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.Z); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.N); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.H); \
    \
    bus->write(0xC000, 0x00);\
    cpu->executeOpcode(opcode); \
    Assert::AreEqual(static_cast<u8>(0xFF), bus->read(HL)); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.Z); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.N); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.H); \
}

#define TEST_SCF(opcode) \
TEST_METHOD(SCF) \
{ \
    flags& flags = cpu->getRegistriesRef().getFlagsRef(); \
    \
	flags.F = 0x00;\
    cpu->executeOpcode(opcode); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.C); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.N); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.H); \
    \
	flags.F = 0xFF;\
    cpu->executeOpcode(opcode); \
    Assert::AreEqual(static_cast<u8>(0x01), flags.flags.C); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.N); \
    Assert::AreEqual(static_cast<u8>(0x00), flags.flags.H); \
}

#define TEST_CCF(opcode) \
TEST_METHOD(CCF)\
{\
flags& flags = cpu->getRegistriesRef().getFlagsRef(); \
\
flags.flags.C = 0;\
flags.flags.H = 1; \
flags.flags.N = 1; \
cpu->executeOpcode(opcode); \
\
Assert::AreEqual(static_cast<u8>(0x01), flags.flags.C); \
Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H); \
Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N); \
\
flags.flags.C = 1;\
flags.flags.H = 0; \
flags.flags.N = 0; \
cpu->executeOpcode(opcode); \
\
Assert::AreEqual(static_cast<u8>(0x00), flags.flags.C); \
Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H); \
Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N); \
}

#define TEST_ADD_A_R(reg, opcode) \
TEST_METHOD(ADD_A_##reg##)\
{\
	u8& A_reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	u8& reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg##];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	flags.F = 0x00;\
	A_reg = 0x05;\
	reg = 0xD3;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0xD8), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0xE5;\
	reg = 0x1F;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x04), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0xE5;\
	reg = 0x1B;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);\
}

#define TEST_ADD_A_pHLq(opcode) \
TEST_METHOD(ADD_A_pHLq)\
{\
	u8& A_reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	flags.F = 0x00;\
	A_reg = 0x05;\
	HL = 0xC000;\
	bus->write(0xC000,0xD3);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0xD8), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0xE5;\
	bus->write(0xC000,0x1F);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x04), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0xE5;\
	bus->write(0xC000,0x1B);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);\
}

#define TEST_ADC_A_R(reg, opcode) \
TEST_METHOD(ADC_A_##reg##)\
{\
	u8& A_reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	u8& reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg##];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	flags.F = 0x00;\
	flags.flags.C = 1;\
	A_reg = 0x05;\
	reg = 0xD3;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0xD9), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0xE5;\
	reg = 0x1F;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x04), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0xE5;\
	reg = 0x1B;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);\
}

#define TEST_ADC_A_pHLq(opcode) \
TEST_METHOD(ADC_A_pHLq)\
{\
	u8& A_reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	flags.F = 0x00;\
	flags.flags.C = 1;\
	A_reg = 0x05;\
	HL = 0xC000;\
	bus->write(0xC000,0xD3);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0xD9), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0xE5;\
	bus->write(0xC000,0x1F);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x04), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0xE5;\
	bus->write(0xC000,0x1B);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);\
}

#define TEST_SUB_A_R(reg, opcode) \
TEST_METHOD(SUB_A_##reg##)\
{\
	u8& A_reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	u8& reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg##];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	flags.F = 0x00;\
	A_reg = 0x05;\
	reg = 0xD3;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0xF0), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0x08;\
	reg = 0x08;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0x25;\
	reg = 0x06;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x1F), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0x20;\
	reg = 0x30;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0xF0), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);\
}

#define TEST_SUB_A_pHLq(opcode) \
TEST_METHOD(SUB_A_pHLq)\
{\
	u8& A_reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	flags.F = 0x00;\
	A_reg = 0x05;\
	HL = 0xC000;\
	bus->write(0xC000,0xD3);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0xF0), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0x08;\
	bus->write(0xC000,0x08);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0x25;\
	bus->write(0xC000,0x06);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x1F), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0x20;\
	bus->write(0xC000,0x30);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0xF0), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);\
}

#define TEST_SBC_A_R(reg, opcode) \
TEST_METHOD(SBC_A_##reg##)\
{\
	u8& A_reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	u8& reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg##];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	flags.F = 0x00;\
	flags.flags.C = 1;\
	A_reg = 0x05;\
	reg = 0xD3;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0xEF), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0x08;\
	reg = 0x08;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
}

#define TEST_SBC_A_pHLq(opcode) \
TEST_METHOD(SBC_A_pHLq)\
{\
	u8& A_reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	flags.F = 0x00;\
	flags.flags.C = 1;\
	A_reg = 0x05;\
	HL = 0xC000;\
	bus->write(0xC000,0xD3);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0xEF), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0x08;\
	bus->write(0xC000,0x08);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
}

#define TEST_AND_A_R(reg, opcode) \
TEST_METHOD(AND_A_##reg)\
{\
	u8& A_Reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	u8& reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	A_Reg = 0x05;\
	reg = 0x0B;\
	flags.F = 0x00;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x01), A_Reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	A_Reg = 0x0A;\
	reg = 0x05;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_Reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
}

#define TEST_AND_A_A(opcode) \
TEST_METHOD(AND_A_A)\
{\
	u8& A_Reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	A_Reg = 0x05;\
	flags.F = 0x00;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x05), A_Reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
}

#define TEST_AND_A_pHLq( opcode) \
TEST_METHOD(AND_A_pHLq)\
{\
	u8& A = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	A = 0x05;\
	HL = 0xC000;\
	bus->write(0xC000,0x0B);\
	flags.F = 0x00;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x01), A);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	A = 0x0A;\
	bus->write(0xC000,0x05);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
}

#define TEST_XOR_A_R(reg, opcode) \
TEST_METHOD(XOR_A_##reg)\
{\
	u8& A_Reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	u8& reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	A_Reg = 0x05;\
	reg = 0x0B;\
	flags.F = 0x00;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0E), A_Reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	A_Reg = 0x0A;\
	reg = 0x0A;\
	flags.F = 0x00;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_Reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
}

#define TEST_XOR_A_A(opcode) \
TEST_METHOD(XOR_A_A)\
{\
	u8& A_Reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	A_Reg = 0x05;\
	flags.F = 0x00;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_Reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
}

#define TEST_XOR_A_pHLq( opcode) \
TEST_METHOD(XOR_A_pHLq)\
{\
	u8& A = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	A = 0x05;\
	HL = 0xC000;\
	bus->write(0xC000,0x0B);\
	flags.F = 0x00;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0E), A);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	A = 0x0A;\
	bus->write(0xC000,0x0A);\
	flags.F = 0x01;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
}

#define TEST_OR_A_R(reg, opcode) \
TEST_METHOD(OR_A_##reg)\
{\
	u8& A_Reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	u8& reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	A_Reg = 0x15;\
	reg = 0x5B;\
	flags.F = 0x00;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x05F), A_Reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	A_Reg = 0x00;\
	reg = 0x00;\
	flags.F = 0x01;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_Reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
}

#define TEST_OR_A_A(opcode) \
TEST_METHOD(OR_A_A)\
{\
	u8& A_Reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	A_Reg = 0x15;\
	flags.F = 0x00;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x015), A_Reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
}

#define TEST_OR_A_pHLq(opcode) \
TEST_METHOD(OR_A_pHLq)\
{\
	u8& A = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	A = 0x15;\
	HL = 0xC000;\
	bus->write(0xC000,0x5B);\
	flags.F = 0x00;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x5F), A);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	A = 0x00;\
	bus->write(0xC000,0x00);\
	flags.F = 0x01;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
}

#define TEST_CP_A_R(reg, opcode) \
TEST_METHOD(CP_A_##reg)\
{\
	u8& A_reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A]; \
	u8& reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg]; \
	flags& flags = cpu->getRegistriesRef().getFlagsRef(); \
	\
	flags.F = 0x00;\
	A_reg = 0xFE; \
	reg = 0x0E; \
	cpu->executeOpcode(opcode); \
	Assert::AreEqual(static_cast<u8>(0xFE), A_reg); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z); \
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.N); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C); \
	\
	A_reg = 0x08; \
	reg = 0x08; \
	cpu->executeOpcode(opcode); \
	Assert::AreEqual(static_cast<u8>(0x08), A_reg); \
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C); \
	\
	A_reg = 0x25; \
	reg = 0x06; \
	cpu->executeOpcode(opcode); \
	Assert::AreEqual(static_cast<u8>(0x25), A_reg); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z); \
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C); \
	\
	A_reg = 0x20; \
	reg = 0x30; \
	cpu->executeOpcode(opcode); \
	Assert::AreEqual(static_cast<u8>(0x20), A_reg); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H); \
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C); \
}

#define TEST_CP_A_A( opcode) \
TEST_METHOD(CP_A_A)\
{\
	u8& A_reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A]; \
	flags& flags = cpu->getRegistriesRef().getFlagsRef(); \
	\
	flags.F = 0x00;\
	A_reg = 0xFE; \
	cpu->executeOpcode(opcode); \
	Assert::AreEqual(static_cast<u8>(0xFE), A_reg); \
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z); \
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.N); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C); \
}

#define TEST_CP_A_pHLq(opcode) \
TEST_METHOD(CP_A_pHLq)\
{\
	u8& A_reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A]; \
	u16& HL = cpu->getRegistriesRef().getDoubleRegistriesRef()[DoubleReg::HL];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	flags.F = 0x00;\
	A_reg = 0xFE; \
	HL = 0xC000;\
	bus->write(0xC000,0x0E);\
	cpu->executeOpcode(opcode); \
	Assert::AreEqual(static_cast<u8>(0xFE), A_reg); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z); \
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.N); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C); \
	\
	A_reg = 0x08; \
	bus->write(0xC000,0x08);\
	cpu->executeOpcode(opcode); \
	Assert::AreEqual(static_cast<u8>(0x08), A_reg); \
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C); \
	\
	A_reg = 0x25; \
	bus->write(0xC000,0x06);\
	cpu->executeOpcode(opcode); \
	Assert::AreEqual(static_cast<u8>(0x25), A_reg); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z); \
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C); \
	\
	A_reg = 0x20; \
	bus->write(0xC000,0x30);\
	cpu->executeOpcode(opcode); \
	Assert::AreEqual(static_cast<u8>(0x20), A_reg); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H); \
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C); \
}




#define TEST_ADD_A_d8(opcode) \
TEST_METHOD(ADD_A_d8)\
{\
	u8& A_reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	flags.F = 0x00;\
	A_reg = 0x05;\
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0xD3);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0xD8), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0xE5;\
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0x1F);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x04), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0xE5;\
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0x1B);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);\
}

#define TEST_ADC_A_d8(opcode) \
TEST_METHOD(ADC_A_d8)\
{\
	u8& A_reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	flags.F = 0x00;\
	flags.flags.C = 1;\
	A_reg = 0x05;\
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0xD3);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0xD9), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0xE5;\
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0x1F);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x04), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0xE5;\
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0x1B);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);\
}

#define TEST_SUB_A_d8(opcode) \
TEST_METHOD(SUB_A_d8)\
{\
	u8& A_reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	flags.F = 0x00;\
	A_reg = 0x05;\
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0xD3);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0xF0), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0x08;\
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0x08);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0x25;\
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0x06);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x1F), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0x20;\
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0x30);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0xF0), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);\
}

#define TEST_SBC_A_d8(opcode) \
TEST_METHOD(SBC_A_d8)\
{\
	u8& A_reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	flags.F = 0x00;\
	flags.flags.C = 1;\
	A_reg = 0x05;\
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0xD3);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0xEF), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	flags.F = 0x00;\
	A_reg = 0x08;\
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0x08);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
}

#define TEST_AND_A_d8(opcode) \
TEST_METHOD(AND_A_d8)\
{\
	u8& A_Reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	A_Reg = 0x05;\
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0x0B);\
	flags.F = 0x00;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x01), A_Reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	A_Reg = 0x0A;\
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0x05);\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_Reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
}

#define TEST_XOR_A_d8(opcode) \
TEST_METHOD(XOR_A_d8)\
{\
	u8& A_Reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	A_Reg = 0x05;\
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0x0B);\
	flags.F = 0x00;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x0E), A_Reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	A_Reg = 0x0A;\
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0x0A);\
	flags.F = 0x00;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_Reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
}


#define TEST_OR_A_d8(opcode) \
TEST_METHOD(OR_A_d8)\
{\
	u8& A_Reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];\
	flags& flags = cpu->getRegistriesRef().getFlagsRef();\
	\
	A_Reg = 0x15;\
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0x5B);\
	flags.F = 0x00;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x05F), A_Reg);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
	\
	A_Reg = 0x00;\
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0x00);\
	flags.F = 0x01;\
	cpu->executeOpcode(opcode);\
	Assert::AreEqual(static_cast<u8>(0x00), A_Reg);\
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.N);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);\
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);\
}


#define TEST_CP_A_d8(opcode) \
TEST_METHOD(CP_A_d8)\
{\
	u8& A_reg = cpu->getRegistriesRef().getRegistriesRef()[Reg::A]; \
	flags& flags = cpu->getRegistriesRef().getFlagsRef(); \
	\
	flags.F = 0x00;\
	A_reg = 0xFE; \
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0x0E);\
	cpu->executeOpcode(opcode); \
	Assert::AreEqual(static_cast<u8>(0xFE), A_reg); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z); \
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.N); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C); \
	\
	A_reg = 0x08; \
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0x08);\
	cpu->executeOpcode(opcode); \
	Assert::AreEqual(static_cast<u8>(0x08), A_reg); \
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C); \
	\
	A_reg = 0x25; \
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0x06);\
	cpu->executeOpcode(opcode); \
	Assert::AreEqual(static_cast<u8>(0x25), A_reg); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z); \
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.H); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C); \
	\
	A_reg = 0x20; \
	cpu->getRegistriesRef().getPCRef() = 0x8000;\
	bus->write(0x8001, 0x30);\
	cpu->executeOpcode(opcode); \
	Assert::AreEqual(static_cast<u8>(0x20), A_reg); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z); \
	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H); \
	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C); \
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{

	TEST_CLASS(I8BitLogicTests)
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

		TEST_INC_R(B, 0x04);
		TEST_INC_R(C, 0x0C);
		TEST_INC_R(D, 0x14);
		TEST_INC_R(E, 0x1C);
		TEST_INC_R(H, 0x24);
		TEST_INC_R(L, 0x2C);
		TEST_INC_R(A, 0x3C);

		TEST_DEC_R(B, 0x05);
		TEST_DEC_R(C, 0x0D);
		TEST_DEC_R(D, 0x15);
		TEST_DEC_R(E, 0x1D);
		TEST_DEC_R(H, 0x25);
		TEST_DEC_R(L, 0x2D);
		TEST_DEC_R(A, 0x3D);

		TEST_CPL(     0x2F);

		TEST_INC_pHLq(0x34);
		TEST_DEC_pHLq(0x35);

		TEST_SCF(     0x37);
		TEST_CCF(	  0x3F);

		TEST_ADD_A_R(B, 0x80);
		TEST_ADD_A_R(C, 0x81);
		TEST_ADD_A_R(D, 0x82);
		TEST_ADD_A_R(E, 0x83);
		TEST_ADD_A_R(H, 0x84);
		TEST_ADD_A_R(L, 0x85);
		TEST_ADD_A_pHLq(0x86);
		TEST_ADD_A_R(A, 0x87); // TODO verifier ce test unit au niveau des flags

		TEST_ADC_A_R(B, 0x88);
		TEST_ADC_A_R(C, 0x89);
		TEST_ADC_A_R(D, 0x8A);
		TEST_ADC_A_R(E, 0x8B);
		TEST_ADC_A_R(H, 0x8C);
		TEST_ADC_A_R(L, 0x8D);
		TEST_ADC_A_pHLq(0x8E);
		TEST_ADC_A_R(A, 0x8F); 

		TEST_SUB_A_R(B, 0x90);
		TEST_SUB_A_R(C, 0x91);
		TEST_SUB_A_R(D, 0x92);
		TEST_SUB_A_R(E, 0x93);
		TEST_SUB_A_R(H, 0x94);
		TEST_SUB_A_R(L, 0x95);
		TEST_SUB_A_pHLq(0x96);
		TEST_SUB_A_R(A, 0x97);

		TEST_SBC_A_R(B, 0x98);
		TEST_SBC_A_R(C, 0x99);
		TEST_SBC_A_R(D, 0x9A);
		TEST_SBC_A_R(E, 0x9B);
		TEST_SBC_A_R(H, 0x9C);
		TEST_SBC_A_R(L, 0x9D);
		TEST_SBC_A_pHLq(0x9E);
		TEST_SBC_A_R(A, 0x9F);

		TEST_AND_A_R(B, 0xA0);
		TEST_AND_A_R(C, 0xA1);
		TEST_AND_A_R(D, 0xA2);
		TEST_AND_A_R(E, 0xA3);
		TEST_AND_A_R(H, 0xA4);
		TEST_AND_A_R(L, 0xA5);
		TEST_AND_A_pHLq(0xA6);
		TEST_AND_A_A(   0xA7);

		TEST_XOR_A_R(B, 0xA8);
		TEST_XOR_A_R(C, 0xA9);
		TEST_XOR_A_R(D, 0xAA);
		TEST_XOR_A_R(E, 0xAB);
		TEST_XOR_A_R(H, 0xAC);
		TEST_XOR_A_R(L, 0xAD);
		TEST_XOR_A_pHLq(0xAE);
		TEST_XOR_A_A(   0xAF);

		TEST_OR_A_R(B, 0xB0);
		TEST_OR_A_R(C, 0xB1);
		TEST_OR_A_R(D, 0xB2);
		TEST_OR_A_R(E, 0xB3);
		TEST_OR_A_R(H, 0xB4);
		TEST_OR_A_R(L, 0xB5);
		TEST_OR_A_pHLq(0xB6);
		TEST_OR_A_A(   0xB7);

		TEST_CP_A_R(B, 0xB8);
		TEST_CP_A_R(C, 0xB9);
		TEST_CP_A_R(D, 0xBA);
		TEST_CP_A_R(E, 0xBB);
		TEST_CP_A_R(H, 0xBC);
		TEST_CP_A_R(L, 0xBD);
		TEST_CP_A_pHLq(0xBE);
		TEST_CP_A_A(   0xBF);
						  
		TEST_ADD_A_d8(0xC6);
		TEST_ADC_A_d8(0xCE);
		TEST_SUB_A_d8(0xD6);
		TEST_SBC_A_d8(0xDE);
		TEST_AND_A_d8(0xE6);
		TEST_XOR_A_d8(0xEE);
		TEST_OR_A_d8( 0xF6);
		TEST_CP_A_d8( 0xFE);
		
		TEST_METHOD(DAA)
		{
			u8& A = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];
			flags& flags = cpu->getRegistriesRef().getFlagsRef();
			flags.F = 0x00;

			TEST_DAA(0x47, 0x48, 0x00, 0x00, 0x00, cpu->executeOpcode(0x3C)); // INC A
			TEST_DAA(0x09, 0x10, 0x00, 0x00, 0x00, cpu->executeOpcode(0x3C)); // INC A
			TEST_DAA(0x99, 0x00, 0x01, 0x00, 0x01, cpu->executeOpcode(0x3C)); // INC A
			TEST_DAA(0xC3, 0x24, 0x00, 0x00, 0x01, cpu->executeOpcode(0x3C)); // INC A

			A = 0xCB; flags.flags.H = 1;
			TEST_DAA(0xCB, 0x31, 0x00, 0x00, 0x01);

			flags.F = 0x00;
			TEST_DAA(0x47, 0x46, 0x00, 0x00, 0x00, cpu->executeOpcode(0x3D)); // DEC A
			TEST_DAA(0x40, 0x39, 0x00, 0x00, 0x00, cpu->executeOpcode(0x3D)); // DEC A
			TEST_DAA(0x10, 0x09, 0x00, 0x00, 0x00, cpu->executeOpcode(0x3D)); // DEC A

			A = 0x00; flags.flags.C = 1;
			TEST_DAA(0x00, 0x99, 0x00, 0x00, 0x01, cpu->executeOpcode(0x3D)); // DEC A

			A = 0xCB; flags.flags.H = 1;
			TEST_DAA(0xCB, 0x65, 0x00, 0x00, 0x01);

			TEST_DAA(0xE5, 0x85, 0x00, 0x00, 0x01);
		}
		//TEST_METHOD(DAA_old)
		//{

		//	u8& A = cpu->getRegistriesRef().getRegistriesRef()[Reg::A];
		//	flags& flags = cpu->getRegistriesRef().getFlagsRef(); \
		//	flags.F = 0x00;
		//	
		//	A = 0x47;
		//	cpu->executeOpcode(0x3C);	//INC A
		//	cpu->executeOpcode(0x27);	//DAA
		//	Assert::AreEqual(static_cast<u8>(0x48), A);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);

		//	A = 0x09;
		//	cpu->executeOpcode(0x3C);	//INC A
		//	cpu->executeOpcode(0x27);	//DAA
		//	Assert::AreEqual(static_cast<u8>(0x10), A);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);

		//	A = 0x99;
		//	cpu->executeOpcode(0x3C);	//INC A
		//	cpu->executeOpcode(0x27);	//DAA
		//	Assert::AreEqual(static_cast<u8>(0x00), A);
		//	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.Z);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);
		//	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);

		//	A = 0xC3;
		//	cpu->executeOpcode(0x3C);	//INC A
		//	cpu->executeOpcode(0x27);	//DAA
		//	Assert::AreEqual(static_cast<u8>(0x24), A);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);
		//	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);

		//	A = 0xCB;
		//	flags.flags.H = 1;
		//	cpu->executeOpcode(0x27);	//DAA
		//	Assert::AreEqual(static_cast<u8>(0x31), A);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);
		//	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);

		//	flags.F = 0x00;
		//	A = 0x47;
		//	cpu->executeOpcode(0x3D);	//DEC A
		//	cpu->executeOpcode(0x27);	//DAA
		//	Assert::AreEqual(static_cast<u8>(0x46), A);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);

		//	A = 0x40;
		//	cpu->executeOpcode(0x3D);	//DEC A
		//	cpu->executeOpcode(0x27);	//DAA
		//	Assert::AreEqual(static_cast<u8>(0x39), A);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);

		//	A = 0x10;
		//	cpu->executeOpcode(0x3D);	//DEC A
		//	cpu->executeOpcode(0x27);	//DAA
		//	Assert::AreEqual(static_cast<u8>(0x09), A);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.C);

		//	A = 0x00;
		//	flags.flags.C = 1;
		//	cpu->executeOpcode(0x3D);	//DEC A
		//	cpu->executeOpcode(0x27);	//DAA
		//	Assert::AreEqual(static_cast<u8>(0x99), A);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);
		//	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);

		//	flags.flags.H = 1;
		//	A = 0xCB;
		//	cpu->executeOpcode(0x27);	//DAA
		//	Assert::AreEqual(static_cast<u8>(0x65), A);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);
		//	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);

		//	A = 0xE5;
		//	cpu->executeOpcode(0x27);	//DAA
		//	Assert::AreEqual(static_cast<u8>(0x85), A);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.Z);
		//	Assert::AreEqual(static_cast <u8>(0x00), flags.flags.H);
		//	Assert::AreEqual(static_cast <u8>(0x01), flags.flags.C);
		//}
	};

	std::shared_ptr<Memory> I8BitLogicTests::memory = nullptr;
	std::shared_ptr<Cartridge> I8BitLogicTests::cartridge = nullptr;
	std::shared_ptr<Bus> I8BitLogicTests::bus = nullptr;
	std::shared_ptr<CPU> I8BitLogicTests::cpu = nullptr;
	std::shared_ptr<PPU> I8BitLogicTests::ppu = nullptr;
}