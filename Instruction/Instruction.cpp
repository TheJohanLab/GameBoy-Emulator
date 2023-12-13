#include "Instruction.h"
#include "../CPU/CPU.h"


Instruction::Instruction()
{

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

void Instruction::updateZFlag(CPU& cpu, u8 byte)
{
	flags* flagRegistry = cpu.getFlagRegistry();

	if (byte == 0x00)
		flagRegistry->flags.Z = 1;
	else
		flagRegistry->flags.Z = 0;
}

void Instruction::updateNFlag(CPU& cpu, u8 byte)
{
	flags* flagRegistry = cpu.getFlagRegistry();

	if (byte == 0x00)
		flagRegistry->flags.N = 0;
	else
		flagRegistry->flags.N = 1;

}
