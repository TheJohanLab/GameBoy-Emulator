#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{

	TEST_CLASS(ICPUControlTests)
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


		TEST_METHOD(DI)
		{
			cpu->setIMEFlag();
			cpu->executeOpcode(0xF3);
			Assert::AreEqual(static_cast<u8>(0x00), cpu->getIMEFlag());

			cpu->clearIMEFlag();
			cpu->executeOpcode(0xF3);
			Assert::AreEqual(static_cast<u8>(0x00), cpu->getIMEFlag());
		}

		
		TEST_METHOD(EI)
		{
			cpu->setIMEFlag();
			cpu->executeOpcode(0xFB);
			Assert::AreEqual(static_cast<u8>(0x01), cpu->getIMEFlag());

			cpu->clearIMEFlag();
			cpu->executeOpcode(0xFB);
			Assert::AreEqual(static_cast<u8>(0x01), cpu->getIMEFlag());
		}

		//TODO
		TEST_METHOD(HALT)
		{

		}

		//TODO
		TEST_METHOD(STOP)
		{

		}
		

	};

	Bus* ICPUControlTests::bus = nullptr;
	CPU* ICPUControlTests::cpu = nullptr;
}