#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"
#include "..\PPU\PPU.h"
#include "..\Utils\Utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{

	TEST_CLASS(I8BitLoadTests)
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

		//TODO Verifier ce test avec un PC correct (Actuellement write dans HRAM)
		TEST_METHOD(LDH_pn8qA)
		{
			u8* A = cpu->getRegistries("A");
			u16* PC = cpu->getPC();

			cpu->setRegistries("A", 0xA8);
			*PC = 0x0082;

			cpu->executeOpcode(0xE0);

			u8 data = cpu->readMemory(0xFF83);

			Assert::AreEqual(static_cast<u8>(0xA8), data);
		}

		//TODO Verifier ce test avec un PC correct (Actuellement write dans HRAM)
		TEST_METHOD(LDH_pCqcA)
		{
			u8* A = cpu->getRegistries("A");
			u8* C = cpu->getRegistries("C");

			cpu->setRegistries("A", 0xA9);
			cpu->setRegistries("C", 0x84);

			cpu->executeOpcode(0xE2);

			u8 data = cpu->readMemory(0xFF84);

			Assert::AreEqual(static_cast<u8>(0xA9), data);
		}

		TEST_METHOD(LD_pa16qcA)
		{
			u8* A = cpu->getRegistries("A");
			u16* PC = cpu->getPC();

			cpu->setRegistries("A", 0xAB);
			*PC = 0xC00A;

			cpu->executeOpcode(0xEA);

			u8 data = cpu->readMemory(0xC00B);

			Assert::AreEqual(static_cast<u8>(0xAB), data);
		}

		//TODO Verifier ce test avec un PC correct (Actuellement write dans HRAM)
		TEST_METHOD(LDH_Acpa8q)
		{
			u8* A = cpu->getRegistries("A");
			u16* PC = cpu->getPC();

			cpu->setRegistries("A", 0x00);
			*PC = 0x0083;
			cpu->writeMemory(0xFF84, 0xAB);

			cpu->executeOpcode(0xF0);

			Assert::AreEqual(static_cast<u8>(0xAB), *A);
		}

		//TODO Verifier ce test avec un PC correct (Actuellement write dans HRAM)
		TEST_METHOD(LDH_AcpCq)
		{
			u8* A = cpu->getRegistries("A");
			u8* C = cpu->getRegistries("C");

			cpu->setRegistries("A", 0x00);
			cpu->setRegistries("C", 0x85);
			cpu->writeMemory(0xFF85, 0xAC);

			cpu->executeOpcode(0xF2);


			Assert::AreEqual(static_cast<u8>(0xAC), *A);
		}

		TEST_METHOD(LD_Acpa16q)
		{
			u8* A = cpu->getRegistries("A");
			u16* PC = cpu->getPC();

			cpu->setRegistries("A", 0x00);
			*PC = 0xC00A;
			cpu->writeMemory(0xC00B, 0xAD);

			cpu->executeOpcode(0xFA);

			Assert::AreEqual(static_cast<u8>(0xAD), *A);
		}
	};
	
	std::shared_ptr<Memory> I8BitLoadTests::memory = nullptr;
	std::shared_ptr<Cartridge> I8BitLoadTests::cartridge = nullptr;
	std::shared_ptr<Bus> I8BitLoadTests::bus = nullptr;
	std::shared_ptr<CPU> I8BitLoadTests::cpu = nullptr;
	std::shared_ptr<PPU> I8BitLoadTests::ppu = nullptr;
}
