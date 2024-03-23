#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{
	TEST_CLASS(I1BitOperationTests)
	{
	private:
		static Bus* bus;
		static CPU* cpu;

	public:

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			bus = new Bus();
			cpu = new CPU(bus);
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			delete cpu;
			delete bus;
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

	Bus* I1BitOperationTests::bus = nullptr;
	CPU* I1BitOperationTests::cpu = nullptr;
}