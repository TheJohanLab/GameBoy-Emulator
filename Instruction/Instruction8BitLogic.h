#pragma once

#include "Instruction.h"
#include "../CPU/CPU.h"

class Instruction8BitLogic : public Instruction
{
	public:
		Instruction8BitLogic(std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles);
		virtual ~Instruction8BitLogic() = default;

		static void INC_B(CPU& cpu);		//0x04 INC B
		static void DEC_B(CPU& cpu);		//0x05 DEC B
		static void INC_C(CPU& cpu);		//0x0C INC C
		static void DEC_C(CPU& cpu);		//0x0D DEC C
		
		static void INC_D(CPU& cpu);		//0x14 INC D
		static void DEC_D(CPU& cpu);		//0x15 DEC D
		static void INC_E(CPU& cpu);		//0x1C INC E
		static void DEC_E(CPU& cpu);		//0x1D DEC E

		static void INC_H(CPU& cpu);		//0x24 INC H
		static void DEC_H(CPU& cpu);		//0x25 DEC H
		static void DAA(CPU& cpu);			//0x27 DAA
		static void INC_L(CPU& cpu);		//0x2C INC L
		static void DEC_L(CPU& cpu);		//0x2D DEC L
		static void CPL(CPU& cpu);			//0x2F CPL

		static void INC_pHLq(CPU& cpu);		//0x34 INC (HL)
		static void DEC_pHLq(CPU& cpu);		//0x35 DEC (HL)
		static void SCF(CPU& cpu);			//0x37 SCF
		static void INC_A(CPU& cpu);		//0x3C INC A
		static void DEC_A(CPU& cpu);		//0x3D DEC A
		static void CCF(CPU& cpu);			//0x3F CCF

		static void ADD_AcB(CPU& cpu);		//0x80 ADD A,B
		static void ADD_AcC(CPU& cpu);		//0x81 ADD A,C
		static void ADD_AcD(CPU& cpu);		//0x82 ADD A,D
		static void ADD_AcE(CPU& cpu);		//0x83 ADD A,E
		static void ADD_AcH(CPU& cpu);		//0x84 ADD A,H
		static void ADD_AcL(CPU& cpu);		//0x85 ADD A,L
		static void ADD_AcpHLq(CPU& cpu);	//0x86 ADD A,(HL)
		static void ADD_AcA(CPU& cpu);		//0x87 ADD A,A
		static void ADC_AcB(CPU& cpu);		//0x88 ADC A,B
		static void ADC_AcC(CPU& cpu);		//0x89 ADC A,C
		static void ADC_AcD(CPU& cpu);		//0x8A ADC A,D
		static void ADC_AcE(CPU& cpu);		//0x8B ADC A,E
		static void ADC_AcH(CPU& cpu);		//0x8C ADC A,H
		static void ADC_AcL(CPU& cpu);		//0x8D ADC A,L
		static void ADC_AcpHLq(CPU& cpu);	//0x8E ADC A,(HL)
		static void ADC_AcA(CPU& cpu);		//0x8F ADC A,A

		static void SUB_B(CPU& cpu);		//0x90 SUB B
		static void SUB_C(CPU& cpu);		//0x91 SUB C
		static void SUB_D(CPU& cpu);		//0x92 SUB D
		static void SUB_E(CPU& cpu);		//0x93 SUB E
		static void SUB_H(CPU& cpu);		//0x94 SUB H
		static void SUB_L(CPU& cpu);		//0x95 SUB L
		static void SUB_pHLq(CPU& cpu);		//0x96 SUB (HL)
		static void SUB_A(CPU& cpu);		//0x97 SUB A
		static void SBC_AcB(CPU& cpu);		//0x98 SBC A,B
		static void SBC_AcC(CPU& cpu);		//0x99 SBC A,C
		static void SBC_AcD(CPU& cpu);		//0x9A SBC A,D
		static void SBC_AcE(CPU& cpu);		//0x9B SBC A,E
		static void SBC_AcH(CPU& cpu);		//0x9C SBC A,H
		static void SBC_AcL(CPU& cpu);		//0x9D SBC A,L
		static void SBC_AcpHLq(CPU& cpu);	//0x9E SBC A,(HL)
		static void SBC_AcA(CPU& cpu);		//0x9F SBC A,A

		static void AND_B(CPU& cpu);		//0xA0 AND B
		static void AND_C(CPU& cpu);		//0xA1 AND C
		static void AND_D(CPU& cpu);		//0xA2 AND D
		static void AND_E(CPU& cpu);		//0xA3 AND E
		static void AND_H(CPU& cpu);		//0xA4 AND H
		static void AND_L(CPU& cpu);		//0xA5 AND L
		static void AND_pHLq(CPU& cpu);		//0xA6 AND (HL)
		static void AND_A(CPU& cpu);		//0xA7 AND A
		static void XOR_B(CPU& cpu);		//0xA8 XOR B
		static void XOR_C(CPU& cpu);		//0xA9 XOR C
		static void XOR_D(CPU& cpu);		//0xAA XOR D
		static void XOR_E(CPU& cpu);		//0xAB XOR E
		static void XOR_H(CPU& cpu);		//0xAC XOR H
		static void XOR_L(CPU& cpu);		//0xAD XOR L
		static void XOR_pHLq(CPU& cpu);		//0xAE XOR (HL)
		static void XOR_A(CPU& cpu);		//0xAF XOR A

		static void OR_B(CPU& cpu);			//0xB0 OR B
		static void OR_C(CPU& cpu);			//0xB1 OR C
		static void OR_D(CPU& cpu);			//0xB2 OR D
		static void OR_E(CPU& cpu);			//0xB3 OR E
		static void OR_H(CPU& cpu);			//0xB4 OR H
		static void OR_L(CPU& cpu);			//0xB5 OR L
		static void OR_pHLq(CPU& cpu);		//0xB6 OR (HL)
		static void OR_A(CPU& cpu);			//0xB7 OR A
		static void CP_B(CPU& cpu);			//0xB8 CP B
		static void CP_C(CPU& cpu);			//0xB9 CP C
		static void CP_D(CPU& cpu);			//0xBA CP D
		static void CP_E(CPU& cpu);			//0xBB CP E
		static void CP_H(CPU& cpu);			//0xBC CP H
		static void CP_L(CPU& cpu);			//0xBD CP L
		static void CP_pHLq(CPU& cpu);		//0xBE CP (HL)
		static void CP_A(CPU& cpu);			//0xBF CP A

		static void ADD_Acd8(CPU& cpu);		//0xC6 ADD A,d8
		static void ADC_Acd8(CPU& cpu);		//0xCE ADC A,d8

		static void SUB_d8(CPU& cpu);		//0xD6 DUB d8
		static void SBC_Acd8(CPU& cpu);		//0xDE SBC A,d8

		static void AND_d8(CPU& cpu);		//0xE6 AND d8
		static void XOR_d8(CPU& cpu);		//0xEE XOR d8

		static void OR_d8(CPU& cpu);		//0xF6 OR d8
		static void CP_d8(CPU& cpu);		//0xFE CP d8
		
};

