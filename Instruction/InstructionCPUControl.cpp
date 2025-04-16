#include "pch.h"

#include "InstructionCPUControl.h"

InstructionCPUControl::InstructionCPUControl(const char* name, std::function<u8(CPU& cpu)> instruction, Registries& reg, std::shared_ptr<Bus> bus)
	:Instruction(name, instruction, reg, bus)
{
}

u8 InstructionCPUControl::nop(CPU & cpu)
{
	return 4;
}

u8 InstructionCPUControl::stop_0(CPU& cpu)
{
	cpu.stopCPU(); //TODO Check how to handle this without cpu reference

	return 4;
}

u8 InstructionCPUControl::halt(CPU& cpu)
{
	//TODO Check if mandatory
	return 4;
}

u8 InstructionCPUControl::prefix_cb(CPU& cpu)
{
	return 4;
}

u8 InstructionCPUControl::di(CPU& cpu)
{
	*mIME = 0;

	return 4;
}

u8 InstructionCPUControl::ei(CPU& cpu)
{
	*mIME = 1;

	return 4;
}
