#include "InstructionCPUControl.h"

InstructionCPUControl::InstructionCPUControl(std::string const & name, void (*pInstruction)(CPU & cpu), u8 ClockCycle)
{
	mName = name;
	pmInstruction = pInstruction;
	mClockCycle = ClockCycle;
}

void InstructionCPUControl::nop(CPU & cpu)
{
}

void InstructionCPUControl::stop_0(CPU& cpu)
{
}

void InstructionCPUControl::halt(CPU& cpu)
{
}

void InstructionCPUControl::prefix_cb(CPU& cpu)
{
}

void InstructionCPUControl::di(CPU& cpu)
{
	cpu.clearIMEFlag();
}

void InstructionCPUControl::ei(CPU& cpu)
{
	cpu.setIMEFlag();
}
