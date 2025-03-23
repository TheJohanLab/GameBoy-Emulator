#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"
#include "..\PPU\PPU.h"
#include "..\Utils\Utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{

	TEST_CLASS(I16BitLoadTests)
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


		TEST_METHOD(POP_RR)
		{
			u16* SP = cpu->getSP();
			combinedRegistries* HL = cpu->getCombinedRegistries("HL");

			*SP = 0xC000;
			cpu->writeMemory(0xC000, 0x12);
			cpu->writeMemory(0xC001, 0x34);
			cpu->setCombinedRegistries("HL", 0x0000);

			cpu->executeOpcode(0xE1);

			Assert::AreEqual(static_cast<u16>(0xC002), *SP);
			Assert::AreEqual(static_cast<u8>(0x12), *HL->getLowRegistry());
			Assert::AreEqual(static_cast<u8>(0x34), *HL->getHighRegistry());

		}

		TEST_METHOD(PUSH_RR)
		{
			u16* SP = cpu->getSP();

			*SP = 0xC002;
			cpu->writeMemory(0xC000, 0x00);
			cpu->writeMemory(0xC001, 0x00);
			cpu->setCombinedRegistries("HL", 0x5678);

			cpu->executeOpcode(0xE5);

			Assert::AreEqual(static_cast<u16>(0xC000), *SP);
			Assert::AreEqual(static_cast<u8>(0x78), cpu->readMemory(0xC000));
			Assert::AreEqual(static_cast<u8>(0x56), cpu->readMemory(0xC001));

		}

		TEST_METHOD(PUSH_AF)
		{
			u16* SP = cpu->getSP();

			*SP = 0xC002;
			cpu->writeMemory(0xC000, 0x00);
			cpu->writeMemory(0xC001, 0x00);
			cpu->setCombinedRegistries("AF", 0x12A0);

			cpu->executeOpcode(0xF5);

			Assert::AreEqual(static_cast<u16>(0xC000), *SP);
			Assert::AreEqual(static_cast<u8>(0xA0), cpu->readMemory(0xC000));
			Assert::AreEqual(static_cast<u8>(0x12), cpu->readMemory(0xC001));

		}

		TEST_METHOD(POP_AF)
		{
			u16* SP = cpu->getSP();
			combinedRegistries* AF = cpu->getCombinedRegistries("AF");
			u8* A = cpu->getRegistries("A");
			flags* F = cpu->getFlagRegistry();

			*SP = 0xC000;
			cpu->writeMemory(0xC000, 0xF0); //Low
			cpu->writeMemory(0xC001, 0x34); //High
			cpu->setCombinedRegistries("AF", 0x0000);

			cpu->executeOpcode(0xF1);

			Assert::AreEqual(static_cast<u16>(0xC002), *SP);
			Assert::AreEqual(static_cast<u8>(0x34), *AF->getHighRegistry());
			Assert::AreEqual(static_cast<u8>(0xF0), *AF->getLowRegistry());
			Assert::AreEqual(static_cast<u8>(0x34), *A);
			Assert::AreEqual(static_cast<u8>(0xF0), F->F);
			Assert::AreEqual(static_cast<u8>(0x01), F->flags.C);
			Assert::AreEqual(static_cast<u8>(0x01), F->flags.H);
			Assert::AreEqual(static_cast<u8>(0x01), F->flags.N);
			Assert::AreEqual(static_cast<u8>(0x01), F->flags.Z);

		}


		//TODO verifier ce test avec des adresses correctes
		TEST_METHOD(LD_pa16qcSP)
		{
			u16* SP = cpu->getSP();
			u16* PC = cpu->getPC();

			*PC = 0xC000;
			*SP = 0x0102;

			cpu->executeOpcode(0x08);

			u8 data1 = cpu->readMemory(0xC001);
			u8 data2 = cpu->readMemory(0xC002);

			Assert::AreEqual(static_cast<u8>(0x02), data1);
			Assert::AreEqual(static_cast<u8>(0x01), data2);
		}


		//TODO Verifier cette instruction
		TEST_METHOD(LDHL_SPce8)
		{
			u16* PC = cpu->getPC();
			u16* SP = cpu->getSP();
			combinedRegistries* HL = cpu->getCombinedRegistries("HL");
			flags* flags = cpu->getFlagRegistry();

			*PC = 0xC002;
			*SP = 0x0001;
			cpu->writeMemory((*PC) + 1, 0x01);
			cpu->executeOpcode(0xF8);
			Assert::AreEqual(static_cast<u16>(0x0002),  HL->getValue());
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.N);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);

			*PC = 0xC002;
			*SP = 0x0009;
			cpu->writeMemory((*PC) + 1, 0xF8);
			cpu->executeOpcode(0xF8);
			Assert::AreEqual(static_cast<u16>(0x0001), HL->getValue());
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.N);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.C);

			*PC = 0xC002;
			*SP = 0x0001;
			cpu->writeMemory((*PC) + 1, 0x0F);
			cpu->executeOpcode(0xF8);
			Assert::AreEqual(static_cast<u16>(0x0010), HL->getValue());
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.N);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);


			//TODO Verifier les flags H et C
			*PC = 0xC002;
			*SP = 0x0002;
			cpu->writeMemory((*PC) + 1, 0xFF);
			cpu->executeOpcode(0xF8);
			Assert::AreEqual(static_cast<u16>(0x0001), HL->getValue());
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.N);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.C);

		}

		TEST_METHOD(LD_SPcHL)
		{
			u16* SP = cpu->getSP();

			cpu->setCombinedRegistries("HL", 0x1234);
			
			cpu->executeOpcode(0xF9);

			Assert::AreEqual(static_cast<u16>(0x1234), *SP);

		}



	};

	std::shared_ptr<Memory> I16BitLoadTests::memory = nullptr;
	std::shared_ptr<Cartridge> I16BitLoadTests::cartridge = nullptr;
	std::shared_ptr<Bus> I16BitLoadTests::bus = nullptr;
	std::shared_ptr<CPU> I16BitLoadTests::cpu = nullptr;
	std::shared_ptr<PPU> I16BitLoadTests::ppu = nullptr;
}
