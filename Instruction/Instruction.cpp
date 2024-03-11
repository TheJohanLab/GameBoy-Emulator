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

u16 Instruction::readNextTwoOpcodes(CPU& cpu)
{
	u16* PC = cpu.getPC();
	u16 lsbValue = static_cast<u16>(cpu.readMemory(0xC001)) & 0x00FF;
	u16 msbValue = (static_cast<u16>(cpu.readMemory(0xC002)) << 8) & 0xFF00;
	u16 twoBytesValue = lsbValue | msbValue;
	*PC += 2;

	return twoBytesValue;
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

void Instruction::setHFlag(CPU& cpu, u8 baseValue, u8 additionalValue, bool substract)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	flagRegistry->flags.H = isHalfOverflow(baseValue, additionalValue, substract) ? 1 : 0;
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

void Instruction::setCFlag(CPU& cpu, const u8& baseValue, const u8& additionnalValue, bool substract)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	flagRegistry->flags.C = isOverflow(baseValue, additionnalValue, substract) ? 1 : 0;
}

void Instruction::setCFlag(CPU& cpu, u8 value)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	flagRegistry->flags.C = (value == 0x01) ? 1 : 0;
}

void Instruction::clearFlag(CPU& cpu, const char& flag)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	switch (flag)
	{
	case 'Z':
		flagRegistry->flags.Z = 0;
		break;
	case 'C':
		flagRegistry->flags.C = 0;
		break;
	case 'H':
		flagRegistry->flags.H = 0;
		break;
	case 'N':
		flagRegistry->flags.N = 0;
		break;
	};
}

void Instruction::setFlags(CPU& cpu, const u8& binaryFlags)
{
	flags* flags = cpu.getFlagRegistry();
	flags->F = binaryFlags;
}

bool Instruction::isHalfOverflow(const u8& baseValue, const u8& additionalValue, bool substract)
{
	if (!substract)
	{
		u8 resultValue = (baseValue & 0x0F) + (additionalValue & 0x0F);
		return resultValue > 0x0F;
	}
	else
	{
		return (additionalValue & 0x0F) > (baseValue & 0x0F);
	}
}

bool Instruction::isHalfOverflow(const u16& baseValue, const u16& additionalValue, bool substract)
{
	if (!substract)
	{
		u16 resultValue = (baseValue & 0x0FFF) + (additionalValue & 0x0FFF);
		return resultValue > 0x0FFF;
	}
	else
	{
		return (additionalValue & 0x0FFF) > (baseValue & 0x0FFF);
	}
}

bool Instruction::isOverflow(const u8& baseValue, const u8& additionalValue, bool substract)
{
	if (!substract)
	{
		u8 resultValue = baseValue + additionalValue;
		return resultValue < baseValue;
	}
	else
	{
		u8 resultValue = baseValue - additionalValue;
		return resultValue > baseValue;
	}
	
}

bool Instruction::isOverflow(const u16& baseValue, const u16& additionalValue, bool substract)
{
	if (!substract)
	{
		u16 resultValue = baseValue + additionalValue;
		return resultValue < baseValue;
	}
	else
	{
		u16 resultValue = baseValue - additionalValue;
		return resultValue > baseValue;
	}

}

//TODO voir avec Merlin pour l'integration de l'instance ou trouver une autre solution
void Instruction::setClockCycle(Instruction& instance, const u8& clockCycle)
{
	instance.mClockCycle = clockCycle;
}
