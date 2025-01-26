#pragma once

#include "Instruction.h"
#include "CPU/CPU.h"
#include "Registries/Registries.h"

class Instruction16BitLoad : public Instruction
{
private:
	static void LD_RRcd16(CPU& cpu, combinedRegistries& registries);
	static void LD_RRcd16(CPU& cpu, u16* registry);
	static void PUSH_RR(CPU& cpu, combinedRegistries& registries);
	static void POP_RR(CPU& cpu, combinedRegistries& registries);

public:
	Instruction16BitLoad(const char* name, u8 (*pInstruction)(CPU & cpu), u8 clockCycles);
	virtual ~Instruction16BitLoad() = default;

	static u8 LD_BCcd16(CPU& cpu);	//0x01 LD BC,d16
	static u8 LD_pa16qcSP(CPU& cpu);	//0x08 LD (a16),SP
	static u8 LD_DEcd16(CPU& cpu);	//0x11 LD DE,d16
	static u8 LD_HLcd16(CPU& cpu);	//0x21 LD HL,d16
	static u8 LD_SPcd16(CPU& cpu);	//0x31 LD SP,d16

	static u8 POP_BC(CPU& cpu);		//0xC1 POP BC
	static u8 PUSH_BC(CPU& cpu);		//0xC5 PUSH BC

	static u8 POP_DE(CPU& cpu);		//0xD1 POP DE
	static u8 PUSH_DE(CPU& cpu);		//0xD5 PUSH DE

	static u8 POP_HL(CPU& cpu);		//0xE1 POP HL
	static u8 PUSH_HL(CPU& cpu);		//0xE5 PUSH HL

	static u8 POP_AF(CPU& cpu);		//0xF1 POP AF
	static u8 PUSH_AF(CPU& cpu);		//0xF5 PUSH AF
	static u8 LDHL_SPcr8(CPU& cpu);	//0xF8 LDHL SP,r8
	static u8 LD_SPcHL(CPU& cpu);		//0xF9 LD SP,HL



};

