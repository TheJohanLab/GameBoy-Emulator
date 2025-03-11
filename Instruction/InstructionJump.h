#pragma once

#include "Instruction.h"
#include "CPU/CPU.h"

class InstructionJump : public Instruction
{
	public:
		InstructionJump(const char* name, std::function<u8(CPU& cpu)> instruction, Registries& reg, std::shared_ptr<Bus> bus);
		virtual ~InstructionJump() = default;

		static u8 JR_r8(CPU& cpu);		//0x18 JR r8
		static u8 JR_NZcr8(CPU& cpu);		//0x20 JR NZ,r8
		static u8 JR_Zcr8(CPU& cpu);		//0x28 JR Z,r8
		static u8 JR_NCcr8(CPU& cpu);		//0x30 JR NC,r8
		static u8 JR_Ccr8(CPU& cpu);		//0x38 JR C,r8

		static u8 RET_NZ(CPU& cpu);		//0xC0 RET NZ
		static u8 JP_NZca16(CPU& cpu);	//0xC2 JP NZ,a16
		static u8 JP_a16(CPU& cpu);		//0xC3 JP a16
		static u8 CALL_NZca16(CPU& cpu);	//0xC4 CALL NZ,a16
		static u8 RST_00H(CPU& cpu);		//0xC7 RST 00H
		static u8 RET_Z(CPU& cpu);		//0xC8 RET Z
		static u8 RET(CPU& cpu);			//0xC9 RET
		static u8 JP_Zca16(CPU& cpu);		//0xCA JP Z,a16
		static u8 CALL_Zca16(CPU& cpu);	//0xCC CALL Z,a16
		static u8 CALL_a16(CPU& cpu);		//0xCD CALL a16
		static u8 RST_08H(CPU& cpu);		//0xCF RST 08H

		static u8 RET_NC(CPU& cpu);		//0xD0 RET NC
		static u8 JP_NCca16(CPU& cpu);	//0xD2 JP NC,a16
		static u8 CALL_NCca16(CPU& cpu);	//0xD4 CALL NC,a16
		static u8 RST_10H(CPU& cpu);		//0xD7 RST 10H
		static u8 RET_C(CPU& cpu);		//0xD8 RET C
		static u8 RETI(CPU& cpu);			//0xD9 RETI
		//static u8 JP_Cca16(CPU& cpu, Instruction& instance);		//0xDA JP C,a16
		static u8 JP_Cca16(CPU& cpu);		//0xDA JP C,a16
		static u8 CALL_Cca16(CPU& cpu);	//0xDC CALL C,a16
		static u8 RST_18H(CPU& cpu);		//0xDF RST 18H

		static u8 RST_20H(CPU& cpu);		//0xE7 RST 20H
		static u8 JP_pHLq(CPU& cpu);		//0xE9 JP (HL)
		static u8 RST_28H(CPU& cpu);		//0xEF RST 28H

		static u8 RST_30H(CPU& cpu);		//0xF7 RST 30H
		static u8 RST_38H(CPU& cpu);		//0xFF RST 38H

		//TODO mettre cette methode dans Instruction.h
		static void PUSH_PC(CPU& cpu);

private:
	//TODO voir avec Merlin pour l'integration de l'instance ou trouver une autre solution
	//static void JP_CCca16(CPU& cpu, Instruction& instance, const u8& flag);
	static u8 JP_CCca16(CPU& cpu, const u8& flag);
	static u8 JR_CCca16(CPU& cpu, const u8& flag);
	static u8 RET_CC(CPU& cpu, const u8& flag);
	static u8 CALL_CC(CPU& cpu, const u8& flag);
	static void RST_VC(CPU& cpu, const u16& address);

};

