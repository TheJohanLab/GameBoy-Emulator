#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{

	TEST_CLASS(I8BitLoadTests)
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

		TEST_METHOD(LD_pRRqcR)
		{

			u8* A = cpu->getRegistries("A");
			combinedRegistries* BC = cpu->getCombinedRegistries("BC");

			*A = 0x0F;
			cpu->setCombinedRegistries("BC", 0xC002);

			cpu->executeOpcode(0x02);

			u8 memoryValue = cpu->readMemory(*BC);
			Assert::AreEqual(static_cast<u8>(0x0F), memoryValue);
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

		TEST_METHOD(LD_RcpRRq)
		{

			u8* A = cpu->getRegistries("A");
			combinedRegistries* BC = cpu->getCombinedRegistries("BC");

			cpu->setCombinedRegistries("BC", 0xC001);
			cpu->writeMemory(0xC001, 0x0F);
			cpu->executeOpcode(0x0A);

			Assert::AreEqual(static_cast<u8>(0x0F), *A);
		}

		TEST_METHOD(LDI_pRRqcR)
		{
			u8* A = cpu->getRegistries("A");
			combinedRegistries* HL = cpu->getCombinedRegistries("HL");

			*A = 0x0F;
			cpu->setCombinedRegistries("HL", 0xC002);

			cpu->executeOpcode(0x22);

			u16 HLValue = HL->getValue();
			u8 memoryValue = cpu->readMemory(HLValue - 1);
			//u16 HLval = static_cast<u16>((*(HL->reg1) << 8) & 0xFF00 | (*(HL->reg2) & 0x00FF));
			Assert::AreEqual(static_cast<u8>(0x0F), memoryValue);
			Assert::AreEqual(static_cast<u16>(0xC003), HLValue);
		}


		TEST_METHOD(LDI_RcpRRq)
		{
			u8* A = cpu->getRegistries("A");
			combinedRegistries* HL = cpu->getCombinedRegistries("HL");

			cpu->setCombinedRegistries("HL", 0xC005);
			cpu->writeMemory(0xC005, 0x0F);

			cpu->executeOpcode(0x2A);

			u16 HLValue = HL->getValue();
			Assert::AreEqual(static_cast<u8>(0x0F), *A);
			Assert::AreEqual(static_cast<u16>(0xC006), HLValue);
		}

		TEST_METHOD(LDD_pRRqcR)
		{
			u8* A = cpu->getRegistries("A");
			combinedRegistries* HL = cpu->getCombinedRegistries("HL");

			*A = 0x08;
			cpu->setCombinedRegistries("HL", 0xC007);

			cpu->executeOpcode(0x32);

			u16 HLValue = HL->getValue();
			u8 memoryValue = cpu->readMemory(HLValue + 1);
			//u16 HLval = static_cast<u16>((*(HL->reg1) << 8) & 0xFF00 | (*(HL->reg2) & 0x00FF));
			Assert::AreEqual(static_cast<u8>(0x08), memoryValue);
			Assert::AreEqual(static_cast<u16>(0xC006), HLValue);
		}


		TEST_METHOD(LD_pRRqcd8)
		{
			combinedRegistries* HL = cpu->getCombinedRegistries("HL");

			u16* PC = cpu->getPC();
			*PC = 0xC007;
			cpu->writeMemory(*PC+1, 0x0A);

			HL->setValue(0xC009);
			cpu->executeOpcode(0x36);

			u8 data = cpu->readMemory(*HL);
			Assert::AreEqual(static_cast<u8>(0x0A), data);
		}
		
		TEST_METHOD(LDD_RcpRRq)
		{
			u8* A = cpu->getRegistries("A");
			combinedRegistries* HL = cpu->getCombinedRegistries("HL");

			cpu->setCombinedRegistries("HL", 0xC00A);
			cpu->writeMemory(*HL, 0x06);

			cpu->executeOpcode(0x3A);

			u16 HLValue = HL->getValue();
			Assert::AreEqual(static_cast<u8>(0x06), *A);
			Assert::AreEqual(static_cast<u16>(0xC009), HLValue);
		}
	};

	Bus* I8BitLoadTests::bus = nullptr;
	CPU* I8BitLoadTests::cpu = nullptr;
}
