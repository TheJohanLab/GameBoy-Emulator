#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{

	TEST_CLASS(I16BitLoadTests)
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

		TEST_METHOD(LD_RRcd16)
		{

			combinedRegistries* BC = cpu->getCombinedRegistries("BC");

			u16* PC = cpu->getPC();
			*PC = 0xc000;
			bus->write(0xC001, 0xA1); //LSB
			bus->write(0xC002, 0xB2); //MSB
			
			BC->setValue(0x0000);
			Assert::AreEqual(static_cast<u16>(0x0000), BC->getValue());

			cpu->executeOpcode(0x01);
			Assert::AreEqual(static_cast<u16>(0xB2A1), BC->getValue());
		}

		TEST_METHOD(LD_Rcd8)
		{
			u8* B = cpu->getRegistries("B");

			u16* PC = cpu->getPC();
			*PC = 0xC000;
			cpu->writeMemory(0xC001, 0x0F);
			cpu->executeOpcode(0x06);

			Assert::AreEqual(static_cast<u8>(0x0F), *B);
		}

	};

	Bus* I16BitLoadTests::bus = nullptr;
	CPU* I16BitLoadTests::cpu = nullptr;
}
