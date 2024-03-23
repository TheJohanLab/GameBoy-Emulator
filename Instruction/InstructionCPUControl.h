#pragma once

#include "Instruction.h"
#include "../CPU/CPU.h"

class InstructionCPUControl : public Instruction
{
		public:
			InstructionCPUControl(const char* name, u8 (*pInstruction)(CPU & cpu), u8 clockCycles);
			virtual ~InstructionCPUControl() = default;

			static u8 nop(CPU & cpu);			//0x00 NOP
			static u8 stop_0(CPU& cpu);		//0x10 STOP 0
			static u8 halt(CPU& cpu);			//0x76 HALT
			static u8 prefix_cb(CPU& cpu);	//0xCB PREFIX CB
			static u8 di(CPU& cpu);			//0xF3 DI
			static u8 ei(CPU& cpu);			//0xFB EI
			

};

