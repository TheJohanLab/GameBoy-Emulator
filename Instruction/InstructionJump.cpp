#include "pch.h"

#include "InstructionJump.h"

/// Private methods
//void InstructionJump::JP_CCca16(CPU& cpu, Instruction& instance, const u8& flagCondition)
u8 InstructionJump::JP_CCca16(CPU& cpu, bool flag)
{
	u16 adress = readNextTwoOpcodes(cpu);
	
	if (flag)
	{
		*mPC = adress -1;
		return 16;
	}
	
	return 12;
}

u8 InstructionJump::JR_CCca16(CPU& cpu, bool flag)
{
	int8_t offset = static_cast<int8_t>(readNextOpcode(cpu));

	if (flag)
	{
		*mPC += (offset);
		return 12;
	}
	
	return 8;
}

u8 InstructionJump::RET_CC(CPU& cpu, bool flag)
{

	if (flag)
	{
		RET(cpu);
		return 20;
	}
	
	return 8;
}

u8 InstructionJump::CALL_CC(CPU& cpu, bool flag)
{
	
	u16 address = readNextTwoOpcodes(cpu);

	if (flag)
	{
		PUSH_PC(cpu);
		//(*mPC)++;
		//u8 lowPC = *mPC & 0x00FF;
		//u8 highPC = (*mPC & 0xFF00) >> 8;
		//(*mSP)--;
		//mBus->write(*mSP, highPC);
		//(*mSP)--;
		//mBus->write(*mSP, lowPC);

		*mPC = address - 1; // -1 because PC will be incremented automatically after

		return 24;
	}
	
	return 12;
}

void InstructionJump::RST_VC(CPU& cpu, const u16& address)
{
	
	PUSH_PC(cpu);

	*mPC = address -1;
}

void InstructionJump::PUSH_PC(CPU& cpu)
{
	//TODO add an assert for this condition
	//if (*SP <= 0xFF47)
	//	throw std::runtime_error("Stack overflow : SP reached an invalid memory region");

	(*mPC)++;

	u8 lowPC = *mPC & 0x00FF;
	u8 highPC = (*mPC & 0xFF00) >> 8;
	(*mSP)--;
	mBus->write(*mSP, highPC);
	(*mSP)--;
	mBus->write(*mSP, lowPC);

	(*mPC)--;
}


// Public methods
InstructionJump::InstructionJump(const char* name, std::function<u8(CPU& cpu)> instruction, Registries& reg, std::shared_ptr<Bus> bus)
	:Instruction(name, instruction, reg, bus)
{
}

u8 InstructionJump::JR_r8(CPU& cpu)
{
	int8_t offset = static_cast<int8_t>(readNextOpcode(cpu));

	*mPC += (offset);

	return 12;
}

u8 InstructionJump::JR_NZcr8(CPU& cpu)
{
	return JR_CCca16(cpu, mFlags->flags.Z == 0);
}

u8 InstructionJump::JR_Zcr8(CPU& cpu)
{
	return JR_CCca16(cpu, mFlags->flags.Z != 0);
}

u8 InstructionJump::JR_NCcr8(CPU& cpu)
{
	return JR_CCca16(cpu, mFlags->flags.C == 0);
}

u8 InstructionJump::JR_Ccr8(CPU& cpu)
{
	return JR_CCca16(cpu, mFlags->flags.C != 0);
}

u8 InstructionJump::RET_NZ(CPU& cpu)
{
	return RET_CC(cpu, mFlags->flags.Z == 0);
}

u8 InstructionJump::JP_NZca16(CPU& cpu)
{
	return JP_CCca16(cpu, mFlags->flags.Z == 0);
}

u8 InstructionJump::JP_a16(CPU& cpu)
{
	u16 adress = readNextTwoOpcodes(cpu);
	*mPC = adress -1;

	return 16;
}

u8 InstructionJump::CALL_NZca16(CPU& cpu)
{
	return CALL_CC(cpu, mFlags->flags.Z == 0);
}

u8 InstructionJump::RST_00H(CPU& cpu)
{
	RST_VC(cpu, 0x0000); 
	return 16;
}

u8 InstructionJump::RET_Z(CPU& cpu)
{
	return RET_CC(cpu, mFlags->flags.Z != 0);
}

u8 InstructionJump::RET(CPU& cpu)
{
	u8 lowPC = mBus->read( (*mSP)++);
	u8 highPC = mBus->read((*mSP)++);

	*mPC = (((highPC << 8) & 0xFF00) | (lowPC & 0x00FF)) -1;

	return 16;
}

u8 InstructionJump::JP_Zca16(CPU& cpu)
{
	return JP_CCca16(cpu, mFlags->flags.Z != 0);
}

u8 InstructionJump::CALL_Zca16(CPU& cpu)
{
	return CALL_CC(cpu, mFlags->flags.Z != 0);
}

u8 InstructionJump::CALL_a16(CPU& cpu)
{
	u16 address = readNextTwoOpcodes(cpu);

	PUSH_PC(cpu);
	//(*mPC)++;
	//u8 lowPC = *mPC & 0x00FF;
	//u8 highPC = (*mPC & 0xFF00) >> 8;
	//(*mSP)--;
	//mBus->write(*mSP, highPC);
	//(*mSP)--;
	//mBus->write(*mSP, lowPC);

	*mPC = address - 1; // -1 because PC will be incremented automatically after

	return 24;
}

u8 InstructionJump::RST_08H(CPU& cpu)
{
	RST_VC(cpu, 0x08);

	return 16;
}

u8 InstructionJump::RET_NC(CPU& cpu)
{
	return RET_CC(cpu, mFlags->flags.C == 0);
}

u8 InstructionJump::JP_NCca16(CPU& cpu)
{
	return JP_CCca16(cpu, mFlags->flags.C == 0);
}

u8 InstructionJump::CALL_NCca16(CPU& cpu)
{
	return CALL_CC(cpu, mFlags->flags.C == 0);
}

u8 InstructionJump::RST_10H(CPU& cpu)
{
	RST_VC(cpu, 0x10);
	return 16;
}

u8 InstructionJump::RET_C(CPU& cpu)
{
	return RET_CC(cpu, mFlags->flags.C != 0);
}

u8 InstructionJump::RETI(CPU& cpu)
{
	*mIME = 1;
	return RET(cpu);
}

u8 InstructionJump::JP_Cca16(CPU& cpu)
{
	return JP_CCca16(cpu, mFlags->flags.C != 0);
}

u8 InstructionJump::CALL_Cca16(CPU& cpu)
{
	return CALL_CC(cpu, mFlags->flags.C != 0);
}

u8 InstructionJump::RST_18H(CPU& cpu)
{
	RST_VC(cpu, 0x18);
	return 16;
}

u8 InstructionJump::RST_20H(CPU& cpu)
{
	RST_VC(cpu, 0x20);
	return 16;
}

u8 InstructionJump::JP_pHLq(CPU& cpu)
{
	u16& HL = (*mDoubleRegistries)[DoubleReg::HL];
	*mPC = HL -1;

	return 4;
}

u8 InstructionJump::RST_28H(CPU& cpu)
{
	RST_VC(cpu, 0x28);

	return 16;
}

u8 InstructionJump::RST_30H(CPU& cpu)
{
	RST_VC(cpu, 0x30);

	return 16;
}

u8 InstructionJump::RST_38H(CPU& cpu)
{
	RST_VC(cpu, 0x38);

	return 16;
}


