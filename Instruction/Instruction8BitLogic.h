#pragma once

#include "Instruction.h"
#include "CPU/CPU.h"

class Instruction8BitLogic : public Instruction
{

	private:
		static void INC_R(CPU& cpu, u8* registry);
		static void DEC_R(CPU& cpu, u8* registry);
		static void ADD_RcR(CPU& cpu, u8* additionalValue, u8* dstRegistry);
		static void ADC_RcR(CPU& cpu, u8* additionalValue, u8* dstRegistry);
		static void SUB_RcR(CPU& cpu, u8* additionalValue, u8* dstRegistry);
		static void SBC_RcR(CPU& cpu, u8* additionalValue, u8* dstRegistry);
		static void AND_R(CPU& cpu, u8* additionalValue, u8* dstRegistry);
		static void XOR_R(CPU& cpu, u8* additionalValue, u8* dstRegistry);
		static void OR_R(CPU& cpu, u8* additionalValue, u8* dstRegistry);
		static void CP_R(CPU& cpu, u8* cmpRegistry, u8 ARegistry);

	public:
		Instruction8BitLogic(const char* name, u8 (*pInstruction)(CPU & cpu), u8 clockCycles);
		virtual ~Instruction8BitLogic() = default;

		static u8 INC_B(CPU& cpu);		//0x04 INC B
		static u8 DEC_B(CPU& cpu);		//0x05 DEC B
		static u8 INC_C(CPU& cpu);		//0x0C INC C
		static u8 DEC_C(CPU& cpu);		//0x0D DEC C
		
		static u8 INC_D(CPU& cpu);		//0x14 INC D
		static u8 DEC_D(CPU& cpu);		//0x15 DEC D
		static u8 INC_E(CPU& cpu);		//0x1C INC E
		static u8 DEC_E(CPU& cpu);		//0x1D DEC E

		static u8 INC_H(CPU& cpu);		//0x24 INC H
		static u8 DEC_H(CPU& cpu);		//0x25 DEC H
		static u8 DAA(CPU& cpu);			//0x27 DAA
		static u8 INC_L(CPU& cpu);		//0x2C INC L
		static u8 DEC_L(CPU& cpu);		//0x2D DEC L
		static u8 CPL(CPU& cpu);			//0x2F CPL

		static u8 INC_pHLq(CPU& cpu);		//0x34 INC (HL)
		static u8 DEC_pHLq(CPU& cpu);		//0x35 DEC (HL)
		static u8 SCF(CPU& cpu);			//0x37 SCF
		static u8 INC_A(CPU& cpu);		//0x3C INC A
		static u8 DEC_A(CPU& cpu);		//0x3D DEC A
		static u8 CCF(CPU& cpu);			//0x3F CCF

		static u8 ADD_AcB(CPU& cpu);		//0x80 ADD A,B
		static u8 ADD_AcC(CPU& cpu);		//0x81 ADD A,C
		static u8 ADD_AcD(CPU& cpu);		//0x82 ADD A,D
		static u8 ADD_AcE(CPU& cpu);		//0x83 ADD A,E
		static u8 ADD_AcH(CPU& cpu);		//0x84 ADD A,H
		static u8 ADD_AcL(CPU& cpu);		//0x85 ADD A,L
		static u8 ADD_AcpHLq(CPU& cpu);	//0x86 ADD A,(HL)
		static u8 ADD_AcA(CPU& cpu);		//0x87 ADD A,A
		static u8 ADC_AcB(CPU& cpu);		//0x88 ADC A,B
		static u8 ADC_AcC(CPU& cpu);		//0x89 ADC A,C
		static u8 ADC_AcD(CPU& cpu);		//0x8A ADC A,D
		static u8 ADC_AcE(CPU& cpu);		//0x8B ADC A,E
		static u8 ADC_AcH(CPU& cpu);		//0x8C ADC A,H
		static u8 ADC_AcL(CPU& cpu);		//0x8D ADC A,L
		static u8 ADC_AcpHLq(CPU& cpu);	//0x8E ADC A,(HL)
		static u8 ADC_AcA(CPU& cpu);		//0x8F ADC A,A

		static u8 SUB_B(CPU& cpu);		//0x90 SUB B
		static u8 SUB_C(CPU& cpu);		//0x91 SUB C
		static u8 SUB_D(CPU& cpu);		//0x92 SUB D
		static u8 SUB_E(CPU& cpu);		//0x93 SUB E
		static u8 SUB_H(CPU& cpu);		//0x94 SUB H
		static u8 SUB_L(CPU& cpu);		//0x95 SUB L
		static u8 SUB_pHLq(CPU& cpu);		//0x96 SUB (HL)
		static u8 SUB_A(CPU& cpu);		//0x97 SUB A
		static u8 SBC_AcB(CPU& cpu);		//0x98 SBC A,B
		static u8 SBC_AcC(CPU& cpu);		//0x99 SBC A,C
		static u8 SBC_AcD(CPU& cpu);		//0x9A SBC A,D
		static u8 SBC_AcE(CPU& cpu);		//0x9B SBC A,E
		static u8 SBC_AcH(CPU& cpu);		//0x9C SBC A,H
		static u8 SBC_AcL(CPU& cpu);		//0x9D SBC A,L
		static u8 SBC_AcpHLq(CPU& cpu);	//0x9E SBC A,(HL)
		static u8 SBC_AcA(CPU& cpu);		//0x9F SBC A,A

		static u8 AND_B(CPU& cpu);		//0xA0 AND B
		static u8 AND_C(CPU& cpu);		//0xA1 AND C
		static u8 AND_D(CPU& cpu);		//0xA2 AND D
		static u8 AND_E(CPU& cpu);		//0xA3 AND E
		static u8 AND_H(CPU& cpu);		//0xA4 AND H
		static u8 AND_L(CPU& cpu);		//0xA5 AND L
		static u8 AND_pHLq(CPU& cpu);		//0xA6 AND (HL)
		static u8 AND_A(CPU& cpu);		//0xA7 AND A
		static u8 XOR_B(CPU& cpu);		//0xA8 XOR B
		static u8 XOR_C(CPU& cpu);		//0xA9 XOR C
		static u8 XOR_D(CPU& cpu);		//0xAA XOR D
		static u8 XOR_E(CPU& cpu);		//0xAB XOR E
		static u8 XOR_H(CPU& cpu);		//0xAC XOR H
		static u8 XOR_L(CPU& cpu);		//0xAD XOR L
		static u8 XOR_pHLq(CPU& cpu);		//0xAE XOR (HL)
		static u8 XOR_A(CPU& cpu);		//0xAF XOR A

		static u8 OR_B(CPU& cpu);			//0xB0 OR B
		static u8 OR_C(CPU& cpu);			//0xB1 OR C
		static u8 OR_D(CPU& cpu);			//0xB2 OR D
		static u8 OR_E(CPU& cpu);			//0xB3 OR E
		static u8 OR_H(CPU& cpu);			//0xB4 OR H
		static u8 OR_L(CPU& cpu);			//0xB5 OR L
		static u8 OR_pHLq(CPU& cpu);		//0xB6 OR (HL)
		static u8 OR_A(CPU& cpu);			//0xB7 OR A
		static u8 CP_B(CPU& cpu);			//0xB8 CP B
		static u8 CP_C(CPU& cpu);			//0xB9 CP C
		static u8 CP_D(CPU& cpu);			//0xBA CP D
		static u8 CP_E(CPU& cpu);			//0xBB CP E
		static u8 CP_H(CPU& cpu);			//0xBC CP H
		static u8 CP_L(CPU& cpu);			//0xBD CP L
		static u8 CP_pHLq(CPU& cpu);		//0xBE CP (HL)
		static u8 CP_A(CPU& cpu);			//0xBF CP A

		static u8 ADD_Acd8(CPU& cpu);		//0xC6 ADD A,d8
		static u8 ADC_Acd8(CPU& cpu);		//0xCE ADC A,d8

		static u8 SUB_d8(CPU& cpu);		//0xD6 DUB d8
		static u8 SBC_Acd8(CPU& cpu);		//0xDE SBC A,d8

		static u8 AND_d8(CPU& cpu);		//0xE6 AND d8
		static u8 XOR_d8(CPU& cpu);		//0xEE XOR d8

		static u8 OR_d8(CPU& cpu);		//0xF6 OR d8
		static u8 CP_d8(CPU& cpu);		//0xFE CP d8
		
};

