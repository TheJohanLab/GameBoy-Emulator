#pragma once
#include "Instruction.h"
#include "../CPU/CPU.h"

class InstructionRotateShift : public Instruction
{
	public:
		InstructionRotateShift(std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles);
		virtual ~InstructionRotateShift() = default;

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

		static void SLA_B(CPU& cpu);		//0xCB10 SLA B
		static void SLA_C(CPU& cpu);		//0xCB11 SLA C
		static void SLA_D(CPU& cpu);		//0xCB12 SLA D
		static void SLA_E(CPU& cpu);		//0xCB13 SLA E
		static void SLA_H(CPU& cpu);		//0xCB14 SLA H
		static void SLA_L(CPU& cpu);		//0xCB15 SLA L
		static void SLA_pHLq(CPU& cpu);		//0xCB16 SLA (HL)
		static void SLA_A(CPU& cpu);		//0xCB17 SLA A
		static void SRA_B(CPU& cpu);		//0xCB18 SRA B
		static void SRA_C(CPU& cpu);		//0xCB19 SRA C
		static void SRA_D(CPU& cpu);		//0xCB1A SRA D
		static void SRA_E(CPU& cpu);		//0xCB1B SRA E
		static void SRA_H(CPU& cpu);		//0xCB1C SRA H
		static void SRA_L(CPU& cpu);		//0xCB1D SRA L
		static void SRA_pHLq(CPU& cpu);		//0xCB1E SRA (HL)
		static void SRA_A(CPU& cpu);		//0xCB1F SRA A

private:
	static void RLCr(u8& registry, flags& flagRegistry);
	static void RRCr(u8& registry, flags& flagRegistry);
	static void RLr(u8& registry, flags& flagResistry);
	static void RRr(u8& registry, flags& flagRegistry);
	static void SLAr(u8& registry, flags& flagRegistry);
	static void SRAr(u8& registry, flags& flagRegistry);

};

