#pragma once

#include "Instruction.h"
#include "../CPU/CPU.h"

class Instruction16BitLoad : public Instruction
{
public:
	Instruction16BitLoad(std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles);
	virtual ~Instruction16BitLoad() = default;

	static void LD_BCcd16(CPU& cpu);	//0x01 LD BC,d16
	static void LD_pa16qcSP(CPU& cpu);	//0x08 LD (a16),SP
	static void LD_DEcd16(CPU& cpu);	//0x11 LD DE,d16
	static void LD_HLcd16(CPU& cpu);	//0x21 LD HL,d16
	static void LD_SPcd16(CPU& cpu);	//0x31 LD SP,d16

	static void POP_BC(CPU& cpu);		//0xC1 POP BC
	static void PUSH_BC(CPU& cpu);		//0xC5 PUSH BC

	static void POP_DE(CPU& cpu);		//0xD1 POP DE
	static void PUSH_DE(CPU& cpu);		//0xD5 PUSH DE

	static void POP_HL(CPU& cpu);		//0xE1 POP HL
	static void PUSH_HL(CPU& cpu);		//0xE5 PUSH HL

	static void POP_AF(CPU& cpu);		//0xF1 POP AF
	static void PUSH_AF(CPU& cpu);		//0xF5 PUSH AF
	static void LDHL_SPcr8(CPU& cpu);	//0xF8 LDHL SP,r8
	static void LD_SPcHL(CPU& cpu);		//LD SP,HL



};

