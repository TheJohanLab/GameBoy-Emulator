#include "InstructionRotateShift.h"

InstructionRotateShift::InstructionRotateShift(std::string const & name, void (*pInstruction)(CPU & cpu), u8 ClockCycle)
{
	mName = name;
	pmInstruction = pInstruction;
	mClockCycle = ClockCycle;

}