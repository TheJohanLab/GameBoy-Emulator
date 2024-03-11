#pragma once

#include "Instruction.h"
#include "../CPU/CPU.h"

class InstructionJump : public Instruction
{
	public:
		InstructionJump(std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles);
		virtual ~InstructionJump() = default;

		static void JR_r8(CPU& cpu);		//0x18 JR r8
		static void JR_NZcr8(CPU& cpu);		//0x20 JR NZ,r8
		static void JR_Zcr8(CPU& cpu);		//0x28 JR Z,r8
		static void JR_NCcr8(CPU& cpu);		//0x30 JR NC,r8
		static void JR_Ccr8(CPU& cpu);		//0x38 JR C,r8

		static void RET_NZ(CPU& cpu);		//0xC0 RET NZ
		static void JP_NZca16(CPU& cpu);	//0xC2 JP NZ,a16
		static void JP_a16(CPU& cpu);		//0xC3 JP a16
		static void CALL_NZca16(CPU& cpu);	//0xC4 CALL NZ,a16
		static void RST_00H(CPU& cpu);		//0xC7 RST 00H
		static void RET_Z(CPU& cpu);		//0xC8 RET Z
		static void RET(CPU& cpu);			//0xC9 RET
		static void JP_Zca16(CPU& cpu);		//0xCA JP Z,a16
		static void CALL_Zca16(CPU& cpu);	//0xCC CALL Z,a16
		static void CALL_a16(CPU& cpu);		//0xCD CALL a16
		static void RST_08H(CPU& cpu);		//0xCF RST 08H

		static void RET_NC(CPU& cpu);		//0xD0 RET NC
		static void JP_NCca16(CPU& cpu);	//0xD2 JP NC,a16
		static void CALL_NCca16(CPU& cpu);	//0xD4 CALL NC,a16
		static void RST_10H(CPU& cpu);		//0xD7 RST 10H
		static void RET_C(CPU& cpu);		//0xD8 RET C
		static void RETI(CPU& cpu);			//0xD9 RETI
		//static void JP_Cca16(CPU& cpu, Instruction& instance);		//0xDA JP C,a16
		static void JP_Cca16(CPU& cpu);		//0xDA JP C,a16
		static void CALL_Cca16(CPU& cpu);	//0xDC CALL C,a16
		static void RST_18H(CPU& cpu);		//0xDF RST 18H

		static void RST_20H(CPU& cpu);		//0xE7 RST 20H
		static void JP_pHLq(CPU& cpu);		//0xE9 JP (HL)
		static void RST_28H(CPU& cpu);		//0xEF RST 28H

		static void RST_30H(CPU& cpu);		//0xF7 RST 30H
		static void RST_38H(CPU& cpu);		//0xFF RST 38H


private:
	//TODO voir avec Merlin pour l'integration de l'instance ou trouver une autre solution
	//static void JP_CCca16(CPU& cpu, Instruction& instance, const u8& flag);
	static void JP_CCca16(CPU& cpu, const u8& flag);
	static void JR_CCca16(CPU& cpu, const u8& flag);
	static void RET_CC(CPU& cpu, const u8& flag);
	static void CALL_CC(CPU& cpu, const u8& flag);

	static void PUSH_PC(CPU& cpu);
};

