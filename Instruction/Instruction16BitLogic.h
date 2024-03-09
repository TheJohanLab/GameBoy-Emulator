#pragma once

#include "Instruction.h"
#include "../CPU/CPU.h"

class Instruction16BitLogic : public Instruction
{
private:
	static void INC_RR(CPU& cpu, combinedRegistries* registries);
	static void DEC_RR(CPU& cpu, combinedRegistries* registries);
	static void ADD_HLcRR(CPU& cpu, combinedRegistries* registries);
	static void ADD_HLcRR(CPU& cpu, u16 registriesValue);

	public:
		Instruction16BitLogic(std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles);
		virtual ~Instruction16BitLogic() = default;

		static void INC_BC(CPU& cpu);		//0x03 INC BC
		static void ADD_HLcBC(CPU& cpu);	//0x09 ADD HL,BC
		static void DEC_BC(CPU& cpu);		//0x0B DEC BC

		static void INC_DE(CPU& cpu);		//0x13 INC DE
		static void ADD_HLcDE(CPU& cpu);	//0x19 ADD HL,DE
		static void DEC_DE(CPU& cpu);		//0x1B DEC DE

		static void INC_HL(CPU& cpu);		//0x23 INC HL
		static void ADD_HLcHL(CPU& cpu);	//0x29 ADD HL,HL
		static void DEC_HL(CPU& cpu);		//0x2B DEC HL

		static void INC_SP(CPU& cpu);		//0x33 INC SP
		static void ADD_HLcSP(CPU& cpu);	//0x39 ADD HL,SP
		static void DEC_SP(CPU& cpu);		//0x3B DEC SP

		static void ADD_SPcr8(CPU& cpu);	//0xE8 ADD SP,r8
};

