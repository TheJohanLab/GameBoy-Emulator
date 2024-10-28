#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"
#include "..\PPU\PPU.h"
#include "..\Utils\Utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{
	TEST_CLASS(I1BitOperationTests)
	{
	private:
		static std::shared_ptr <Bus> bus;
		static std::shared_ptr <PPU> ppu;
		static std::shared_ptr<CPU> cpu;

	public:

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			bus = std::make_shared<Bus>();
			ppu = std::make_shared<PPU>(bus, nullptr);
			cpu = std::make_shared<CPU>(bus, ppu);
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			
		}

		TEST_METHOD(BIT_bcr)
		{
			u8* A = cpu->getRegistries("A");
			*A = 0b00001000;
			cpu->executeOpcodeCB(0x67);
			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));
		
			cpu->executeOpcodeCB(0x5F);
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.Z));
			Assert::AreEqual(static_cast<u8>(0x01), static_cast<u8>(cpu->getFlagRegistry()->flags.H));
			Assert::AreEqual(static_cast<u8>(0x00), static_cast<u8>(cpu->getFlagRegistry()->flags.N));

		}

		TEST_METHOD(RES_bcr)
		{
			u8* A = cpu->getRegistries("A");
			*A = 0b11111111;
			cpu->executeOpcodeCB(0x9F);
			Assert::AreEqual(static_cast<u8>(0b11110111), *A);

			u8* B = cpu->getRegistries("B");
			*B = 0b11110111;
			cpu->executeOpcodeCB(0x98);
			Assert::AreEqual(static_cast<u8>(0b11110111), *B);
		}

		TEST_METHOD(RES_bcpHLq)
		{
			combinedRegistries* HL = cpu->getCombinedRegistries("HL");
			cpu->writeMemory(0xC000, 0xFF);
			cpu->setCombinedRegistries("HL", 0xC000);
			cpu->executeOpcodeCB(0xA6);
			Assert::AreEqual(static_cast<u8>(0b11101111), cpu->readMemory(0xC000));
		}

		TEST_METHOD(SET_bcr)
		{
			u8* A = cpu->getRegistries("A");
			*A = 0b00000000;
			cpu->executeOpcodeCB(0xF7);
			Assert::AreEqual(static_cast<u8>(0b01000000), *A);

			u8* B = cpu->getRegistries("B");
			*B = 0b01000000;
			cpu->executeOpcodeCB(0xF0);
			Assert::AreEqual(static_cast<u8>(0b01000000), *B);
		}

		TEST_METHOD(SET_bcpHLq)
		{
			combinedRegistries* HL = cpu->getCombinedRegistries("HL");
			cpu->writeMemory(0xC002, 0x00);
			cpu->setCombinedRegistries("HL", 0xC002);
			cpu->executeOpcodeCB(0xE6);
			Assert::AreEqual(static_cast<u8>(0b00010000), cpu->readMemory(0xC002));
		}
		
	};

	std::shared_ptr<Bus> I1BitOperationTests::bus = nullptr;
	std::shared_ptr<CPU> I1BitOperationTests::cpu = nullptr;
	std::shared_ptr<PPU> I1BitOperationTests::ppu = nullptr;
}