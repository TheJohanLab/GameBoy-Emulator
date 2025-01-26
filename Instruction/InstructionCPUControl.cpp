#include "pch.h"

#include "InstructionCPUControl.h"

InstructionCPUControl::InstructionCPUControl(const char* name, u8 (*pInstruction)(CPU & cpu), u8 ClockCycle)
	:Instruction(name, pInstruction, ClockCycle)
{
}

u8 InstructionCPUControl::nop(CPU & cpu)
{
	return 4;
}

u8 InstructionCPUControl::stop_0(CPU& cpu)
{
	//cpu.stopCPU();
	return 4;
}

u8 InstructionCPUControl::halt(CPU& cpu)
{
	return 4;
}

u8 InstructionCPUControl::prefix_cb(CPU& cpu)
{
	return 4;
}

u8 InstructionCPUControl::di(CPU& cpu)
{
	cpu.clearIMEFlag();
	return 4;
}

u8 InstructionCPUControl::ei(CPU& cpu)
{
	cpu.setIMEFlag();
	return 4;
}
