#include "CPU.h"

CPU::CPU()
{

}

CPU::CPU(Bus const& bus) : mBus(bus)
{
	initInstructionSet();
}

void CPU::initInstructionSet() 
{
	InstructionFactory instructionFactory = InstructionFactory();

	mInstructionSet =
	{
		//0x0
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"NOP", &InstructionCPUControl::nop, 4),				//0x00

		
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (BC),A", &Instruction8BitLoad::LD_pBCqcA, 8),		//0x02
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,d8", &Instruction8BitLoad::LD_Bcd8, 8),			//0x06
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,(BC)", &Instruction8BitLoad::LD_AcpBCq, 8),		//0x0A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,d8", &Instruction8BitLoad::LD_Ccd8, 8),			//0x0F
		//0x1
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (DE),A", &Instruction8BitLoad::LD_pDEqcA, 8),		//0x12
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,d8", &Instruction8BitLoad::LD_Dcd8, 8),			//0x16
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,(DE)", &Instruction8BitLoad::LD_AcpDEq, 8),		//0x1A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,d8", &Instruction8BitLoad::LD_Ecd8, 8),			//0x1E
		//0x2
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL+),A", &Instruction8BitLoad::LD_pHLaqcA, 8),	//0x22
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,d8", &Instruction8BitLoad::LD_Hcd8, 8),		//0x26
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,(HL+)", &Instruction8BitLoad::LD_AcpHLaq, 8),	//0x2A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,d8", &Instruction8BitLoad::LD_Lcd8, 8),		//0x2E
		//0x3
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL-),A", &Instruction8BitLoad::LD_pHLmqcA, 8),	//0x32
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),d", &Instruction8BitLoad::LD_pHLqcd8, 12),	//0x36
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,(HL-)", &Instruction8BitLoad::LD_AcpHLmq, 8),	//0x3A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,d8", &Instruction8BitLoad::LD_Acd8, 8),		//0x3E
		//0x4
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,B", &Instruction8BitLoad::LD_BcB, 4),			//0x40
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,C", &Instruction8BitLoad::LD_BcC, 4),			//0x41
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,D", &Instruction8BitLoad::LD_BcD, 4),			//0x42
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,E", &Instruction8BitLoad::LD_BcE, 4),			//0x43
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,H", &Instruction8BitLoad::LD_BcH, 4),			//0x44
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,L", &Instruction8BitLoad::LD_BcL, 4),			//0x45
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,(HL)", &Instruction8BitLoad::LD_BcpHLq, 8),	//0x46
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,A", &Instruction8BitLoad::LD_BcA, 4),			//0x47
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,B", &Instruction8BitLoad::LD_CcB, 4),			//0x48
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,C", &Instruction8BitLoad::LD_CcC, 4),			//0x49
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,D", &Instruction8BitLoad::LD_CcD, 4),			//0x4A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,E", &Instruction8BitLoad::LD_CcE, 4),			//0x4B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,H", &Instruction8BitLoad::LD_CcH, 4),			//0x4C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,L", &Instruction8BitLoad::LD_CcL, 4),			//0x4D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,(HL)", &Instruction8BitLoad::LD_CcpHLq, 8),	//0x4E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,A", &Instruction8BitLoad::LD_CcA, 4),			//0x4F
		//0x5
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,B",	&Instruction8BitLoad::LD_DcB	, 4),		//0x50
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,C",	&Instruction8BitLoad::LD_DcC	, 4),		//0x51
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,D",	&Instruction8BitLoad::LD_DcD	, 4),		//0x52
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,E",	&Instruction8BitLoad::LD_DcE	, 4),		//0x53
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,H",	&Instruction8BitLoad::LD_DcH	, 4),		//0x54
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,L",	&Instruction8BitLoad::LD_DcL	, 4),		//0x55
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,(HL)", &Instruction8BitLoad::LD_DcpHLq	, 8),		//0x56
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,A",	&Instruction8BitLoad::LD_DcA	, 4),		//0x57
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,B",	&Instruction8BitLoad::LD_EcB	, 4),		//0x58
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,C",	&Instruction8BitLoad::LD_EcC	, 4),		//0x59
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,D",	&Instruction8BitLoad::LD_EcD	, 4),		//0x5A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,E",	&Instruction8BitLoad::LD_EcE	, 4),		//0x5B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,H",	&Instruction8BitLoad::LD_EcH	, 4),		//0x5C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,L",	&Instruction8BitLoad::LD_EcL	, 4),		//0x5D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,(HL)", &Instruction8BitLoad::LD_EcpHLq	, 8),		//0x5E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,A",	&Instruction8BitLoad::LD_EcA	, 4),		//0x5F
		//0x6
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,B",	&Instruction8BitLoad::LD_HcB	, 4),		//0x60
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,C",	&Instruction8BitLoad::LD_HcC	, 4),		//0x61
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,D",	&Instruction8BitLoad::LD_HcD	, 4),		//0x62
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,E",	&Instruction8BitLoad::LD_HcE	, 4),		//0x63
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,H",	&Instruction8BitLoad::LD_HcH	, 4),		//0x64
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,L",	&Instruction8BitLoad::LD_HcL	, 4),		//0x65
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,(HL)", &Instruction8BitLoad::LD_HcpHLq	, 8),	//0x66
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,A",	&Instruction8BitLoad::LD_HcA	, 4),		//0x67
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,B",	&Instruction8BitLoad::LD_LcB	, 4),		//0x68
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,C",	&Instruction8BitLoad::LD_LcC	, 4),		//0x69
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,D",	&Instruction8BitLoad::LD_LcD	, 4),		//0x6A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,E",	&Instruction8BitLoad::LD_LcE	, 4),		//0x6B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,H",	&Instruction8BitLoad::LD_LcH	, 4),		//0x6C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,L",	&Instruction8BitLoad::LD_LcL	, 4),		//0x6D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,(HL)", &Instruction8BitLoad::LD_LcpHLq	, 8),		//0x6E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,A",	&Instruction8BitLoad::LD_LcA	, 4),		//0x6F
		//0x7
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),B",	&Instruction8BitLoad::LD_pHLqcB	, 4),		//0x70
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),C",	&Instruction8BitLoad::LD_pHLqcC	, 4),		//0x71
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),D",	&Instruction8BitLoad::LD_pHLqcD	, 4),		//0x72
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),E",	&Instruction8BitLoad::LD_pHLqcE	, 4),		//0x73
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),H",	&Instruction8BitLoad::LD_pHLqcH	, 4),		//0x74
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),L",	&Instruction8BitLoad::LD_pHLqcL	, 4),		//0x75
																																					//0x76
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),A",	&Instruction8BitLoad::LD_pHLqcA	, 4),		//0x77
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,B",	&Instruction8BitLoad::LD_AcB	, 4),		//0x78
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,C",	&Instruction8BitLoad::LD_AcC	, 4),		//0x79
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,D",	&Instruction8BitLoad::LD_AcD	, 4),		//0x7A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,E",	&Instruction8BitLoad::LD_AcE	, 4),		//0x7B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,H",	&Instruction8BitLoad::LD_AcH	, 4),		//0x7C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,L",	&Instruction8BitLoad::LD_AcL	, 4),		//0x7D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,(HL)", &Instruction8BitLoad::LD_AcpHLq	, 8),		//0x7E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,A",	&Instruction8BitLoad::LD_AcA	, 4),		//0x7F
		//0xC
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,B", &Instruction1BitOperation::bit_0cB, 1),	//CB40
		//0xE
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LDH (a8),A",	&Instruction8BitLoad::LDH_pa8qcA	, 4),		//0xE0
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (C),A",		&Instruction8BitLoad::LD_pCqcA		, 4),		//0xE2
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LDH (a16),A",	&Instruction8BitLoad::LDH_pa16qcA	, 4),		//0xEA
		//0xF
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LDH A,(a8)",	&Instruction8BitLoad::LDH_Acpa8q	, 4),		//0xF0
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,(C)",		&Instruction8BitLoad::LD_AcpCq		, 4),		//0xF2
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LDH A,(a16)",	&Instruction8BitLoad::LDH_Acpa16q	, 4),		//0xFA
		//0xCB0
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RLC B",	&InstructionRotateShift::RLC_B,		8),		//0xCB00
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RLC C",	&InstructionRotateShift::RLC_C,		8),		//0xCB01
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RLC D",	&InstructionRotateShift::RLC_D,		8),		//0xCB02
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RLC E",	&InstructionRotateShift::RLC_E,		8),		//0xCB03
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RLC H",	&InstructionRotateShift::RLC_H,		8),		//0xCB04
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RLC L",	&InstructionRotateShift::RLC_L,		8),		//0xCB05
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RLC (HL)", &InstructionRotateShift::RLC_pHLq,  16),	//0xCB06
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RLC A",	&InstructionRotateShift::RLC_A,		8),		//0xCB07
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RRC B",	&InstructionRotateShift::RRC_B,		8),		//0xCB08
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RRC C",	&InstructionRotateShift::RRC_C,		8),		//0xCB09
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RRC D",	&InstructionRotateShift::RRC_D,		8),		//0xCB0A
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RRC E",	&InstructionRotateShift::RRC_E,		8),		//0xCB0B
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RRC H",	&InstructionRotateShift::RRC_H,		8),		//0xCB0C
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RRC L",	&InstructionRotateShift::RRC_L,		8),		//0xCB0D
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RRC (HL)",	&InstructionRotateShift::RRC_pHLq,  16),	//0xCB0E
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RRC A",	&InstructionRotateShift::RRC_A,		8),		//0xCB0F
		//0xCB1
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RL B",		&InstructionRotateShift::RL_B,		8),		//0xCB10
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RL C",		&InstructionRotateShift::RL_C,		8),		//0xCB11
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RL D",		&InstructionRotateShift::RL_D,		8),		//0xCB12
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RL E",		&InstructionRotateShift::RL_E,		8),		//0xCB13
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RL H",		&InstructionRotateShift::RL_H,		8),		//0xCB14
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RL L",		&InstructionRotateShift::RL_L,		8),		//0xCB15
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RL (HL)",	&InstructionRotateShift::RL_pHLq,	16),	//0xCB16
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RL A",		&InstructionRotateShift::RL_A,		8),		//0xCB17
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RR B",		&InstructionRotateShift::RR_B,		8),		//0xCB18
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RR C",		&InstructionRotateShift::RR_C,		8),		//0xCB19
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RR D",		&InstructionRotateShift::RR_D,		8),		//0xCB1A
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RR E",		&InstructionRotateShift::RR_E,		8),		//0xCB1B
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RR H",		&InstructionRotateShift::RR_H,		8),		//0xCB1C
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RR L",		&InstructionRotateShift::RR_L,		8),		//0xCB1D
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RR (HL)",	&InstructionRotateShift::RR_pHLq,	16),	//0xCB1E
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RR A",		&InstructionRotateShift::RR_A,		8),		//0xCB1F
		//0xCB2
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SLA B",	&InstructionRotateShift::SLA_B,		8),		//0xCB20
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SLA C",	&InstructionRotateShift::SLA_C,		8),		//0xCB21
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SLA D",	&InstructionRotateShift::SLA_D,		8),		//0xCB22
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SLA E",	&InstructionRotateShift::SLA_E,		8),		//0xCB23
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SLA H",	&InstructionRotateShift::SLA_H,		8),		//0xCB24
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SLA L",	&InstructionRotateShift::SLA_L,		8),		//0xCB25
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SLA (HL)",	&InstructionRotateShift::SLA_pHLq,	16),	//0xCB26
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SLA A",	&InstructionRotateShift::SLA_A,		8),		//0xCB27
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRA B",	&InstructionRotateShift::SRA_B,		8),		//0xCB28
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRA C",	&InstructionRotateShift::SRA_C,		8),		//0xCB29
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRA D",	&InstructionRotateShift::SRA_D,		8),		//0xCB2A
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRA E",	&InstructionRotateShift::SRA_E,		8),		//0xCB2B
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRA H",	&InstructionRotateShift::SRA_H,		8),		//0xCB2C
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRA L",	&InstructionRotateShift::SRA_L,		8),		//0xCB2D
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRA (HL)",	&InstructionRotateShift::SRA_pHLq,	16),	//0xCB2E
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRA A",	&InstructionRotateShift::SRA_A,		8),		//0xCB2F
	};
}

u8 CPU::executeOpcode(u16 opcode) const
{
	CPU cpu;

	if (opcode == 0xCB) 
	{
		return executeOpcodeCB(cpu);
	}

	(mInstructionSet[opcode]->getFunctionPointer())(cpu);
	std::cout << mInstructionSet[opcode]->getName() << "\n";
	
	return mInstructionSet[opcode]->getClockCycle();
}

u8 CPU::executeOpcodeCB(CPU &cpu) const
{
	// read opcode
	u16 opcodeCB = 0x00;
	(mInstructionSet[0x100 + opcodeCB]->getFunctionPointer())(cpu);
	std::cout << mInstructionSet[0x100 + opcodeCB]->getName() << "\n";

	return (4 + mInstructionSet[0x100 + opcodeCB]->getClockCycle());
}


Registries CPU::getRegistries(std::string registry) const
{
	std::map<std::string, u8 > registriesMap = {
		
	}
}