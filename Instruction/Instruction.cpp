#include "pch.h"

#include "Instruction.h"
#include "CPU/CPU.h"


Instruction::Instruction(const char* name, std::function<u8(CPU& cpu)> instruction, Registries& registries, std::shared_ptr<Bus> bus)
	:mName(name), mInstruction(instruction),
	mBus(bus),
	mRegistries(registries.getRegistriesRef()),
	mAF(registries.getAFRef()), mBC(registries.getAFRef()), mDE(registries.getAFRef()), mHL(registries.getAFRef()),
	mSP(registries.getSPRef()), mPC(registries.getPCRef())
{
}



u8 Instruction::readNextOpcode(CPU& cpu)
{
	u16* PC = cpu.getPC();
	*PC += 1;

	 u8 value = cpu.readMemory(*PC);

#ifdef _DEBUG
	 std::stringstream ss;
	 ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(value);
	 cpu.setNextOpcodesValue("0x" + ss.str());
#endif

#ifdef LOG_DEBUG
	 GBE_LOG_INFO("readNextOpcode : {:#x}", value);
#endif

	 return value;
}

u16 Instruction::readNextTwoOpcodes(CPU& cpu)
{
	u16* PC = cpu.getPC();
	u16 lsbValue = static_cast<u16>(cpu.readMemory((*PC) + 1)) & 0x00FF;
	u16 msbValue = (static_cast<u16>(cpu.readMemory((*PC) + 2)) << 8) & 0xFF00;
	u16 twoBytesValue = lsbValue | msbValue;
	*PC += 2;

#ifdef _DEBUG
	std::stringstream ss;
	ss << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(twoBytesValue);
	cpu.setNextOpcodesValue("0x" + ss.str());
#endif

#ifdef LOG_DEBUG
	GBE_LOG_INFO("readNextTwoOpcodes : {:#x}", twoBytesValue);
#endif

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
		//return ((baseValue ^ (baseValue - additionalValue)) & (1 << 4));
		return ((baseValue & 0xF) - ((baseValue - additionalValue) & 0xF)) & 0x10;
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
		((baseValue & 0xFFF) - ((baseValue - additionalValue) & 0xFFF)) & 0x1000;
		//return ((baseValue ^ (baseValue - additionalValue)) & (1 << 8));
		//return (additionalValue & 0x0FFF) > (baseValue & 0x0FFF);
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

