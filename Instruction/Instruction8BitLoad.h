#pragma once

#include "Instruction.h"
#include "../CPU/CPU.h"
#include "../Registries/Registries.h"

class Instruction8BitLoad : public Instruction
{
private:
		static void LD_Rcd8(CPU& cpu, u8& registry);
		static void LD_pRRqcd8(CPU& cpu, combinedRegistries& registries);
		static void LD_pRRqcR(CPU& cpu, combinedRegistries& addrRegistries, u8& srcRegistry);
		static void LD_RcpRRq(CPU& cpu, combinedRegistries& addrRegistries, u8& dstRegistry);

public:
		Instruction8BitLoad(std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles);
		virtual ~Instruction8BitLoad() = default;
	
		
		static void LD_pBCqcA(CPU& cpu);	//0x02 LD (BC),A
		static void LD_Bcd8(CPU& cpu);		//0x06 LD B,d8
		static void LD_AcpBCq(CPU& cpu);	//0x0A LD A,(BC)
		static void LD_Ccd8(CPU& cpu);		//0x0E LD C,d8

		static void LD_pDEqcA(CPU& cpu);	//0x12 LD (DE),A
		static void LD_Dcd8(CPU& cpu);		//0x16 LD D,d8
		static void LD_AcpDEq(CPU& cpu);	//0x1A LD A,(DE)
		static void LD_Ecd8(CPU& cpu);		//0x1E LD E,d8

		static void LDI_pHLqcA(CPU& cpu);	//0x22 LDI (HL),A
		static void LD_Hcd8(CPU& cpu);		//0x26 LD H,d8
		static void LDI_AcpHLq(CPU& cpu);	//0x2A LDI A,(HL)
		static void LD_Lcd8(CPU& cpu);		//0x2E LD L,d8

		static void LDD_pHLqcA(CPU& cpu);	//0x32 LDD (HL),A
		static void LD_pHLqcd8(CPU& cpu);	//0x36 LD (HL),d8
		static void LDD_AcpHLq(CPU& cpu);	//0x3A LDD A,(HL)
		static void LD_Acd8(CPU& cpu);		//0x3E LD A,d8

		static void LD_BcB(CPU& cpu);		//0x40 LD B,B
		static void LD_BcC(CPU& cpu);		//0x41 LD B,C
		static void LD_BcD(CPU& cpu);		//0x42 LD B,D
		static void LD_BcE(CPU& cpu);		//0x43 LD B,E
		static void LD_BcH(CPU& cpu);		//0x44 LD B,H
		static void LD_BcL(CPU& cpu);		//0x45 LD B,L
		static void LD_BcpHLq(CPU& cpu);	//0x46 LD B,(HL)
		static void LD_BcA(CPU& cpu);		//0x47 LD B,A
		static void LD_CcB(CPU& cpu);		//0x48 LD C,B
		static void LD_CcC(CPU& cpu);		//0x49 LD C,C
		static void LD_CcD(CPU& cpu);		//0x4A LD C,D
		static void LD_CcE(CPU& cpu);		//0x4B LD C,E
		static void LD_CcH(CPU& cpu);		//0x4C LD C,H
		static void LD_CcL(CPU& cpu);		//0x4D LD C,L
		static void LD_CcpHLq(CPU& cpu);	//0x4E LD C,(HL)
		static void LD_CcA(CPU& cpu);		//0x4F LD C,A

		static void LD_DcB(CPU& cpu);		//0x50 LD D,B
		static void LD_DcC(CPU& cpu);		//0x51 LD D,C
		static void LD_DcD(CPU& cpu);		//0x52 LD D,D
		static void LD_DcE(CPU& cpu);		//0x53 LD D,E
		static void LD_DcH(CPU& cpu);		//0x54 LD D,H
		static void LD_DcL(CPU& cpu);		//0x55 LD D,L
		static void LD_DcpHLq(CPU& cpu);	//0x56 LD D,(HL)
		static void LD_DcA(CPU& cpu);		//0x57 LD D,A
		static void LD_EcB(CPU& cpu);		//0x58 LD E,B
		static void LD_EcC(CPU& cpu);		//0x59 LD E,C
		static void LD_EcD(CPU& cpu);		//0x5A LD E,D
		static void LD_EcE(CPU& cpu);		//0x5B LD E,E
		static void LD_EcH(CPU& cpu);		//0x5C LD E,H
		static void LD_EcL(CPU& cpu);		//0x5D LD E,L
		static void LD_EcpHLq(CPU& cpu);	//0x5E LD E,(HL)
		static void LD_EcA(CPU& cpu);		//0x5F LD E,A

		static void LD_HcB(CPU& cpu);		//0x60 LD H,B
		static void LD_HcC(CPU& cpu);		//0x61 LD H,C
		static void LD_HcD(CPU& cpu);		//0x62 LD H,D
		static void LD_HcE(CPU& cpu);		//0x63 LD H,E
		static void LD_HcH(CPU& cpu);		//0x64 LD H,H
		static void LD_HcL(CPU& cpu);		//0x65 LD H,L
		static void LD_HcpHLq(CPU& cpu);	//0x66 LD H,(HL)
		static void LD_HcA(CPU& cpu);		//0x67 LD H,A
		static void LD_LcB(CPU& cpu);		//0x68 LD L,B
		static void LD_LcC(CPU& cpu);		//0x69 LD L,C
		static void LD_LcD(CPU& cpu);		//0x6A LD L,D
		static void LD_LcE(CPU& cpu);		//0x6B LD L,E
		static void LD_LcH(CPU& cpu);		//0x6C LD L,H
		static void LD_LcL(CPU& cpu);		//0x6D LD L,L
		static void LD_LcpHLq(CPU& cpu);	//0x6E LD L,(HL)
		static void LD_LcA(CPU& cpu);		//0x6F LD L,A

		static void LD_pHLqcB(CPU& cpu);	//0x70 LD (HL),B
		static void LD_pHLqcC(CPU& cpu);	//0x71 LD (HL),C
		static void LD_pHLqcD(CPU& cpu);	//0x72 LD (HL),D
		static void LD_pHLqcE(CPU& cpu);	//0x73 LD (HL),E
		static void LD_pHLqcH(CPU& cpu);	//0x74 LD (HL),H
		static void LD_pHLqcL(CPU& cpu);	//0x75 LD (HL),L
		static void LD_pHLqcA(CPU& cpu);	//0x77 LD (HL),A
		static void LD_AcB(CPU& cpu);		//0x78 LD A,B
		static void LD_AcC(CPU& cpu);		//0x79 LD A,C
		static void LD_AcD(CPU& cpu);		//0x7A LD A,D
		static void LD_AcE(CPU& cpu);		//0x7B LD A,E
		static void LD_AcH(CPU& cpu);		//0x7C LD A,H
		static void LD_AcL(CPU& cpu);		//0x7D LD A,L
		static void LD_AcpHLq(CPU& cpu);	//0x7E LD A,(HL)
		static void LD_AcA(CPU& cpu);		//0x7F LD A,A

		static void LDH_pa8qcA(CPU& cpu);	//0xE0 LDH (a8),A
		static void LD_pCqcA(CPU& cpu);		//0xE2 LD (C),A
		static void LD_pa16qcA(CPU& cpu);	//0xEA LDH (a16),A

		static void LDH_Acpa8q(CPU& cpu);	//0xF0 LDH A,(a8)
		static void LD_AcpCq(CPU& cpu);		//0xF2 LD A,(C)
		static void LD_Acpa16q(CPU& cpu);	//0xFA LDH A,(a16)



		
};

