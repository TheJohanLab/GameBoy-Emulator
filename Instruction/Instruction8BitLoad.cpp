#include "pch.h"

#include "Instruction8BitLoad.h"



Instruction8BitLoad::Instruction8BitLoad(const char* name, u8(*pInstruction)(CPU& cpu), u8 clockCycles)
	:Instruction(name, pInstruction, clockCycles)
{
}

u8 Instruction8BitLoad::LD_pBCqcA(CPU& cpu)
{
	u8* Aregistry = cpu.getRegistries("A");
	combinedRegistries* BCRegistries = cpu.getCombinedRegistries("BC");

	LD_pRRqcR(cpu, *BCRegistries, *Aregistry);

	return 8;
}

u8 Instruction8BitLoad::LD_Bcd8(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	LD_Rcd8(cpu, *registry);

	return 8;
}

u8 Instruction8BitLoad::LD_AcpBCq(CPU& cpu)
{
	u8* destRegistry = cpu.getRegistries("A");
	combinedRegistries* addrRegistries = cpu.getCombinedRegistries("BC");
	LD_RcpRRq(cpu, *addrRegistries, *destRegistry);

	return 8;
}

u8 Instruction8BitLoad::LD_Ccd8(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	LD_Rcd8(cpu, *registry);

	return 8;
}

u8 Instruction8BitLoad::LD_pDEqcA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	combinedRegistries* addrRegistries = cpu.getCombinedRegistries("DE");
	LD_pRRqcR(cpu, *addrRegistries, *registry);

	return 8;
}

u8 Instruction8BitLoad::LD_Dcd8(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	LD_Rcd8(cpu, *registry);

	return 8;
}

u8 Instruction8BitLoad::LD_AcpDEq(CPU& cpu)
{
	u8* destRegistry = cpu.getRegistries("A");
	combinedRegistries* addrRegistries = cpu.getCombinedRegistries("DE");
	LD_RcpRRq(cpu, *addrRegistries, *destRegistry);

	return 8;
}

u8 Instruction8BitLoad::LD_Ecd8(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	LD_Rcd8(cpu, *registry);

	return 8;
}

u8 Instruction8BitLoad::LDI_pHLqcA(CPU& cpu)
{
	u8* Aregistry = cpu.getRegistries("A");
	combinedRegistries* HLRegistries = cpu.getCombinedRegistries("HL");
	LD_pRRqcR(cpu, *HLRegistries, *Aregistry);
	(*HLRegistries)++;

	return 8;
}

u8 Instruction8BitLoad::LD_Hcd8(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	LD_Rcd8(cpu, *registry);

	return 8;
}

u8 Instruction8BitLoad::LDI_AcpHLq(CPU& cpu)
{
	u8* ARegistry = cpu.getRegistries("A");
	combinedRegistries* HLRegistries = cpu.getCombinedRegistries("HL");
	LD_RcpRRq(cpu, *HLRegistries, *ARegistry);
	(*HLRegistries)++;

	return 8;
}

u8 Instruction8BitLoad::LD_Lcd8(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	LD_Rcd8(cpu, *registry);

	return 8;
}

u8 Instruction8BitLoad::LDD_pHLqcA(CPU& cpu)
{
	u8* Aregistry = cpu.getRegistries("A");
	combinedRegistries* HLRegistries = cpu.getCombinedRegistries("HL");
	LD_pRRqcR(cpu, *HLRegistries, *Aregistry);
	(*HLRegistries)--;

	return 8;
}

u8 Instruction8BitLoad::LD_pHLqcd8(CPU& cpu)
{
	combinedRegistries* HLRegistry = cpu.getCombinedRegistries("HL");
	LD_pRRqcd8(cpu, *HLRegistry);

	return 12;
}

u8 Instruction8BitLoad::LDD_AcpHLq(CPU& cpu)
{
	u8* ARegistry = cpu.getRegistries("A");
	combinedRegistries* HLRegistries = cpu.getCombinedRegistries("HL");
	LD_RcpRRq(cpu, *HLRegistries, *ARegistry);
	(*HLRegistries)--;

	return 8;
}

u8 Instruction8BitLoad::LD_Acd8(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	LD_Rcd8(cpu, *registry);

	return 8;
}

u8 Instruction8BitLoad::LD_BcB(CPU& cpu)
{
	//TODO Verifier cette instruction
	u8* dstRegistry = cpu.getRegistries("B");
	u8* srcRegistry = cpu.getRegistries("B");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_BcC(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("B");
	u8* srcRegistry = cpu.getRegistries("C");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_BcD(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("B");
	u8* srcRegistry = cpu.getRegistries("D");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_BcE(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("B");
	u8* srcRegistry = cpu.getRegistries("E");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_BcH(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("B");
	u8* srcRegistry = cpu.getRegistries("H");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_BcL(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("B");
	u8* srcRegistry = cpu.getRegistries("L");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_BcpHLq(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("B");
	combinedRegistries* addrRegistries = cpu.getCombinedRegistries("HL");
	LD_pRRqcR(cpu, *addrRegistries, *dstRegistry);

	return 8;
}

u8 Instruction8BitLoad::LD_BcA(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("B");
	u8* srcRegistry = cpu.getRegistries("A");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_CcB(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("C");
	u8* srcRegistry = cpu.getRegistries("B");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_CcC(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("C");
	u8* srcRegistry = cpu.getRegistries("C");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_CcD(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("C");
	u8* srcRegistry = cpu.getRegistries("D");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_CcE(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("C");
	u8* srcRegistry = cpu.getRegistries("E");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_CcH(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("C");
	u8* srcRegistry = cpu.getRegistries("H");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_CcL(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("C");
	u8* srcRegistry = cpu.getRegistries("L");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_CcpHLq(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("C");
	combinedRegistries* addrRegistries = cpu.getCombinedRegistries("HL");
	LD_pRRqcR(cpu, *addrRegistries, *dstRegistry);

	return 8;
}

u8 Instruction8BitLoad::LD_CcA(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("C");
	u8* srcRegistry = cpu.getRegistries("A");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_DcB(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("D");
	u8* srcRegistry = cpu.getRegistries("B");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_DcC(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("D");
	u8* srcRegistry = cpu.getRegistries("C");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_DcD(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("D");
	u8* srcRegistry = cpu.getRegistries("D");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_DcE(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("D");
	u8* srcRegistry = cpu.getRegistries("E");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_DcH(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("D");
	u8* srcRegistry = cpu.getRegistries("H");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_DcL(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("D");
	u8* srcRegistry = cpu.getRegistries("L");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_DcpHLq(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("D");
	combinedRegistries* addrRegistries = cpu.getCombinedRegistries("HL");
	LD_pRRqcR(cpu, *addrRegistries, *dstRegistry);

	return 8;
}

u8 Instruction8BitLoad::LD_DcA(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("D");
	u8* srcRegistry = cpu.getRegistries("A");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_EcB(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("E");
	u8* srcRegistry = cpu.getRegistries("B");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_EcC(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("E");
	u8* srcRegistry = cpu.getRegistries("C");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_EcD(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("E");
	u8* srcRegistry = cpu.getRegistries("D");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_EcE(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("E");
	u8* srcRegistry = cpu.getRegistries("E");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_EcH(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("E");
	u8* srcRegistry = cpu.getRegistries("H");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_EcL(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("E");
	u8* srcRegistry = cpu.getRegistries("L");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_EcpHLq(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("E");
	combinedRegistries* addrRegistries = cpu.getCombinedRegistries("HL");
	LD_pRRqcR(cpu, *addrRegistries, *dstRegistry);

	return 8;
}

u8 Instruction8BitLoad::LD_EcA(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("E");
	u8* srcRegistry = cpu.getRegistries("A");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_HcB(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("H");
	u8* srcRegistry = cpu.getRegistries("B");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_HcC(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("H");
	u8* srcRegistry = cpu.getRegistries("C");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_HcD(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("H");
	u8* srcRegistry = cpu.getRegistries("D");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_HcE(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("H");
	u8* srcRegistry = cpu.getRegistries("E");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_HcH(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("H");
	u8* srcRegistry = cpu.getRegistries("B");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_HcL(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("H");
	u8* srcRegistry = cpu.getRegistries("L");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_HcpHLq(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("H");
	combinedRegistries* addrRegistries = cpu.getCombinedRegistries("HL");
	LD_pRRqcR(cpu, *addrRegistries, *dstRegistry);

	return 8;
}

u8 Instruction8BitLoad::LD_HcA(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("H");
	u8* srcRegistry = cpu.getRegistries("A");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_LcB(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("L");
	u8* srcRegistry = cpu.getRegistries("B");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_LcC(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("L");
	u8* srcRegistry = cpu.getRegistries("C");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_LcD(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("L");
	u8* srcRegistry = cpu.getRegistries("D");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_LcE(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("L");
	u8* srcRegistry = cpu.getRegistries("E");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_LcH(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("L");
	u8* srcRegistry = cpu.getRegistries("H");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_LcL(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("L");
	u8* srcRegistry = cpu.getRegistries("L");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_LcpHLq(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("L");
	combinedRegistries* addrRegistries = cpu.getCombinedRegistries("HL");
	LD_pRRqcR(cpu, *addrRegistries, *dstRegistry);

	return 8;
}

u8 Instruction8BitLoad::LD_LcA(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("L");
	u8* srcRegistry = cpu.getRegistries("A");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_pHLqcB(CPU& cpu)
{
	u8* srcRegistry = cpu.getRegistries("B");
	combinedRegistries* addrRegistries = cpu.getCombinedRegistries("HL");
	LD_pRRqcR(cpu, *addrRegistries, *srcRegistry);

	return 8;
}

u8 Instruction8BitLoad::LD_pHLqcC(CPU& cpu)
{
	u8* srcRegistry = cpu.getRegistries("C");
	combinedRegistries* addrRegistries = cpu.getCombinedRegistries("HL");
	LD_pRRqcR(cpu, *addrRegistries, *srcRegistry);

	return 8;
}

u8 Instruction8BitLoad::LD_pHLqcD(CPU& cpu)
{
	u8* srcRegistry = cpu.getRegistries("D");
	combinedRegistries* addrRegistries = cpu.getCombinedRegistries("HL");
	LD_pRRqcR(cpu, *addrRegistries, *srcRegistry);

	return 8;
}

u8 Instruction8BitLoad::LD_pHLqcE(CPU& cpu)
{
	u8* srcRegistry = cpu.getRegistries("E");
	combinedRegistries* addrRegistries = cpu.getCombinedRegistries("HL");
	LD_pRRqcR(cpu, *addrRegistries, *srcRegistry);

	return 8;
}

u8 Instruction8BitLoad::LD_pHLqcH(CPU& cpu)
{
	u8* srcRegistry = cpu.getRegistries("H");
	combinedRegistries* addrRegistries = cpu.getCombinedRegistries("HL");
	LD_pRRqcR(cpu, *addrRegistries, *srcRegistry);

	return 8;
}

u8 Instruction8BitLoad::LD_pHLqcL(CPU& cpu)
{
	u8* srcRegistry = cpu.getRegistries("L");
	combinedRegistries* addrRegistries = cpu.getCombinedRegistries("HL");
	LD_pRRqcR(cpu, *addrRegistries, *srcRegistry);

	return 8;
}

u8 Instruction8BitLoad::LD_pHLqcA(CPU& cpu)
{
	u8* srcRegistry = cpu.getRegistries("A");
	combinedRegistries* addrRegistries = cpu.getCombinedRegistries("HL");
	LD_pRRqcR(cpu, *addrRegistries, *srcRegistry);

	return 8;
}

u8 Instruction8BitLoad::LD_AcB(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("B");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_AcC(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("C");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_AcD(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("D");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_AcE(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("E");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_AcH(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("H");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_AcL(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("L");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LD_AcpHLq(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	combinedRegistries* addrRegistries = cpu.getCombinedRegistries("HL");
	LD_pRRqcR(cpu, *addrRegistries, *dstRegistry);

	return 8;
}

u8 Instruction8BitLoad::LD_AcA(CPU& cpu)
{
	u8* dstRegistry = cpu.getRegistries("A");
	u8* srcRegistry = cpu.getRegistries("A");
	*dstRegistry = *srcRegistry;

	return 4;
}

u8 Instruction8BitLoad::LDH_pa8qcA(CPU& cpu)
{
	//TODO Verifier cette instruction
	//u16* PC = cpu.getPC();
	//*PC += 1;
	//u8* ARegistry = cpu.getRegistries("A");
	//cpu.writeMemory(0xFF00 + *PC, *ARegistry);

	u8 addressOffset = readNextOpcode(cpu);
	auto ARegistry = cpu.getRegistries("A");
	cpu.writeMemory(0xFF00 + addressOffset, *ARegistry);

	return 12;
}

u8 Instruction8BitLoad::LD_pCqcA(CPU& cpu)
{
	//TODO Verifier cette instruction
	u8* ARegistry = cpu.getRegistries("A");
	u8* CRegistry = cpu.getRegistries("C");
	cpu.writeMemory(0xFF00 + *CRegistry, *ARegistry);

	return 8;
}

u8 Instruction8BitLoad::LD_pa16qcA(CPU& cpu)
{
	//u16* PC = cpu.getPC();
	//*PC += 1;
	//u8* ARegistry = cpu.getRegistries("A");
	//cpu.writeMemory(*PC, *ARegistry);

	u16* PC = cpu.getPC();
	u16 address = readNextTwoOpcodes(cpu);

	auto ARegistry = cpu.getRegistries("A");
	cpu.writeMemory(address, *ARegistry);


	return 16;
}

u8 Instruction8BitLoad::LDH_Acpa8q(CPU& cpu)
{
	u8 addressOffset = readNextOpcode(cpu);
	
	u8 data = cpu.readMemory(0xFF00 + addressOffset);
	cpu.setRegistries("A", data);

	return 12;
}

u8 Instruction8BitLoad::LD_AcpCq(CPU& cpu)
{
	//TODO Verifier cette instruction
	u8* ARegistry = cpu.getRegistries("A");
	u8* CRegistry = cpu.getRegistries("C");

	*ARegistry = cpu.readMemory(0xFF00 + *CRegistry);

	return 8;
}

u8 Instruction8BitLoad::LD_Acpa16q(CPU& cpu)
{
	u16 address = readNextTwoOpcodes(cpu);
	u8 data = cpu.readMemory(address);
	cpu.setRegistries("A", data);

	return 16;
}


/// ///////////////////////

void Instruction8BitLoad::LD_Rcd8(CPU& cpu, u8& registry)
{
	/*u16* PC = cpu.getPC();
	*PC += 1;
	u8 data = cpu.readMemory(*PC);*/

	u8 data = readNextOpcode(cpu);
	registry = data;
}

void Instruction8BitLoad::LD_pRRqcR(CPU& cpu, combinedRegistries& addrRegistries, u8& srcRegistry)
{
	cpu.writeMemory(addrRegistries, srcRegistry);
}

void Instruction8BitLoad::LD_RcpRRq(CPU& cpu, combinedRegistries& addrRegistries, u8& dstRegistry)
{
	u8 data = cpu.readMemory(addrRegistries);
	dstRegistry = data;
}

void Instruction8BitLoad::LD_pRRqcd8(CPU& cpu, combinedRegistries& registries)
{
	u16* PC = cpu.getPC();
	*PC += 1;
	u8 data = cpu.readMemory(*PC);
	cpu.writeMemory(registries, data);
}

