#include "InstructionJump.h"

InstructionJump::InstructionJump(std::string const & name, void (*pInstruction)(CPU & cpu), u8 ClockCycle)
{
	mName = name;
	pmInstruction = pInstruction;
	mClockCycle = ClockCycle;

}

void InstructionJump::JR_r8(CPU& cpu)
{
}

void InstructionJump::JR_NZcr8(CPU& cpu)
{
}

void InstructionJump::JR_Zcr8(CPU& cpu)
{
}

void InstructionJump::JR_NCcr8(CPU& cpu)
{
}

void InstructionJump::JR_Ccr8(CPU& cpu)
{
}

void InstructionJump::RET_NZ(CPU& cpu)
{
}

void InstructionJump::JP_NZca16(CPU& cpu)
{
}

void InstructionJump::JP_a16(CPU& cpu)
{
}

void InstructionJump::CALL_NZca16(CPU& cpu)
{
}

void InstructionJump::RST_00H(CPU& cpu)
{
}

void InstructionJump::RET_Z(CPU& cpu)
{
}

void InstructionJump::RET(CPU& cpu)
{
}

void InstructionJump::JP_Zca16(CPU& cpu)
{
}

void InstructionJump::CALL_Zca16(CPU& cpu)
{
}

void InstructionJump::CALL_a16(CPU& cpu)
{
}

void InstructionJump::RST_08H(CPU& cpu)
{
}

void InstructionJump::RET_NC(CPU& cpu)
{
}

void InstructionJump::JP_NCca16(CPU& cpu)
{
}

void InstructionJump::CALL_NCca16(CPU& cpu)
{
}

void InstructionJump::RST_10H(CPU& cpu)
{
}

void InstructionJump::RET_C(CPU& cpu)
{
}

void InstructionJump::RETI(CPU& cpu)
{
}

void InstructionJump::JP_Cca16(CPU& cpu)
{
}

void InstructionJump::CALL_Cca16(CPU& cpu)
{
}

void InstructionJump::RST_18H(CPU& cpu)
{
}

void InstructionJump::RST_20H(CPU& cpu)
{
}

void InstructionJump::JP_pHLq(CPU& cpu)
{
}

void InstructionJump::RST_28H(CPU& cpu)
{
}

void InstructionJump::RST_30H(CPU& cpu)
{
}

void InstructionJump::RST_38H(CPU& cpu)
{
}
