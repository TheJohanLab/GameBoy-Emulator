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
	// cpu.stopCPU(); // STOP inutilisé : ne s'arrete qu'a un reset ou un input joypad poour l'ecomonie d'energie => Pas utile pour un emulateur
	return 4;
}

u8 InstructionCPUControl::halt(CPU& cpu)
{
    cpu.haltCPU();
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
	cpu->setEIFlag(0x02);
	return 4;
}
