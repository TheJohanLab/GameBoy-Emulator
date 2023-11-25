#include "Instruction8BitLoad.h"

Instruction8BitLoad::Instruction8BitLoad(std::string const& name, void(* pInstruction)(CPU& cpu), u8 clockCycles)
{
}

void Instruction8BitLoad::LD_pBCqcA(CPU& cpu)
{
}

void Instruction8BitLoad::LD_Bcd8(CPU& cpu)
{
}

void Instruction8BitLoad::LD_AcpBCq(CPU& cpu)
{
}

void Instruction8BitLoad::LD_Ccd8(CPU& cpu)
{
}

void Instruction8BitLoad::LD_pDEqcA(CPU& cpu)
{
}

void Instruction8BitLoad::LD_Dcd8(CPU& cpu)
{
}

void Instruction8BitLoad::LD_AcpDEq(CPU& cpu)
{
}

void Instruction8BitLoad::LD_Ecd8(CPU& cpu)
{
}

void Instruction8BitLoad::LD_pHLaqcA(CPU& cpu)
{
}

void Instruction8BitLoad::LD_Hcd8(CPU& cpu)
{
}

void Instruction8BitLoad::LD_AcpHLaq(CPU& cpu)
{
}

void Instruction8BitLoad::LD_Lcd8(CPU& cpu)
{
}

void Instruction8BitLoad::LD_pHLmqcA(CPU& cpu)
{
}

void Instruction8BitLoad::LD_pHLqcd8(CPU& cpu)
{
}

void Instruction8BitLoad::LD_AcpHLmq(CPU& cpu)
{
}

void Instruction8BitLoad::LD_Acd8(CPU& cpu)
{
}

void Instruction8BitLoad::LD_BcB(CPU& cpu)
{

}

void Instruction8BitLoad::LD_BcC(CPU& cpu)
{
	cpu.setRegistries("C", 0x03);
	u8* registryC = cpu.getRegistries("C");
	cpu.setRegistries("B", *registryC);

}

void Instruction8BitLoad::LD_BcD(CPU& cpu)
{
}

void Instruction8BitLoad::LD_BcE(CPU& cpu)
{
}

void Instruction8BitLoad::LD_BcH(CPU& cpu)
{
}

void Instruction8BitLoad::LD_BcL(CPU& cpu)
{
}

void Instruction8BitLoad::LD_BcpHLq(CPU& cpu)
{
}

void Instruction8BitLoad::LD_BcA(CPU& cpu)
{
}

void Instruction8BitLoad::LD_CcB(CPU& cpu)
{
}

void Instruction8BitLoad::LD_CcC(CPU& cpu)
{
}

void Instruction8BitLoad::LD_CcD(CPU& cpu)
{
}

void Instruction8BitLoad::LD_CcE(CPU& cpu)
{
}

void Instruction8BitLoad::LD_CcH(CPU& cpu)
{
}

void Instruction8BitLoad::LD_CcL(CPU& cpu)
{
}

void Instruction8BitLoad::LD_CcpHLq(CPU& cpu)
{
}

void Instruction8BitLoad::LD_CcA(CPU& cpu)
{
}

void Instruction8BitLoad::LD_DcB(CPU& cpu)
{
}

void Instruction8BitLoad::LD_DcC(CPU& cpu)
{
}

void Instruction8BitLoad::LD_DcD(CPU& cpu)
{
}

void Instruction8BitLoad::LD_DcE(CPU& cpu)
{
}

void Instruction8BitLoad::LD_DcH(CPU& cpu)
{
}

void Instruction8BitLoad::LD_DcL(CPU& cpu)
{
}

void Instruction8BitLoad::LD_DcpHLq(CPU& cpu)
{
}

void Instruction8BitLoad::LD_DcA(CPU& cpu)
{
}

void Instruction8BitLoad::LD_EcB(CPU& cpu)
{
}

void Instruction8BitLoad::LD_EcC(CPU& cpu)
{
}

void Instruction8BitLoad::LD_EcD(CPU& cpu)
{
}

void Instruction8BitLoad::LD_EcE(CPU& cpu)
{
}

void Instruction8BitLoad::LD_EcH(CPU& cpu)
{
}

void Instruction8BitLoad::LD_EcL(CPU& cpu)
{
}

void Instruction8BitLoad::LD_EcpHLq(CPU& cpu)
{
}

void Instruction8BitLoad::LD_EcA(CPU& cpu)
{
}

void Instruction8BitLoad::LD_HcB(CPU& cpu)
{
}

void Instruction8BitLoad::LD_HcC(CPU& cpu)
{
}

void Instruction8BitLoad::LD_HcD(CPU& cpu)
{
}

void Instruction8BitLoad::LD_HcE(CPU& cpu)
{
}

void Instruction8BitLoad::LD_HcH(CPU& cpu)
{
}

void Instruction8BitLoad::LD_HcL(CPU& cpu)
{
}

void Instruction8BitLoad::LD_HcpHLq(CPU& cpu)
{
}

void Instruction8BitLoad::LD_HcA(CPU& cpu)
{
}

void Instruction8BitLoad::LD_LcB(CPU& cpu)
{
}

void Instruction8BitLoad::LD_LcC(CPU& cpu)
{
}

void Instruction8BitLoad::LD_LcD(CPU& cpu)
{
}

void Instruction8BitLoad::LD_LcE(CPU& cpu)
{
}

void Instruction8BitLoad::LD_LcH(CPU& cpu)
{
}

void Instruction8BitLoad::LD_LcL(CPU& cpu)
{
}

void Instruction8BitLoad::LD_LcpHLq(CPU& cpu)
{
}

void Instruction8BitLoad::LD_LcA(CPU& cpu)
{
}

void Instruction8BitLoad::LD_pHLqcB(CPU& cpu)
{
}

void Instruction8BitLoad::LD_pHLqcC(CPU& cpu)
{
}

void Instruction8BitLoad::LD_pHLqcD(CPU& cpu)
{
}

void Instruction8BitLoad::LD_pHLqcE(CPU& cpu)
{
}

void Instruction8BitLoad::LD_pHLqcH(CPU& cpu)
{
}

void Instruction8BitLoad::LD_pHLqcL(CPU& cpu)
{
}

void Instruction8BitLoad::LD_pHLqcA(CPU& cpu)
{
}

void Instruction8BitLoad::LD_AcB(CPU& cpu)
{
}

void Instruction8BitLoad::LD_AcC(CPU& cpu)
{
}

void Instruction8BitLoad::LD_AcD(CPU& cpu)
{
}

void Instruction8BitLoad::LD_AcE(CPU& cpu)
{
}

void Instruction8BitLoad::LD_AcH(CPU& cpu)
{
}

void Instruction8BitLoad::LD_AcL(CPU& cpu)
{
}

void Instruction8BitLoad::LD_AcpHLq(CPU& cpu)
{
}

void Instruction8BitLoad::LD_AcA(CPU& cpu)
{
}

void Instruction8BitLoad::LDH_pa8qcA(CPU& cpu)
{
}

void Instruction8BitLoad::LD_pCqcA(CPU& cpu)
{
}

void Instruction8BitLoad::LDH_pa16qcA(CPU& cpu)
{
}

void Instruction8BitLoad::LDH_Acpa8q(CPU& cpu)
{
}

void Instruction8BitLoad::LD_AcpCq(CPU& cpu)
{
}

void Instruction8BitLoad::LDH_Acpa16q(CPU& cpu)
{
}
