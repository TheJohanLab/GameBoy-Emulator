#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"
#include "..\PPU\PPU.h"
#include "..\Utils\Utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{

	TEST_CLASS(I16BitLogicTests)
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

		TEST_METHOD(INC_RR)
		{
			combinedRegistries* BC = cpu->getCombinedRegistries("BC");
			
			u8* B = cpu->getRegistries("B");
			u8* C = cpu->getRegistries("C");

			cpu->setCombinedRegistries("BC", 0x1234);
			cpu->executeOpcode(0x03);

			Assert::AreEqual(static_cast<u8>(0x12), *B);
			Assert::AreEqual(static_cast <u8>(0x35), *C);

			BC->setValue(0x12FF);
			cpu->executeOpcode(0x03);
			Assert::AreEqual(static_cast<u8>(0x13), *B);
			Assert::AreEqual(static_cast <u8>(0x00), *C);

			BC->setValue(0xFFFF);
			cpu->executeOpcode(0x03);
			Assert::AreEqual(static_cast<u8>(0x00), *B);
			Assert::AreEqual(static_cast <u8>(0x00), *C);

		}

		TEST_METHOD(DEC_RR)
		{
			combinedRegistries* BC = cpu->getCombinedRegistries("BC");
			u8* B = cpu->getRegistries("B");
			u8* C = cpu->getRegistries("C");

			BC->setValue(0x1234);
			cpu->executeOpcode(0x0B);

			Assert::AreEqual(static_cast<u8>(0x12), *B);
			Assert::AreEqual(static_cast <u8>(0x33), *C);

			BC->setValue(0x1200);
			cpu->executeOpcode(0x0B);
			Assert::AreEqual(static_cast<u8>(0x11), *B);
			Assert::AreEqual(static_cast <u8>(0xFF), *C);

			BC->setValue(0x0000);
			cpu->executeOpcode(0x0B);
			Assert::AreEqual(static_cast<u8>(0xFF), *B);
			Assert::AreEqual(static_cast <u8>(0xFF), *C);


		}

		TEST_METHOD(ADD_HLcRR)
		{

			combinedRegistries* BC = cpu->getCombinedRegistries("BC");
			combinedRegistries* HL = cpu->getCombinedRegistries("HL");
			u8* B = cpu->getRegistries("B");
			u8* C = cpu->getRegistries("C");
			u8* H = cpu->getRegistries("H");
			u8* L = cpu->getRegistries("L");
			flags* flags = cpu->getFlagRegistry(); 
			flags->flags.Z = 1;
			flags->flags.N = 1;
			flags->flags.H = 0;
			flags->flags.C = 0;

			BC->setValue(0x0002);
			HL->setValue(0x0008);
			cpu->executeOpcode(0x09);
			Assert::AreEqual(static_cast<u8>(0x00), *B);
			Assert::AreEqual(static_cast<u8>(0x02), *C);
			Assert::AreEqual(static_cast<u16>(0x000A), HL->getValue());
			Assert::AreEqual(static_cast<u8>(0x00), *H);
			Assert::AreEqual(static_cast<u8>(0x0A), *L);
			Assert::AreEqual(static_cast<u8>(0x00), *HL->getHighRegistry());
			Assert::AreEqual(static_cast<u8>(0x0A), *HL->getLowRegistry());
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.N);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);

			BC->setValue(0x0005);
			HL->setValue(0x0FFB);
			flags->flags.Z = 0;
			cpu->executeOpcode(0x09);
			Assert::AreEqual(static_cast<u8>(0x00), *B);
			Assert::AreEqual(static_cast<u8>(0x05), *C);
			Assert::AreEqual(static_cast<u16>(0x1000), HL->getValue());
			Assert::AreEqual(static_cast<u8>(0x10), *H);
			Assert::AreEqual(static_cast<u8>(0x00), *L);
			Assert::AreEqual(static_cast<u8>(0x10), *HL->getHighRegistry());
			Assert::AreEqual(static_cast<u8>(0x00), *HL->getLowRegistry());
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);

			BC->setValue(0x0002);
			HL->setValue(0xFFFE);
			cpu->executeOpcode(0x09);
			Assert::AreEqual(static_cast<u16>(0x0000), HL->getValue());
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.C);
		}

		
	};
	std::shared_ptr<Memory> I16BitLogicTests::memory = nullptr;
	std::shared_ptr<Cartridge> I16BitLogicTests::cartridge = nullptr;
	std::shared_ptr<Bus> I16BitLogicTests::bus = nullptr;
	std::shared_ptr<CPU> I16BitLogicTests::cpu = nullptr;
	std::shared_ptr<PPU> I16BitLogicTests::ppu = nullptr;
}