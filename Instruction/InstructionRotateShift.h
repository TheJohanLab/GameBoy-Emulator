#pragma once
#include "Instruction.h"
#include "../CPU/CPU.h"

class InstructionRotateShift : public Instruction
{
	public:
		InstructionRotateShift(const char* name, u8 (*pInstruction)(CPU & cpu), u8 clockCycles);
		virtual ~InstructionRotateShift() = default;

		static u8 RLCA(CPU& cpu);				//0x07 RLCA
		static u8 RRCA(CPU& cpu);				//0x0F RRCA
		static u8 RLA(CPU& cpu);				//0x17 RLA
		static u8 RRA(CPU& cpu);				//0x1F RRA

		static u8 RLC_B(CPU& cpu);			//0xCB00 RLC B
		static u8 RLC_C(CPU& cpu);			//0xCB01 RLC C
		static u8 RLC_D(CPU& cpu);			//0xCB02 RLC D
		static u8 RLC_E(CPU& cpu);			//0xCB03 RLC E
		static u8 RLC_H(CPU& cpu);			//0xCB04 RLC H
		static u8 RLC_L(CPU& cpu);			//0xCB05 RLC L
		static u8 RLC_pHLq(CPU& cpu);			//0xCB06 RLC (HL)
		static u8 RLC_A(CPU& cpu);			//0xCB07 RLC A
		static u8 RRC_B(CPU& cpu);			//0xCB08 RRC B
		static u8 RRC_C(CPU& cpu);			//0xCB09 RRC C
		static u8 RRC_D(CPU& cpu);			//0xCB0A RRC D
		static u8 RRC_E(CPU& cpu);			//0xCB0B RRC E
		static u8 RRC_H(CPU& cpu);			//0xCB0C RRC H
		static u8 RRC_L(CPU& cpu);			//0xCB0D RRC L
		static u8 RRC_pHLq(CPU& cpu);			//0xCB0E RRC (HL)
		static u8 RRC_A(CPU& cpu);			//0xCB0F RRC A

		static u8 RL_B(CPU& cpu);			//0xCB10 RL B
		static u8 RL_C(CPU& cpu);			//0xCB11 RL C
		static u8 RL_D(CPU& cpu);			//0xCB12 RL D
		static u8 RL_E(CPU& cpu);			//0xCB13 RL E
		static u8 RL_H(CPU& cpu);			//0xCB14 RL H
		static u8 RL_L(CPU& cpu);			//0xCB15 RL L
		static u8 RL_pHLq(CPU& cpu);		//0xCB16 RL (HL)
		static u8 RL_A(CPU& cpu);			//0xCB17 RL A
		static u8 RR_B(CPU& cpu);			//0xCB18 RR B
		static u8 RR_C(CPU& cpu);			//0xCB19 RR C
		static u8 RR_D(CPU& cpu);			//0xCB1A RR D
		static u8 RR_E(CPU& cpu);			//0xCB1B RR E
		static u8 RR_H(CPU& cpu);			//0xCB1C RR H
		static u8 RR_L(CPU& cpu);			//0xCB1D RR L
		static u8 RR_pHLq(CPU& cpu);		//0xCB1E RR (HL)
		static u8 RR_A(CPU& cpu);			//0xCB1F RR A

		static u8 SLA_B(CPU& cpu);		//0xCB20 SLA B
		static u8 SLA_C(CPU& cpu);		//0xCB21 SLA C
		static u8 SLA_D(CPU& cpu);		//0xCB22 SLA D
		static u8 SLA_E(CPU& cpu);		//0xCB23 SLA E
		static u8 SLA_H(CPU& cpu);		//0xCB24 SLA H
		static u8 SLA_L(CPU& cpu);		//0xCB25 SLA L
		static u8 SLA_pHLq(CPU& cpu);		//0xCB26 SLA (HL)
		static u8 SLA_A(CPU& cpu);		//0xCB27 SLA A
		static u8 SRA_B(CPU& cpu);		//0xCB28 SRA B
		static u8 SRA_C(CPU& cpu);		//0xCB29 SRA C
		static u8 SRA_D(CPU& cpu);		//0xCB2A SRA D
		static u8 SRA_E(CPU& cpu);		//0xCB2B SRA E
		static u8 SRA_H(CPU& cpu);		//0xCB2C SRA H
		static u8 SRA_L(CPU& cpu);		//0xCB2D SRA L
		static u8 SRA_pHLq(CPU& cpu);		//0xCB2E SRA (HL)
		static u8 SRA_A(CPU& cpu);		//0xCB2F SRA A

		static u8 SWAP_B(CPU& cpu);		//0xCB30 SWAP B
		static u8 SWAP_C(CPU& cpu);		//0xCB31 SWAP C
		static u8 SWAP_D(CPU& cpu);		//0xCB32 SWAP D
		static u8 SWAP_E(CPU& cpu);		//0xCB33 SWAP E
		static u8 SWAP_H(CPU& cpu);		//0xCB34 SWAP H
		static u8 SWAP_L(CPU& cpu);		//0xCB35 SWAP L
		static u8 SWAP_pHLq(CPU& cpu);	//0xCB36 SWAP (HL)
		static u8 SWAP_A(CPU& cpu);		//0xCB37 SWAP A
		static u8 SRL_B(CPU& cpu);		//0xCB38 SRL B
		static u8 SRL_C(CPU& cpu);		//0xCB39 SRL C
		static u8 SRL_D(CPU& cpu);		//0xCB3A SRL D
		static u8 SRL_E(CPU& cpu);		//0xCB3B SRL E
		static u8 SRL_H(CPU& cpu);		//0xCB3C SRL H
		static u8 SRL_L(CPU& cpu);		//0xCB3D SRL L
		static u8 SRL_pHLq(CPU& cpu);		//0xCB3E SRL (HL)
		static u8 SRL_A(CPU& cpu);		//0xCB3F SRL A


private:
	static void RLCr(u8& registry, flags& flagRegistry, CPU& cpu);
	static void RRCr(u8& registry, flags& flagRegistry, CPU& cpu);
	static void RLr(u8& registry, flags& flagResistry, CPU& cpu);
	static void RRr(u8& registry, flags& flagRegistry, CPU& cpu);
	static void SLAr(u8& registry, flags& flagRegistry, CPU& cpu);
	static void SRAr(u8& registry, flags& flagRegistry, CPU& cpu);
	static void SWAPr(u8& registry, flags& flagRegistry, CPU& cpu);
	static void SRLr(u8& registry, flags& flagRegistry, CPU& cpu);

};

