#pragma once

#include "Instruction.h"
#include "CPU/CPU.h"
#include "Registries/Registries.h"

class Instruction8BitLoad : public Instruction
{
private:
		static void LD_Rcd8(CPU& cpu, u8& registry);
		static void LD_pRRqcd8(CPU& cpu, combinedRegistries& registries);
		static void LD_pRRqcR(CPU& cpu, combinedRegistries& addrRegistries, u8& srcRegistry);
		static void LD_RcpRRq(CPU& cpu, combinedRegistries& addrRegistries, u8& dstRegistry);

public:
		//Instruction8BitLoad(const char* name, u8(*pInstruction)(CPU & cpu), u8 clockCycles);
		Instruction8BitLoad(const char* name, std::function<u8(CPU& cpu)> instruction, Registries& reg, std::shared_ptr<Bus> bus);
		virtual ~Instruction8BitLoad() = default;

		static u8 LD_pBCqcA(CPU& cpu);	//0x02 LD (BC),A
		static u8 LD_Bcd8(CPU& cpu);		//0x06 LD B,d8
		static u8 LD_AcpBCq(CPU& cpu);	//0x0A LD A,(BC)
		static u8 LD_Ccd8(CPU& cpu);		//0x0E LD C,d8

		static u8 LD_pDEqcA(CPU& cpu);	//0x12 LD (DE),A
		static u8 LD_Dcd8(CPU& cpu);		//0x16 LD D,d8
		static u8 LD_AcpDEq(CPU& cpu);	//0x1A LD A,(DE)
		static u8 LD_Ecd8(CPU& cpu);		//0x1E LD E,d8

		static u8 LDI_pHLqcA(CPU& cpu);	//0x22 LDI (HL),A
		static u8 LD_Hcd8(CPU& cpu);		//0x26 LD H,d8
		static u8 LDI_AcpHLq(CPU& cpu);	//0x2A LDI A,(HL)
		static u8 LD_Lcd8(CPU& cpu);		//0x2E LD L,d8

		static u8 LDD_pHLqcA(CPU& cpu);	//0x32 LDD (HL),A
		static u8 LD_pHLqcd8(CPU& cpu);	//0x36 LD (HL),d8
		static u8 LDD_AcpHLq(CPU& cpu);	//0x3A LDD A,(HL)
		static u8 LD_Acd8(CPU& cpu);		//0x3E LD A,d8

		static u8 LD_BcB(CPU& cpu);		//0x40 LD B,B
		static u8 LD_BcC(CPU& cpu);		//0x41 LD B,C
		static u8 LD_BcD(CPU& cpu);		//0x42 LD B,D
		static u8 LD_BcE(CPU& cpu);		//0x43 LD B,E
		static u8 LD_BcH(CPU& cpu);		//0x44 LD B,H
		static u8 LD_BcL(CPU& cpu);		//0x45 LD B,L
		static u8 LD_BcpHLq(CPU& cpu);	//0x46 LD B,(HL)
		static u8 LD_BcA(CPU& cpu);		//0x47 LD B,A
		static u8 LD_CcB(CPU& cpu);		//0x48 LD C,B
		static u8 LD_CcC(CPU& cpu);		//0x49 LD C,C
		static u8 LD_CcD(CPU& cpu);		//0x4A LD C,D
		static u8 LD_CcE(CPU& cpu);		//0x4B LD C,E
		static u8 LD_CcH(CPU& cpu);		//0x4C LD C,H
		static u8 LD_CcL(CPU& cpu);		//0x4D LD C,L
		static u8 LD_CcpHLq(CPU& cpu);	//0x4E LD C,(HL)
		static u8 LD_CcA(CPU& cpu);		//0x4F LD C,A

		static u8 LD_DcB(CPU& cpu);		//0x50 LD D,B
		static u8 LD_DcC(CPU& cpu);		//0x51 LD D,C
		static u8 LD_DcD(CPU& cpu);		//0x52 LD D,D
		static u8 LD_DcE(CPU& cpu);		//0x53 LD D,E
		static u8 LD_DcH(CPU& cpu);		//0x54 LD D,H
		static u8 LD_DcL(CPU& cpu);		//0x55 LD D,L
		static u8 LD_DcpHLq(CPU& cpu);	//0x56 LD D,(HL)
		static u8 LD_DcA(CPU& cpu);		//0x57 LD D,A
		static u8 LD_EcB(CPU& cpu);		//0x58 LD E,B
		static u8 LD_EcC(CPU& cpu);		//0x59 LD E,C
		static u8 LD_EcD(CPU& cpu);		//0x5A LD E,D
		static u8 LD_EcE(CPU& cpu);		//0x5B LD E,E
		static u8 LD_EcH(CPU& cpu);		//0x5C LD E,H
		static u8 LD_EcL(CPU& cpu);		//0x5D LD E,L
		static u8 LD_EcpHLq(CPU& cpu);	//0x5E LD E,(HL)
		static u8 LD_EcA(CPU& cpu);		//0x5F LD E,A

		static u8 LD_HcB(CPU& cpu);		//0x60 LD H,B
		static u8 LD_HcC(CPU& cpu);		//0x61 LD H,C
		static u8 LD_HcD(CPU& cpu);		//0x62 LD H,D
		static u8 LD_HcE(CPU& cpu);		//0x63 LD H,E
		static u8 LD_HcH(CPU& cpu);		//0x64 LD H,H
		static u8 LD_HcL(CPU& cpu);		//0x65 LD H,L
		static u8 LD_HcpHLq(CPU& cpu);	//0x66 LD H,(HL)
		static u8 LD_HcA(CPU& cpu);		//0x67 LD H,A
		static u8 LD_LcB(CPU& cpu);		//0x68 LD L,B
		static u8 LD_LcC(CPU& cpu);		//0x69 LD L,C
		static u8 LD_LcD(CPU& cpu);		//0x6A LD L,D
		static u8 LD_LcE(CPU& cpu);		//0x6B LD L,E
		static u8 LD_LcH(CPU& cpu);		//0x6C LD L,H
		static u8 LD_LcL(CPU& cpu);		//0x6D LD L,L
		static u8 LD_LcpHLq(CPU& cpu);	//0x6E LD L,(HL)
		static u8 LD_LcA(CPU& cpu);		//0x6F LD L,A

		static u8 LD_pHLqcB(CPU& cpu);	//0x70 LD (HL),B
		static u8 LD_pHLqcC(CPU& cpu);	//0x71 LD (HL),C
		static u8 LD_pHLqcD(CPU& cpu);	//0x72 LD (HL),D
		static u8 LD_pHLqcE(CPU& cpu);	//0x73 LD (HL),E
		static u8 LD_pHLqcH(CPU& cpu);	//0x74 LD (HL),H
		static u8 LD_pHLqcL(CPU& cpu);	//0x75 LD (HL),L
		static u8 LD_pHLqcA(CPU& cpu);	//0x77 LD (HL),A
		static u8 LD_AcB(CPU& cpu);		//0x78 LD A,B
		static u8 LD_AcC(CPU& cpu);		//0x79 LD A,C
		static u8 LD_AcD(CPU& cpu);		//0x7A LD A,D
		static u8 LD_AcE(CPU& cpu);		//0x7B LD A,E
		static u8 LD_AcH(CPU& cpu);		//0x7C LD A,H
		static u8 LD_AcL(CPU& cpu);		//0x7D LD A,L
		static u8 LD_AcpHLq(CPU& cpu);	//0x7E LD A,(HL)
		static u8 LD_AcA(CPU& cpu);		//0x7F LD A,A

		static u8 LDH_pa8qcA(CPU& cpu);	//0xE0 LDH (a8),A
		static u8 LD_pCqcA(CPU& cpu);		//0xE2 LD (C),A
		static u8 LD_pa16qcA(CPU& cpu);	//0xEA LDH (a16),A

		static u8 LDH_Acpa8q(CPU& cpu);	//0xF0 LDH A,(a8)
		static u8 LD_AcpCq(CPU& cpu);		//0xF2 LD A,(C)
		static u8 LD_Acpa16q(CPU& cpu);	//0xFA LDH A,(a16)



		
};

