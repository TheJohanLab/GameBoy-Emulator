#include "Instruction.h"
#include "../CPU/CPU.h"


Instruction::Instruction()
{

}


u8 Instruction::readNextOpcode(CPU& cpu)
{
	u16* PC = cpu.getPC();
	*PC += 1;
	return cpu.readMemory(*PC);
}

void Instruction::updateHFlag(CPU& cpu, u8 byte, bool substract)
{
	flags* flagRegistry = cpu.getFlagRegistry();

	if (!substract)
	{
		if ((byte & 0x0F) == 0x0F)
			flagRegistry->flags.H = 1;
		else
			flagRegistry->flags.H = 0;
	}
	else
	{
		//TODO verifier
		if ((byte & 0x0F) == 0x00)
			flagRegistry->flags.H = 1;
		else
			flagRegistry->flags.H = 0;
	}
}

void Instruction::setHFlag(CPU& cpu, u8 registryValue, u8 addValue, bool substract)
{
	flags* flagRegistry = cpu.getFlagRegistry();

	if (!substract)
	{
		u8 resValue = registryValue + addValue;
		if ( (registryValue & 0x0F) + (addValue & 0x0F) > 0x0F)
			flagRegistry->flags.H = 1;
		else
			flagRegistry->flags.H = 0;
	}
	else
	{
		u8 a = (registryValue & 0x0F);
		u8 b = (addValue & 0x0F);
		u8 resValue = a - b;
		//if (((registryValue & 0x0F) - (addValue & 0x0F)) > (registryValue & 0x0F))
		//if (resValue > a)
		//TODO a verifier
		if (a < b)
			flagRegistry->flags.H = 1;
		else
			flagRegistry->flags.H = 0;
	}
}

void Instruction::setHFlag(CPU& cpu, u8 value)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	flagRegistry->flags.H = (value == 0x01) ? 1 : 0;
}

void Instruction::setZFlag(CPU& cpu, u8 value)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	flagRegistry->flags.Z = (value == 0x00) ? 1 : 0;
}

void Instruction::setNFlag(CPU& cpu, u8 value)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	flagRegistry->flags.N = (value == 0x01) ? 1 : 0;
}

void Instruction::setCFlag(CPU& cpu, u8 registryValue, u8 addValue, bool substract)
{
	flags* flagRegistry = cpu.getFlagRegistry();

	if (!substract)
	{
		u8 resValue = registryValue + addValue;
		flagRegistry->flags.C = (resValue < registryValue) ? 1 : 0;
	}
	else
	{
		u8 resValue = registryValue - addValue;
		flagRegistry->flags.C = (resValue > registryValue) ? 1 : 0;
	}
}

void Instruction::setCFlag(CPU& cpu, u8 value)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	flagRegistry->flags.C = (value == 0x01) ? 1 : 0;
}
