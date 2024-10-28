#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"
#include "..\PPU\PPU.h"
#include "..\Utils\Utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{

	TEST_CLASS(ICPUControlTests)
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

	std::shared_ptr<Bus> ICPUControlTests::bus = nullptr;
	std::shared_ptr<CPU> ICPUControlTests::cpu = nullptr;
	std::shared_ptr<PPU> ICPUControlTests::ppu = nullptr;
}