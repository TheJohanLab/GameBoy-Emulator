#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{

	TEST_CLASS(IJumpTests)
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

		//TODO Verifier que l'odre dans la memoire est correcte pour charger une adresse
		TEST_METHOD(JP_a16)
		{
			u16* PC = cpu->getPC();
			*PC = 0xC000;
			cpu->writeMemory((*PC) + 1, 0x05);
			cpu->writeMemory((*PC) + 2, 0xC0);
			
			cpu->executeOpcode(0xC3);

			Assert::AreEqual(static_cast<u16>(0xC005), *PC);
		}

		//Verifier l'opcode
		TEST_METHOD(JP_pHLq)
		{
			u16* PC = cpu->getPC();
			*PC = 0xC000;
			cpu->setCombinedRegistries("HL", 0xC006);

			cpu->executeOpcode(0xE9);

			Assert::AreEqual(static_cast<u16>(0xC006), *PC);
		}

		TEST_METHOD(JP_Cca16)
		{
			u16* PC = cpu->getPC();
			flags* f = cpu->getFlagRegistry();
			*PC = 0xC000;
			f->flags.C = 1;

			cpu->writeMemory((*PC) + 1, 0x07);
			cpu->writeMemory((*PC) + 2, 0xC0);

			cpu->executeOpcode(0xDA);

			Assert::AreEqual(static_cast<u16>(0xC007), *PC);

			*PC = 0xC000;
			f->flags.C = 0;

			cpu->writeMemory((*PC) + 1, 0x07);
			cpu->writeMemory((*PC) + 2, 0xC0);

			cpu->executeOpcode(0xDA);

			Assert::AreEqual(static_cast<u16>(0xC002), *PC);
		}

		TEST_METHOD(JP_NCca16)
		{
			u16* PC = cpu->getPC();
			flags* f = cpu->getFlagRegistry();
			*PC = 0xC000;
			f->flags.C = 1;

			cpu->writeMemory((*PC) + 1, 0x07);
			cpu->writeMemory((*PC) + 2, 0xC0);

			cpu->executeOpcode(0xD2);

			Assert::AreEqual(static_cast<u16>(0xC002), *PC);

			*PC = 0xC000;
			f->flags.C = 0;

			cpu->writeMemory((*PC) + 1, 0x07);
			cpu->writeMemory((*PC) + 2, 0xC0);

			cpu->executeOpcode(0xD2);

			Assert::AreEqual(static_cast<u16>(0xC007), *PC);
		}

		TEST_METHOD(JP_Zca16)
		{
			u16* PC = cpu->getPC();
			flags* f = cpu->getFlagRegistry();
			*PC = 0xC000;
			f->flags.Z = 1;

			cpu->writeMemory((*PC) + 1, 0x07);
			cpu->writeMemory((*PC) + 2, 0xC0);

			cpu->executeOpcode(0xCA);

			Assert::AreEqual(static_cast<u16>(0xC007), *PC);

			*PC = 0xC000;
			f->flags.Z = 0;

			cpu->writeMemory((*PC) + 1, 0x07);
			cpu->writeMemory((*PC) + 2, 0xC0);

			cpu->executeOpcode(0xDA);

			Assert::AreEqual(static_cast<u16>(0xC002), *PC);
		}

		TEST_METHOD(JP_NZca16)
		{
			u16* PC = cpu->getPC();
			flags* f = cpu->getFlagRegistry();
			*PC = 0xC000;
			f->flags.Z = 1;

			cpu->writeMemory((*PC) + 1, 0x07);
			cpu->writeMemory((*PC) + 2, 0xC0);

			cpu->executeOpcode(0xC2);

			Assert::AreEqual(static_cast<u16>(0xC002), *PC);

			*PC = 0xC000;
			f->flags.Z = 0;

			cpu->writeMemory((*PC) + 1, 0x07);
			cpu->writeMemory((*PC) + 2, 0xC0);

			cpu->executeOpcode(0xD2);

			Assert::AreEqual(static_cast<u16>(0xC007), *PC);
		}

		TEST_METHOD(JR_a16)
		{
			u16* PC = cpu->getPC();
			flags* f = cpu->getFlagRegistry();
			*PC = 0xC000;

			cpu->writeMemory((*PC) + 1, 0x32);

			cpu->executeOpcode(0x18);

			Assert::AreEqual(static_cast<u16>(0xC033), *PC);

			*PC = 0xC064; // 3172
			cpu->writeMemory((*PC) + 1, 0xCE); // -50
			cpu->executeOpcode(0x18);
			Assert::AreEqual(static_cast<u16>(0xC033), *PC); // 3122

			*PC = 0xC078; 
			cpu->writeMemory((*PC) + 1, 0x9C); // -100
			cpu->executeOpcode(0x18);
			Assert::AreEqual(static_cast<u16>(0xC015), *PC); // 3122
		}

		TEST_METHOD(JR_NZca16)
		{
			u16* PC = cpu->getPC();
			flags* f = cpu->getFlagRegistry();
			*PC = 0xC000;
			f->flags.Z = 1;

			cpu->writeMemory((*PC) + 1, 0x32);

			cpu->executeOpcode(0x20);

			Assert::AreEqual(static_cast<u16>(0xC001), *PC);

			*PC = 0xC000;
			f->flags.Z = 0;

			cpu->writeMemory((*PC) + 1, 0x32);

			cpu->executeOpcode(0x20);

			Assert::AreEqual(static_cast<u16>(0xC033), *PC);
		}

		TEST_METHOD(JR_Zca16)
		{
			u16* PC = cpu->getPC();
			flags* f = cpu->getFlagRegistry();
			*PC = 0xC000;
			f->flags.Z = 0;

			cpu->writeMemory((*PC) + 1, 0x32);

			cpu->executeOpcode(0x28);

			Assert::AreEqual(static_cast<u16>(0xC001), *PC);

			*PC = 0xC000;
			f->flags.Z = 1;

			cpu->writeMemory((*PC) + 1, 0x32);

			cpu->executeOpcode(0x28);

			Assert::AreEqual(static_cast<u16>(0xC033), *PC);
		}

		TEST_METHOD(JR_NCca16)
		{
			u16* PC = cpu->getPC();
			flags* f = cpu->getFlagRegistry();
			*PC = 0xC000;
			f->flags.C = 1;

			cpu->writeMemory((*PC) + 1, 0x32);

			cpu->executeOpcode(0x30);

			Assert::AreEqual(static_cast<u16>(0xC001), *PC);

			*PC = 0xC000;
			f->flags.C = 0;

			cpu->writeMemory((*PC) + 1, 0x32);

			cpu->executeOpcode(0x30);

			Assert::AreEqual(static_cast<u16>(0xC033), *PC);
		}

		TEST_METHOD(JR_Cca16)
		{
			u16* PC = cpu->getPC();
			flags* f = cpu->getFlagRegistry();
			*PC = 0xC000;
			f->flags.C = 0;

			cpu->writeMemory((*PC) + 1, 0x32);

			cpu->executeOpcode(0x38);

			Assert::AreEqual(static_cast<u16>(0xC001), *PC);

			*PC = 0xC000;
			f->flags.C = 1;

			cpu->writeMemory((*PC) + 1, 0x32);

			cpu->executeOpcode(0x38);

			Assert::AreEqual(static_cast<u16>(0xC033), *PC);
		}

		TEST_METHOD(RET)
		{

			u16* SP = cpu->getSP();
			u16* PC = cpu->getPC();

			*SP = 0xC000;
			cpu->writeMemory(0xC000, 0x12);
			cpu->writeMemory(0xC001, 0x34);
			*PC =  0x0000;

			cpu->executeOpcode(0xC9);

			Assert::AreEqual(static_cast<u16>(0xC002), *SP);
			Assert::AreEqual(static_cast<u16>(0x3412), *PC );

		}

		TEST_METHOD(RET_NC)
		{
			u16* SP = cpu->getSP();
			u16* PC = cpu->getPC();
			flags* f = cpu->getFlagRegistry();
			f->flags.C = 1;

			*SP = 0xC000;
			cpu->writeMemory(0xC000, 0x12);
			cpu->writeMemory(0xC001, 0x34);
			*PC = 0x0000;

			cpu->executeOpcode(0xD0);

			Assert::AreEqual(static_cast<u16>(0xC000), *SP);
			Assert::AreEqual(static_cast<u16>(0x0000), *PC);

			f->flags.C = 0;

			*SP = 0xC000;
			cpu->writeMemory(0xC000, 0x12);
			cpu->writeMemory(0xC001, 0x34);
			*PC = 0x0000;

			cpu->executeOpcode(0xD0);

			Assert::AreEqual(static_cast<u16>(0xC002), *SP);
			Assert::AreEqual(static_cast<u16>(0x3412), *PC);

		}

		TEST_METHOD(RET_C)
		{
			u16* SP = cpu->getSP();
			u16* PC = cpu->getPC();
			flags* f = cpu->getFlagRegistry();
			f->flags.C = 0;

			*SP = 0xC000;
			cpu->writeMemory(0xC000, 0x12);
			cpu->writeMemory(0xC001, 0x34);
			*PC = 0x0000;

			cpu->executeOpcode(0xD8);

			Assert::AreEqual(static_cast<u16>(0xC000), *SP);
			Assert::AreEqual(static_cast<u16>(0x0000), *PC);

			f->flags.C = 1;

			*SP = 0xC000;
			cpu->writeMemory(0xC000, 0x12);
			cpu->writeMemory(0xC001, 0x34);
			*PC = 0x0000;

			cpu->executeOpcode(0xD8);

			Assert::AreEqual(static_cast<u16>(0xC002), *SP);
			Assert::AreEqual(static_cast<u16>(0x3412), *PC);

		}

		TEST_METHOD(RET_NZ)
		{
			u16* SP = cpu->getSP();
			u16* PC = cpu->getPC();
			flags* f = cpu->getFlagRegistry();
			f->flags.Z = 1;

			*SP = 0xC000;
			cpu->writeMemory(0xC000, 0x12);
			cpu->writeMemory(0xC001, 0x34);
			*PC = 0x0000;

			cpu->executeOpcode(0xC0);

			Assert::AreEqual(static_cast<u16>(0xC000), *SP);
			Assert::AreEqual(static_cast<u16>(0x0000), *PC);

			f->flags.Z = 0;

			*SP = 0xC000;
			cpu->writeMemory(0xC000, 0x12);
			cpu->writeMemory(0xC001, 0x34);
			*PC = 0x0000;

			cpu->executeOpcode(0xC0);

			Assert::AreEqual(static_cast<u16>(0xC002), *SP);
			Assert::AreEqual(static_cast<u16>(0x3412), *PC);

		}

		TEST_METHOD(RET_Z)
		{
			u16* SP = cpu->getSP();
			u16* PC = cpu->getPC();
			flags* f = cpu->getFlagRegistry();
			f->flags.Z = 0;

			*SP = 0xC000;
			cpu->writeMemory(0xC000, 0x12);
			cpu->writeMemory(0xC001, 0x34);
			*PC = 0x0000;

			cpu->executeOpcode(0xC8);

			Assert::AreEqual(static_cast<u16>(0xC000), *SP);
			Assert::AreEqual(static_cast<u16>(0x0000), *PC);

			f->flags.Z = 1;

			*SP = 0xC000;
			cpu->writeMemory(0xC000, 0x12);
			cpu->writeMemory(0xC001, 0x34);
			*PC = 0x0000;

			cpu->executeOpcode(0xC8);

			Assert::AreEqual(static_cast<u16>(0xC002), *SP);
			Assert::AreEqual(static_cast<u16>(0x3412), *PC);

		}

		//TODO
		TEST_METHOD(CALL_a16)
		{
		

		}

		//TODO
		TEST_METHOD(CALL_NZca16)
		{


		}

		//TODO
		TEST_METHOD(CALL_Zca16)
		{


		}

		//TODO
		TEST_METHOD(CALL_NCca16)
		{


		}

		//TODO
		TEST_METHOD(CALL_Cca16)
		{


		}

	};

	Bus* IJumpTests::bus = nullptr;
	CPU* IJumpTests::cpu = nullptr;
}