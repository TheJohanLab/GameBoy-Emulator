#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{
	TEST_CLASS(IRotateShiftTests)
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

		TEST_METHOD(RLC_r)
		{
			u8* A = cpu->getRegistries("A");

			*A = 0b11110000;

			cpu->executeOpcodeCB(0x07);

			Assert::AreEqual(static_cast<u8>(0b11100001), *A);
		}
	};

	Bus* IRotateShiftTests::bus = nullptr;
	CPU* IRotateShiftTests::cpu = nullptr;
}