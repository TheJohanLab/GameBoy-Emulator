#pragma once

#include "Instruction.h"
#include "../CPU/CPU.h"

class InstructionCPUControl : public Instruction
{
		public:
			InstructionCPUControl(std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles);
			virtual ~InstructionCPUControl() = default;

			static void nop(CPU & cpu);			//0x00 NOP
			static void stop_0(CPU& cpu);		//0x10 STOP 0
			static void halt(CPU& cpu);			//0x76 HALT
			static void prefix_cb(CPU& cpu);	//0xCB PREFIX CB
			static void di(CPU& cpu);			//0xF3 DI
			static void ei(CPU& cpu);			//0xFB EI
			

};

