#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"
#include "..\PPU\PPU.h"
#include "..\Utils\Utils.h"


#define TEST_BIT(n, reg, opcode) \
TEST_METHOD(BIT_##n##c##reg) \
{ \
    u8& r = cpu->getRegistriesRef().getRegistriesRef()[Reg::reg]; \
    r = (1 << n); \
    cpu->executeOpcodeCB(opcode); \
    Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.Z)); \
    Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.H)); \
    Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N)); \
    r = 0x00; \
    cpu->executeOpcodeCB(opcode); \
    Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.Z)); \
    Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.H)); \
    Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N)); \
}

#define TEST_BIT_pHLq(n, opcode) \
TEST_METHOD(BIT_##n##cpHLq) \
{ \
	bus->write(0x8000, (1 << n));\
	cpu->getRegistriesRef().getHLRef() = 0x8000;\
    cpu->executeOpcodeCB(opcode); \
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));\
	bus->write(0x8000, 0b00000000);\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));\
	Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.H));\
	Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));\
}

#define TEST_RES(bit, reg, opcode)\
TEST_METHOD(RES_##bit##c##reg)\
{\
    u8& r = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg];\
    r = 0xFF;\
    cpu->executeOpcodeCB(opcode);\
    Assert::AreEqual(static_cast<u8>(0xFF & ~(1 << bit)), r);\
    \
    r = 0xFF & ~(1 << bit);\
    cpu->executeOpcodeCB(opcode);\
    Assert::AreEqual(static_cast<u8>(0xFF & ~(1 << bit)), r);\
}

#define TEST_RES_pHLq(bit, opcode) \
TEST_METHOD(RES_##bit##_pHLq) \
{ \
	cpu->getRegistriesRef().getHLRef() = 0xC000;\
	cpu->writeMemory(0xC000, 0xFF);\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0xFF & ~(1 << bit)), cpu->readMemory(0xC000));\
	\
	cpu->writeMemory(0xC000, 0xFF & ~(1 << bit));\
	cpu->executeOpcodeCB(opcode);\
	Assert::AreEqual(static_cast<u8>(0xFF & ~(1 << bit)), cpu->readMemory(0xC000));\
}

#define TEST_SET(bit, reg, opcode) \
TEST_METHOD(SET_##bit##c##reg) \
{ \
    u8& r = cpu->getRegistriesRef().getRegistriesRef()[Reg::##reg]; \
    r = 0x00; \
    cpu->executeOpcodeCB(opcode); \
    Assert::AreEqual(static_cast<u8>(1 << bit), r); \
    \
    r = 0x00 | (1 << bit); \
    cpu->executeOpcodeCB(opcode); \
    Assert::AreEqual(static_cast<u8>(1 << bit), r); \
}


#define TEST_SET_pHLq(bit, opcode) \
TEST_METHOD(SET_##bit##cpHLq) \
{ \
    cpu->getRegistriesRef().getHLRef() = 0xC000; \
    cpu->writeMemory(0xC000, 0x00); \
    cpu->executeOpcodeCB(opcode); \
    Assert::AreEqual(static_cast<u8>(1 << bit), cpu->readMemory(0xC000)); \
    \
    cpu->writeMemory(0xC000, (1 << bit)); \
    cpu->executeOpcodeCB(opcode); \
    Assert::AreEqual(static_cast<u8>(1 << bit), cpu->readMemory(0xC000)); \
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{
	TEST_CLASS(I1BitOperationTests)
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

		//BIT
		TEST_BIT(0, B, 0x40);
		TEST_BIT(0, C, 0x41);
		TEST_BIT(0, D, 0x42);
		TEST_BIT(0, E, 0x43);
		TEST_BIT(0, H, 0x44);
		TEST_BIT(0, L, 0x45);
		TEST_BIT(0, A, 0x47);

		TEST_BIT(1, B, 0x48);
		TEST_BIT(1, C, 0x49);
		TEST_BIT(1, D, 0x4A);
		TEST_BIT(1, E, 0x4B);
		TEST_BIT(1, H, 0x4C);
		TEST_BIT(1, L, 0x4D);
		TEST_BIT(1, A, 0x4F);

		TEST_BIT(2, B, 0x50);
		TEST_BIT(2, C, 0x51);
		TEST_BIT(2, D, 0x52);
		TEST_BIT(2, E, 0x53);
		TEST_BIT(2, H, 0x54);
		TEST_BIT(2, L, 0x55);
		TEST_BIT(2, A, 0x57);

		TEST_BIT(3, B, 0x58);
		TEST_BIT(3, C, 0x59);
		TEST_BIT(3, D, 0x5A);
		TEST_BIT(3, E, 0x5B);
		TEST_BIT(3, H, 0x5C);
		TEST_BIT(3, L, 0x5D);
		TEST_BIT(3, A, 0x5F);

		TEST_BIT(4, B, 0x60);
		TEST_BIT(4, C, 0x61);
		TEST_BIT(4, D, 0x62);
		TEST_BIT(4, E, 0x63);
		TEST_BIT(4, H, 0x64);
		TEST_BIT(4, L, 0x65);
		TEST_BIT(4, A, 0x67);

		TEST_BIT(5, B, 0x68);
		TEST_BIT(5, C, 0x69);
		TEST_BIT(5, D, 0x6A);
		TEST_BIT(5, E, 0x6B);
		TEST_BIT(5, H, 0x6C);
		TEST_BIT(5, L, 0x6D);
		TEST_BIT(5, A, 0x6F);

		TEST_BIT(6, B, 0x70);
		TEST_BIT(6, C, 0x71);
		TEST_BIT(6, D, 0x72);
		TEST_BIT(6, E, 0x73);
		TEST_BIT(6, H, 0x74);
		TEST_BIT(6, L, 0x75);
		TEST_BIT(6, A, 0x77);

		TEST_BIT(7, B, 0x78);
		TEST_BIT(7, C, 0x79);
		TEST_BIT(7, D, 0x7A);
		TEST_BIT(7, E, 0x7B);
		TEST_BIT(7, H, 0x7C);
		TEST_BIT(7, L, 0x7D);
		TEST_BIT(7, A, 0x7F);

		TEST_BIT_pHLq(0, 0x46);
		TEST_BIT_pHLq(1, 0x4E);
		TEST_BIT_pHLq(2, 0x56);
		TEST_BIT_pHLq(3, 0x5E);
		TEST_BIT_pHLq(4, 0x66);
		TEST_BIT_pHLq(5, 0x6E);
		TEST_BIT_pHLq(6, 0x76);
		TEST_BIT_pHLq(7, 0x7E);


		//RES
		TEST_RES(0, B, 0x80);
		TEST_RES(0, C, 0x81);
		TEST_RES(0, D, 0x82);
		TEST_RES(0, E, 0x83);
		TEST_RES(0, H, 0x84);
		TEST_RES(0, L, 0x85);
		TEST_RES(0, A, 0x87);

		TEST_RES(1, B, 0x88);
		TEST_RES(1, C, 0x89);
		TEST_RES(1, D, 0x8A);
		TEST_RES(1, E, 0x8B);
		TEST_RES(1, H, 0x8C);
		TEST_RES(1, L, 0x8D);
		TEST_RES(1, A, 0x8F);

		TEST_RES(2, B, 0x90);
		TEST_RES(2, C, 0x91);
		TEST_RES(2, D, 0x92);
		TEST_RES(2, E, 0x93);
		TEST_RES(2, H, 0x94);
		TEST_RES(2, L, 0x95);
		TEST_RES(2, A, 0x97);

		TEST_RES(3, B, 0x98);
		TEST_RES(3, C, 0x99);
		TEST_RES(3, D, 0x9A);
		TEST_RES(3, E, 0x9B);
		TEST_RES(3, H, 0x9C);
		TEST_RES(3, L, 0x9D);
		TEST_RES(3, A, 0x9F);

		TEST_RES(4, B, 0xA0);
		TEST_RES(4, C, 0xA1);
		TEST_RES(4, D, 0xA2);
		TEST_RES(4, E, 0xA3);
		TEST_RES(4, H, 0xA4);
		TEST_RES(4, L, 0xA5);
		TEST_RES(4, A, 0xA7);

		TEST_RES(5, B, 0xA8);
		TEST_RES(5, C, 0xA9);
		TEST_RES(5, D, 0xAA);
		TEST_RES(5, E, 0xAB);
		TEST_RES(5, H, 0xAC);
		TEST_RES(5, L, 0xAD);
		TEST_RES(5, A, 0xAF);

		TEST_RES(6, B, 0xB0);
		TEST_RES(6, C, 0xB1);
		TEST_RES(6, D, 0xB2);
		TEST_RES(6, E, 0xB3);
		TEST_RES(6, H, 0xB4);
		TEST_RES(6, L, 0xB5);
		TEST_RES(6, A, 0xB7);

		TEST_RES(7, B, 0xB8);
		TEST_RES(7, C, 0xB9);
		TEST_RES(7, D, 0xBA);
		TEST_RES(7, E, 0xBB);
		TEST_RES(7, H, 0xBC);
		TEST_RES(7, L, 0xBD);
		TEST_RES(7, A, 0xBF);

		TEST_RES_pHLq(0, 0x86);
		TEST_RES_pHLq(1, 0x8E);
		TEST_RES_pHLq(2, 0x96);
		TEST_RES_pHLq(3, 0x9E);
		TEST_RES_pHLq(4, 0xA6);
		TEST_RES_pHLq(5, 0xAE);
		TEST_RES_pHLq(6, 0xB6);
		TEST_RES_pHLq(7, 0xBE);

		//SET
		TEST_SET(0, B, 0xC0);
		TEST_SET(0, C, 0xC1);
		TEST_SET(0, D, 0xC2);
		TEST_SET(0, E, 0xC3);
		TEST_SET(0, H, 0xC4);
		TEST_SET(0, L, 0xC5);
		TEST_SET(0, A, 0xC7);

		TEST_SET(1, B, 0xC8);
		TEST_SET(1, C, 0xC9);
		TEST_SET(1, D, 0xCA);
		TEST_SET(1, E, 0xCB);
		TEST_SET(1, H, 0xCC);
		TEST_SET(1, L, 0xCD);
		TEST_SET(1, A, 0xCF);

		TEST_SET(2, B, 0xD0);
		TEST_SET(2, C, 0xD1);
		TEST_SET(2, D, 0xD2);
		TEST_SET(2, E, 0xD3);
		TEST_SET(2, H, 0xD4);
		TEST_SET(2, L, 0xD5);
		TEST_SET(2, A, 0xD7);

		TEST_SET(3, B, 0xD8);
		TEST_SET(3, C, 0xD9);
		TEST_SET(3, D, 0xDA);
		TEST_SET(3, E, 0xDB);
		TEST_SET(3, H, 0xDC);
		TEST_SET(3, L, 0xDD);
		TEST_SET(3, A, 0xDF);

		TEST_SET(4, B, 0xE0);
		TEST_SET(4, C, 0xE1);
		TEST_SET(4, D, 0xE2);
		TEST_SET(4, E, 0xE3);
		TEST_SET(4, H, 0xE4);
		TEST_SET(4, L, 0xE5);
		TEST_SET(4, A, 0xE7);

		TEST_SET(5, B, 0xE8);
		TEST_SET(5, C, 0xE9);
		TEST_SET(5, D, 0xEA);
		TEST_SET(5, E, 0xEB);
		TEST_SET(5, H, 0xEC);
		TEST_SET(5, L, 0xED);
		TEST_SET(5, A, 0xEF);

		TEST_SET(6, B, 0xF0);
		TEST_SET(6, C, 0xF1);
		TEST_SET(6, D, 0xF2);
		TEST_SET(6, E, 0xF3);
		TEST_SET(6, H, 0xF4);
		TEST_SET(6, L, 0xF5);
		TEST_SET(6, A, 0xF7);

		TEST_SET(7, B, 0xF8);
		TEST_SET(7, C, 0xF9);
		TEST_SET(7, D, 0xFA);
		TEST_SET(7, E, 0xFB);
		TEST_SET(7, H, 0xFC);
		TEST_SET(7, L, 0xFD);
		TEST_SET(7, A, 0xFF);

		TEST_SET_pHLq(0, 0xC6);
		TEST_SET_pHLq(1, 0xCE);
		TEST_SET_pHLq(2, 0xD6);
		TEST_SET_pHLq(3, 0xDE);
		TEST_SET_pHLq(4, 0xE6);
		TEST_SET_pHLq(5, 0xEE);
		TEST_SET_pHLq(6, 0xF6);
		TEST_SET_pHLq(7, 0xFE);
		
	};

	std::shared_ptr <Memory> I1BitOperationTests::memory = nullptr;
	std::shared_ptr <Cartridge> I1BitOperationTests::cartridge = nullptr;
	std::shared_ptr<Bus> I1BitOperationTests::bus = nullptr;
	std::shared_ptr<CPU> I1BitOperationTests::cpu = nullptr;
	std::shared_ptr<PPU> I1BitOperationTests::ppu = nullptr;


}