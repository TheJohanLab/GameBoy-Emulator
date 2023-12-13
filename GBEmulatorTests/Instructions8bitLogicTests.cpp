#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{

	TEST_CLASS(I8BitLogicTests)
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

		TEST_METHOD(INC_R)
		{
			u8* B_reg = cpu->getRegistries("B");
			flags* flags = cpu->getFlagRegistry();

			*B_reg = 0x03;
			cpu->executeOpcode(0x04);

			Assert::AreEqual(static_cast<u8>(0x04), *B_reg);
			Assert::AreEqual(static_cast < u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.N);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);

			*B_reg = 0x1F;
			cpu->executeOpcode(0x04);
			Assert::AreEqual(static_cast<u8>(0x20), *B_reg);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);

			*B_reg = 0xFF;
			cpu->executeOpcode(0x04);
			Assert::AreEqual(static_cast<u8>(0x00), *B_reg);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.Z);

		}

		TEST_METHOD(DEC_R)
		{
			u8* B_reg = cpu->getRegistries("B");
			flags* flags = cpu->getFlagRegistry();

			*B_reg = 0x03;
			cpu->executeOpcode(0x05);

			Assert::AreEqual(static_cast<u8>(0x02), *B_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.N);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);

			*B_reg = 0x10;
			cpu->executeOpcode(0x05);
			Assert::AreEqual(static_cast<u8>(0x0F), *B_reg);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);

			*B_reg = 0x01;
			cpu->executeOpcode(0x05);
			Assert::AreEqual(static_cast<u8>(0x00), *B_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.Z);

		}
	};

	Bus* I8BitLogicTests::bus = nullptr;
	CPU* I8BitLogicTests::cpu = nullptr;
}