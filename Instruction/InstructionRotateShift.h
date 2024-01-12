#pragma once
#include "Instruction.h"
#include "../CPU/CPU.h"

class InstructionRotateShift : public Instruction
{
	public:
		InstructionRotateShift(std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles);
		virtual ~InstructionRotateShift() = default;

		static void RLCA(CPU& cpu);				//0x07 RLCA
		static void RRCA(CPU& cpu);				//0x0F RRCA
		static void RLA(CPU& cpu);				//0x17 RLA
		static void RRA(CPU& cpu);				//0x1F RRA

		static void RLC_B(CPU& cpu);			//0xCB00 RLC B
		static void RLC_C(CPU& cpu);			//0xCB01 RLC C
		static void RLC_D(CPU& cpu);			//0xCB02 RLC D
		static void RLC_E(CPU& cpu);			//0xCB03 RLC E
		static void RLC_H(CPU& cpu);			//0xCB04 RLC H
		static void RLC_L(CPU& cpu);			//0xCB05 RLC L
		static void RLC_pHLq(CPU& cpu);			//0xCB06 RLC (HL)
		static void RLC_A(CPU& cpu);			//0xCB07 RLC A
		static void RRC_B(CPU& cpu);			//0xCB08 RRC B
		static void RRC_C(CPU& cpu);			//0xCB09 RRC C
		static void RRC_D(CPU& cpu);			//0xCB0A RRC D
		static void RRC_E(CPU& cpu);			//0xCB0B RRC E
		static void RRC_H(CPU& cpu);			//0xCB0C RRC H
		static void RRC_L(CPU& cpu);			//0xCB0D RRC L
		static void RRC_pHLq(CPU& cpu);			//0xCB0E RRC (HL)
		static void RRC_A(CPU& cpu);			//0xCB0F RRC A

		static void RL_B(CPU& cpu);			//0xCB10 RL B
		static void RL_C(CPU& cpu);			//0xCB11 RL C
		static void RL_D(CPU& cpu);			//0xCB12 RL D
		static void RL_E(CPU& cpu);			//0xCB13 RL E
		static void RL_H(CPU& cpu);			//0xCB14 RL H
		static void RL_L(CPU& cpu);			//0xCB15 RL L
		static void RL_pHLq(CPU& cpu);		//0xCB16 RL (HL)
		static void RL_A(CPU& cpu);			//0xCB17 RL A
		static void RR_B(CPU& cpu);			//0xCB18 RR B
		static void RR_C(CPU& cpu);			//0xCB19 RR C
		static void RR_D(CPU& cpu);			//0xCB1A RR D
		static void RR_E(CPU& cpu);			//0xCB1B RR E
		static void RR_H(CPU& cpu);			//0xCB1C RR H
		static void RR_L(CPU& cpu);			//0xCB1D RR L
		static void RR_pHLq(CPU& cpu);		//0xCB1E RR (HL)
		static void RR_A(CPU& cpu);			//0xCB1F RR A

		static void SLA_B(CPU& cpu);		//0xCB20 SLA B
		static void SLA_C(CPU& cpu);		//0xCB21 SLA C
		static void SLA_D(CPU& cpu);		//0xCB22 SLA D
		static void SLA_E(CPU& cpu);		//0xCB23 SLA E
		static void SLA_H(CPU& cpu);		//0xCB24 SLA H
		static void SLA_L(CPU& cpu);		//0xCB25 SLA L
		static void SLA_pHLq(CPU& cpu);		//0xCB26 SLA (HL)
		static void SLA_A(CPU& cpu);		//0xCB27 SLA A
		static void SRA_B(CPU& cpu);		//0xCB28 SRA B
		static void SRA_C(CPU& cpu);		//0xCB29 SRA C
		static void SRA_D(CPU& cpu);		//0xCB2A SRA D
		static void SRA_E(CPU& cpu);		//0xCB2B SRA E
		static void SRA_H(CPU& cpu);		//0xCB2C SRA H
		static void SRA_L(CPU& cpu);		//0xCB2D SRA L
		static void SRA_pHLq(CPU& cpu);		//0xCB2E SRA (HL)
		static void SRA_A(CPU& cpu);		//0xCB2F SRA A

		static void SWAP_B(CPU& cpu);		//0xCB30 SWAP B
		static void SWAP_C(CPU& cpu);		//0xCB31 SWAP C
		static void SWAP_D(CPU& cpu);		//0xCB32 SWAP D
		static void SWAP_E(CPU& cpu);		//0xCB33 SWAP E
		static void SWAP_H(CPU& cpu);		//0xCB34 SWAP H
		static void SWAP_L(CPU& cpu);		//0xCB35 SWAP L
		static void SWAP_pHLq(CPU& cpu);	//0xCB36 SWAP (HL)
		static void SWAP_A(CPU& cpu);		//0xCB37 SWAP A
		static void SRL_B(CPU& cpu);		//0xCB38 SRL B
		static void SRL_C(CPU& cpu);		//0xCB39 SRL C
		static void SRL_D(CPU& cpu);		//0xCB3A SRL D
		static void SRL_E(CPU& cpu);		//0xCB3B SRL E
		static void SRL_H(CPU& cpu);		//0xCB3C SRL H
		static void SRL_L(CPU& cpu);		//0xCB3D SRL L
		static void SRL_pHLq(CPU& cpu);		//0xCB3E SRL (HL)
		static void SRL_A(CPU& cpu);		//0xCB3F SRL A


private:
	static void RLCr(u8& registry, flags& flagRegistry);
	static void RRCr(u8& registry, flags& flagRegistry);
	static void RLr(u8& registry, flags& flagResistry);
	static void RRr(u8& registry, flags& flagRegistry);
	static void SLAr(u8& registry, flags& flagRegistry);
	static void SRAr(u8& registry, flags& flagRegistry);
	static void SWAPr(u8& registry, flags& flagRegistry);
	static void SRLr(u8& registry, flags& flagRegistry);

};

