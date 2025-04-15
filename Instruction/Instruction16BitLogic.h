#pragma once

#include "Instruction.h"
#include "CPU/CPU.h"

class Instruction16BitLogic : public Instruction
{
private:
	static void INC_RR(CPU& cpu, u16& doubleRegistry);
	static void DEC_RR(CPU& cpu, u16& doubleRegistry);
	static void ADD_HLcRR(CPU& cpu, const u16& doubleRegistry);

	public:
		Instruction16BitLogic(const char* name, std::function<u8(CPU& cpu)> instruction, Registries& reg, std::shared_ptr<Bus> bus);
		virtual ~Instruction16BitLogic() = default;

		static u8 INC_BC(CPU& cpu);		//0x03 INC BC
		static u8 ADD_HLcBC(CPU& cpu);	//0x09 ADD HL,BC
		static u8 DEC_BC(CPU& cpu);		//0x0B DEC BC

		static u8 INC_DE(CPU& cpu);		//0x13 INC DE
		static u8 ADD_HLcDE(CPU& cpu);	//0x19 ADD HL,DE
		static u8 DEC_DE(CPU& cpu);		//0x1B DEC DE

		static u8 INC_HL(CPU& cpu);		//0x23 INC HL
		static u8 ADD_HLcHL(CPU& cpu);	//0x29 ADD HL,HL
		static u8 DEC_HL(CPU& cpu);		//0x2B DEC HL

		static u8 INC_SP(CPU& cpu);		//0x33 INC SP
		static u8 ADD_HLcSP(CPU& cpu);	//0x39 ADD HL,SP
		static u8 DEC_SP(CPU& cpu);		//0x3B DEC SP

		static u8 ADD_SPcr8(CPU& cpu);	//0xE8 ADD SP,r8
};

