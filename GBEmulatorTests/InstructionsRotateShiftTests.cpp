#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"
#include "..\PPU\PPU.h"
#include "..\Utils\Utils.h"

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

		TEST_METHOD(RLC_r)
		{
			u8* A = cpu->getRegistries("A");
			*A = 0b11110000;
			cpu->executeOpcodeCB(0x07);
			Assert::AreEqual(static_cast<u8>(0b11100001), *A);

			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.C));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

			u8* B = cpu->getRegistries("B");
			*B = 0b01110001;
			cpu->executeOpcodeCB(0x00);
			Assert::AreEqual(static_cast<u8>(0b11100010), *B);

			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.C));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

			u8* C = cpu->getRegistries("C");
			*C = 0b00000000;
			cpu->executeOpcodeCB(0x01);
			Assert::AreEqual(static_cast<u8>(0b00000000), *C);

			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.C));
			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

		}

		TEST_METHOD(RRC_r)
		{
			u8* A = cpu->getRegistries("A");
			*A = 0b00001111;
			cpu->executeOpcodeCB(0x0F);
			Assert::AreEqual(static_cast<u8>(0b10000111), *A);

			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.C));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

			u8* B = cpu->getRegistries("B");
			*B = 0b00001110;
			cpu->executeOpcodeCB(0x08);
			Assert::AreEqual(static_cast<u8>(0b00000111), *B);

			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.C));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

			u8* C = cpu->getRegistries("C");
			*C = 0b00000000;
			cpu->executeOpcodeCB(0x09);
			Assert::AreEqual(static_cast<u8>(0b00000000), *C);

			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.C));
			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

		}

		TEST_METHOD(RL_r)
		{
			u8* A = cpu->getRegistries("A");
			*A = 0b11111111;
			cpu->getFlagRegistry()->flags.C = 0x00;
			cpu->executeOpcodeCB(0x17);
			Assert::AreEqual(static_cast<u8>(0b11111110), *A);
			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.C));

			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));


			u8* B = cpu->getRegistries("B");
			*B = 0b00000000;
			cpu->getFlagRegistry()->flags.C = 0x01;
			cpu->executeOpcodeCB(0x10);
			Assert::AreEqual(static_cast<u8>(0b00000001), *B);
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.C));

			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

			u8* C = cpu->getRegistries("C");
			*C = 0b00000000;
			cpu->getFlagRegistry()->flags.C = 0x00;
			cpu->executeOpcodeCB(0x11);
			Assert::AreEqual(static_cast<u8>(0b00000000), *C);
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.C));

			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

		}

		TEST_METHOD(RR_r)
		{
			u8* A = cpu->getRegistries("A");
			*A = 0b11111111;
			cpu->getFlagRegistry()->flags.C = 0x00;
			cpu->executeOpcodeCB(0x1F);
			Assert::AreEqual(static_cast<u8>(0b01111111), *A);
			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.C));

			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));


			u8* B = cpu->getRegistries("B");
			*B = 0b00000000;
			cpu->getFlagRegistry()->flags.C = 0x01;
			cpu->executeOpcodeCB(0x18);
			Assert::AreEqual(static_cast<u8>(0b10000000), *B);
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.C));

			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

			u8* C = cpu->getRegistries("C");
			*C = 0b00000000;
			cpu->getFlagRegistry()->flags.C = 0x00;
			cpu->executeOpcodeCB(0x19);
			Assert::AreEqual(static_cast<u8>(0b00000000), *C);
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.C));

			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

		}

		TEST_METHOD(SLA_r)
		{
			u8* A = cpu->getRegistries("A");
			*A = 0b11111111;
			cpu->executeOpcodeCB(0x27);
			Assert::AreEqual(static_cast<u8>(0b11111110), *A);
			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.C));

			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));


			u8* B = cpu->getRegistries("B");
			*B = 0b00000000;
			cpu->getFlagRegistry()->flags.C = 0x01;
			cpu->executeOpcodeCB(0x20);
			Assert::AreEqual(static_cast<u8>(0b00000000), *B);
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.C));

			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

			u8* C = cpu->getRegistries("C");
			*C = 0b00000000;
			cpu->getFlagRegistry()->flags.C = 0x00;
			cpu->executeOpcodeCB(0x21);
			Assert::AreEqual(static_cast<u8>(0b00000000), *C);
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.C));

			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

		}

		TEST_METHOD(SRA_r)
		{
			u8* A = cpu->getRegistries("A");
			*A = 0b11111111;
			cpu->executeOpcodeCB(0x2F);
			Assert::AreEqual(static_cast<u8>(0b11111111), *A);
			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.C));

			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

			u8* D = cpu->getRegistries("D");
			*D = 0b01111111;
			cpu->executeOpcodeCB(0x2A);
			Assert::AreEqual(static_cast<u8>(0b00111111), *D);
			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.C));

			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

			u8* C = cpu->getRegistries("C");
			*C = 0b00000000;
			cpu->getFlagRegistry()->flags.C = 0x00;
			cpu->executeOpcodeCB(0x29);
			Assert::AreEqual(static_cast<u8>(0b00000000), *C);
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.C));

			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

		}

		TEST_METHOD(SWAPr)
		{
			u8* A = cpu->getRegistries("A");
			*A = 0b10100101;
			cpu->executeOpcodeCB(0x37);
			Assert::AreEqual(static_cast<u8>(0b01011010), *A);
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.C));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

			u8* B = cpu->getRegistries("B");
			*B = 0b00000000;
			cpu->executeOpcodeCB(0x30);
			Assert::AreEqual(static_cast<u8>(0b00000000), *B);
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.C));
			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

		}

		TEST_METHOD(SRL_r)
		{
			u8* A = cpu->getRegistries("A");
			*A = 0b11111111;
			cpu->executeOpcodeCB(0x3F);
			Assert::AreEqual(static_cast<u8>(0b01111111), *A);
			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.C));

			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

			u8* D = cpu->getRegistries("D");
			*D = 0b01111111;
			cpu->executeOpcodeCB(0x3A);
			Assert::AreEqual(static_cast<u8>(0b00111111), *D);
			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.C));

			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

			u8* C = cpu->getRegistries("C");
			*C = 0b00000000;
			cpu->getFlagRegistry()->flags.C = 0x00;
			cpu->executeOpcodeCB(0x39);
			Assert::AreEqual(static_cast<u8>(0b00000000), *C);
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.C));

			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

		}

	};

	std::shared_ptr<Memory> IRotateShiftTests::memory = nullptr;
	std::shared_ptr<Cartridge> IRotateShiftTests::cartridge = nullptr;
	std::shared_ptr<Bus> IRotateShiftTests::bus = nullptr;
	std::shared_ptr<CPU> IRotateShiftTests::cpu = nullptr;
	std::shared_ptr<PPU> IRotateShiftTests::ppu = nullptr;
}