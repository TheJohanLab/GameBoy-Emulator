#include "CPU.h"

CPU::CPU()
{

}

CPU::CPU(Bus* bus) : mBus(bus)
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
		//0xCB3
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SWAP B", &InstructionRotateShift::SWAP_B, 8),			//0xCB30
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SWAP C", &InstructionRotateShift::SWAP_C, 8),			//0xCB31
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SWAP D", &InstructionRotateShift::SWAP_D, 8),			//0xCB32
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SWAP E", &InstructionRotateShift::SWAP_E, 8),			//0xCB33
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SWAP H", &InstructionRotateShift::SWAP_H, 8),			//0xCB34
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SWAP L", &InstructionRotateShift::SWAP_L, 8),			//0xCB35
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SWAP (HL)", &InstructionRotateShift::SWAP_pHLq, 16),	//0xCB36
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SWAP A", &InstructionRotateShift::SWAP_A, 8),			//0xCB37
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRL B", &InstructionRotateShift::SRL_B, 8),			//0xCB38
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRL C", &InstructionRotateShift::SRL_C, 8),			//0xCB39
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRL D", &InstructionRotateShift::SRL_D, 8),			//0xCB3A
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRL E", &InstructionRotateShift::SRL_E, 8),			//0xCB3B
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRL H", &InstructionRotateShift::SRL_H, 8),			//0xCB3C
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRL L", &InstructionRotateShift::SRL_L, 8),			//0xCB3D
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRL (HL)", &InstructionRotateShift::SRL_pHLq, 16),		//0xCB3E
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRL A", &InstructionRotateShift::SRL_A, 8),			//0xCB3F
		//0xCB4
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,B", &Instruction1BitOperation::BIT_0cB, 8),		//0xCB40
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,C", &Instruction1BitOperation::BIT_0cC, 8),		//0xCB41
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,D", &Instruction1BitOperation::BIT_0cD, 8),		//0xCB42
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,E", &Instruction1BitOperation::BIT_0cE, 8),		//0xCB43
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,H", &Instruction1BitOperation::BIT_0cH, 8),		//0xCB44
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,L", &Instruction1BitOperation::BIT_0cL, 8),		//0xCB45
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,(HL)", &Instruction1BitOperation::BIT_0cpHLq, 16),	//0xCB46
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,A", &Instruction1BitOperation::BIT_0cA, 8),		//0xCB47
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 1,B", &Instruction1BitOperation::BIT_1cB, 8),		//0xCB48
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 1,C", &Instruction1BitOperation::BIT_1cC, 8),		//0xCB49
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 1,D", &Instruction1BitOperation::BIT_1cD, 8),		//0xCB4A
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 1,E", &Instruction1BitOperation::BIT_1cE, 8),		//0xCB4B
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 1,H", &Instruction1BitOperation::BIT_1cH, 8),		//0xCB4C
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 1,L", &Instruction1BitOperation::BIT_1cL, 8),		//0xCB4D
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 1,(HL)", &Instruction1BitOperation::BIT_1cpHLq, 16),	//0xCB4E
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 1,A", &Instruction1BitOperation::BIT_1cA, 8),		//0xCB4F
		//0xCB5
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 2,B", &Instruction1BitOperation::BIT_2cB, 8),		//0xCB50
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 2,C", &Instruction1BitOperation::BIT_2cC, 8),		//0xCB51
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 2,D", &Instruction1BitOperation::BIT_2cD, 8),		//0xCB52
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 2,E", &Instruction1BitOperation::BIT_2cE, 8),		//0xCB53
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 2,H", &Instruction1BitOperation::BIT_2cH, 8),		//0xCB54
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 2,L", &Instruction1BitOperation::BIT_2cL, 8),		//0xCB55
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 2,(HL)", &Instruction1BitOperation::BIT_2cpHLq, 16),	//0xCB56
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 2,A", &Instruction1BitOperation::BIT_2cA, 8),		//0xCB57
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 3,B", &Instruction1BitOperation::BIT_3cB, 8),		//0xCB58
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 3,C", &Instruction1BitOperation::BIT_3cC, 8),		//0xCB59
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 3,D", &Instruction1BitOperation::BIT_3cD, 8),		//0xCB5A
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 3,E", &Instruction1BitOperation::BIT_3cE, 8),		//0xCB5B
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 3,H", &Instruction1BitOperation::BIT_3cH, 8),		//0xCB5C
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 3,L", &Instruction1BitOperation::BIT_3cL, 8),		//0xCB5D
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 3,(HL)", &Instruction1BitOperation::BIT_3cpHLq, 16),	//0xCB5E
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 3,A", &Instruction1BitOperation::BIT_3cA, 8),		//0xCB5F
		//0xCB6
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 4,B", &Instruction1BitOperation::BIT_4cB, 8),		//0xCB60
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 4,C", &Instruction1BitOperation::BIT_4cC, 8),		//0xCB61
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 4,D", &Instruction1BitOperation::BIT_4cD, 8),		//0xCB62
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 4,E", &Instruction1BitOperation::BIT_4cE, 8),		//0xCB63
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 4,H", &Instruction1BitOperation::BIT_4cH, 8),		//0xCB64
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 4,L", &Instruction1BitOperation::BIT_4cL, 8),		//0xCB65
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 4,(HL)", &Instruction1BitOperation::BIT_4cpHLq, 16),	//0xCB66
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 4,A", &Instruction1BitOperation::BIT_4cA, 8),		//0xCB67
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 5,B", &Instruction1BitOperation::BIT_5cB, 8),		//0xCB68
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 5,C", &Instruction1BitOperation::BIT_5cC, 8),		//0xCB69
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 5,D", &Instruction1BitOperation::BIT_5cD, 8),		//0xCB6A
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 5,E", &Instruction1BitOperation::BIT_5cE, 8),		//0xCB6B
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 5,H", &Instruction1BitOperation::BIT_5cH, 8),		//0xCB6C
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 5,L", &Instruction1BitOperation::BIT_5cL, 8),		//0xCB6D
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 5,(HL)", &Instruction1BitOperation::BIT_5cpHLq, 16),	//0xCB6E
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 5,A", &Instruction1BitOperation::BIT_5cA, 8),		//0xCB6F
		//0xCB7
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 6,B", &Instruction1BitOperation::BIT_6cB, 8),		//0xCB70
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 6,C", &Instruction1BitOperation::BIT_6cC, 8),		//0xCB71
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 6,D", &Instruction1BitOperation::BIT_6cD, 8),		//0xCB72
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 6,E", &Instruction1BitOperation::BIT_6cE, 8),		//0xCB73
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 6,H", &Instruction1BitOperation::BIT_6cH, 8),		//0xCB74
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 6,L", &Instruction1BitOperation::BIT_6cL, 8),		//0xCB75
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 6,(HL)", &Instruction1BitOperation::BIT_6cpHLq, 16),	//0xCB76
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 6,A", &Instruction1BitOperation::BIT_6cA, 8),		//0xCB77
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 7,B", &Instruction1BitOperation::BIT_7cB, 8),		//0xCB78
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 7,C", &Instruction1BitOperation::BIT_7cC, 8),		//0xCB79
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 7,D", &Instruction1BitOperation::BIT_7cD, 8),		//0xCB7A
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 7,E", &Instruction1BitOperation::BIT_7cE, 8),		//0xCB7B
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 7,H", &Instruction1BitOperation::BIT_7cH, 8),		//0xCB7C
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 7,L", &Instruction1BitOperation::BIT_7cL, 8),		//0xCB7D
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 7,(HL)", &Instruction1BitOperation::BIT_7cpHLq, 16),	//0xCB7E
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 7,A", &Instruction1BitOperation::BIT_7cA, 8),		//0xCB7F
		//0xCB8
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 0,B", &Instruction1BitOperation::RES_0cB, 8),		//0xCB80
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 0,C", &Instruction1BitOperation::RES_0cC, 8),		//0xCB81
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 0,D", &Instruction1BitOperation::RES_0cD, 8),		//0xCB82
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 0,E", &Instruction1BitOperation::RES_0cE, 8),		//0xCB83
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 0,H", &Instruction1BitOperation::RES_0cH, 8),		//0xCB84
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 0,L", &Instruction1BitOperation::RES_0cL, 8),		//0xCB85
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 0,(HL)", &Instruction1BitOperation::RES_0cpHLq, 16),	//0xCB86
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 0,A", &Instruction1BitOperation::RES_0cA, 8),		//0xCB87
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 1,B", &Instruction1BitOperation::RES_1cB, 8),		//0xCB88
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 1,C", &Instruction1BitOperation::RES_1cC, 8),		//0xCB89
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 1,D", &Instruction1BitOperation::RES_1cD, 8),		//0xCB8A
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 1,E", &Instruction1BitOperation::RES_1cE, 8),		//0xCB8B
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 1,H", &Instruction1BitOperation::RES_1cH, 8),		//0xCB8C
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 1,L", &Instruction1BitOperation::RES_1cL, 8),		//0xCB8D
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 1,(HL)", &Instruction1BitOperation::RES_1cpHLq, 16),	//0xCB8E
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 1,A", &Instruction1BitOperation::RES_1cA, 8),		//0xCB8F
		//0xCB9
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 2,B", &Instruction1BitOperation::RES_2cB, 8),		//0xCB90
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 2,C", &Instruction1BitOperation::RES_2cC, 8),		//0xCB91
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 2,D", &Instruction1BitOperation::RES_2cD, 8),		//0xCB92
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 2,E", &Instruction1BitOperation::RES_2cE, 8),		//0xCB93
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 2,H", &Instruction1BitOperation::RES_2cH, 8),		//0xCB94
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 2,L", &Instruction1BitOperation::RES_2cL, 8),		//0xCB95
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 2,(HL)", &Instruction1BitOperation::RES_2cpHLq, 16),	//0xCB96
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 2,A", &Instruction1BitOperation::RES_2cA, 8),		//0xCB97
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 3,B", &Instruction1BitOperation::RES_3cB, 8),		//0xCB98
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 3,C", &Instruction1BitOperation::RES_3cC, 8),		//0xCB99
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 3,D", &Instruction1BitOperation::RES_3cD, 8),		//0xCB9A
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 3,E", &Instruction1BitOperation::RES_3cE, 8),		//0xCB9B
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 3,H", &Instruction1BitOperation::RES_3cH, 8),		//0xCB9C
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 3,L", &Instruction1BitOperation::RES_3cL, 8),		//0xCB9D
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 3,(HL)", &Instruction1BitOperation::RES_3cpHLq, 16),	//0xCB9E
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 3,A", &Instruction1BitOperation::RES_3cA, 8),		//0xCB9F
		//0xCBA
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 4,B", &Instruction1BitOperation::RES_4cB, 8),		//0xCBA0
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 4,C", &Instruction1BitOperation::RES_4cC, 8),		//0xCBA1
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 4,D", &Instruction1BitOperation::RES_4cD, 8),		//0xCBA2
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 4,E", &Instruction1BitOperation::RES_4cE, 8),		//0xCBA3
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 4,H", &Instruction1BitOperation::RES_4cH, 8),		//0xCBA4
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 4,L", &Instruction1BitOperation::RES_4cL, 8),		//0xCBA5
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 4,(HL)", &Instruction1BitOperation::RES_4cpHLq, 16),	//0xCBA6
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 4,A", &Instruction1BitOperation::RES_4cA, 8),		//0xCBA7
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 5,B", &Instruction1BitOperation::RES_5cB, 8),		//0xCBA8
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 5,C", &Instruction1BitOperation::RES_5cC, 8),		//0xCBA9
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 5,D", &Instruction1BitOperation::RES_5cD, 8),		//0xCBAA
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 5,E", &Instruction1BitOperation::RES_5cE, 8),		//0xCBAB
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 5,H", &Instruction1BitOperation::RES_5cH, 8),		//0xCBAC
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 5,L", &Instruction1BitOperation::RES_5cL, 8),		//0xCBAD
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 5,(HL)", &Instruction1BitOperation::RES_5cpHLq, 16),	//0xCBAE
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 5,A", &Instruction1BitOperation::RES_5cA, 8),		//0xCBAF
		//0xCBB
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 6,B", &Instruction1BitOperation::RES_6cB, 8),		//0xCBB0
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 6,C", &Instruction1BitOperation::RES_6cC, 8),		//0xCBB1
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 6,D", &Instruction1BitOperation::RES_6cD, 8),		//0xCBB2
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 6,E", &Instruction1BitOperation::RES_6cE, 8),		//0xCBB3
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 6,H", &Instruction1BitOperation::RES_6cH, 8),		//0xCBB4
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 6,L", &Instruction1BitOperation::RES_6cL, 8),		//0xCBB5
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 6,(HL)", &Instruction1BitOperation::RES_6cpHLq, 16),	//0xCBB6
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 6,A", &Instruction1BitOperation::RES_6cA, 8),		//0xCBB7
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 7,B", &Instruction1BitOperation::RES_7cB, 8),		//0xCBB8
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 7,C", &Instruction1BitOperation::RES_7cC, 8),		//0xCBB9
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 7,D", &Instruction1BitOperation::RES_7cD, 8),		//0xCBBA
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 7,E", &Instruction1BitOperation::RES_7cE, 8),		//0xCBBB
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 7,H", &Instruction1BitOperation::RES_7cH, 8),		//0xCBBC
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 7,L", &Instruction1BitOperation::RES_7cL, 8),		//0xCBBD
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 7,(HL)", &Instruction1BitOperation::RES_7cpHLq, 16),	//0xCBBE
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 7,A", &Instruction1BitOperation::RES_7cA, 8),		//0xCBBF
		//0xCBC
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 0,B", &Instruction1BitOperation::SET_0cB, 8),		//0xCBC0
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 0,C", &Instruction1BitOperation::SET_0cC, 8),		//0xCBC1
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 0,D", &Instruction1BitOperation::SET_0cD, 8),		//0xCBC2
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 0,E", &Instruction1BitOperation::SET_0cE, 8),		//0xCBC3
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 0,H", &Instruction1BitOperation::SET_0cH, 8),		//0xCBC4
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 0,L", &Instruction1BitOperation::SET_0cL, 8),		//0xCBC5
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 0,(HL)", &Instruction1BitOperation::SET_0cpHLq, 16),	//0xCBC6
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 0,A", &Instruction1BitOperation::SET_0cA, 8),		//0xCBC7
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 1,B", &Instruction1BitOperation::SET_1cB, 8),		//0xCBC8
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 1,C", &Instruction1BitOperation::SET_1cC, 8),		//0xCBC9
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 1,D", &Instruction1BitOperation::SET_1cD, 8),		//0xCBCA
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 1,E", &Instruction1BitOperation::SET_1cE, 8),		//0xCBCB
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 1,H", &Instruction1BitOperation::SET_1cH, 8),		//0xCBCC
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 1,L", &Instruction1BitOperation::SET_1cL, 8),		//0xCBCD
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 1,(HL)", &Instruction1BitOperation::SET_1cpHLq, 16),	//0xCBCE
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 1,A", &Instruction1BitOperation::SET_1cA, 8),		//0xCBCF
		//0xCBD
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 2,B", &Instruction1BitOperation::SET_2cB, 8),		//0xCBD0
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 2,C", &Instruction1BitOperation::SET_2cC, 8),		//0xCBD1
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 2,D", &Instruction1BitOperation::SET_2cD, 8),		//0xCBD2
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 2,E", &Instruction1BitOperation::SET_2cE, 8),		//0xCBD3
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 2,H", &Instruction1BitOperation::SET_2cH, 8),		//0xCBD4
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 2,L", &Instruction1BitOperation::SET_2cL, 8),		//0xCBD5
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 2,(HL)", &Instruction1BitOperation::SET_2cpHLq, 16),	//0xCBD6
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 2,A", &Instruction1BitOperation::SET_2cA, 8),		//0xCBD7
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 3,B", &Instruction1BitOperation::SET_3cB, 8),		//0xCBD8
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 3,C", &Instruction1BitOperation::SET_3cC, 8),		//0xCBD9
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 3,D", &Instruction1BitOperation::SET_3cD, 8),		//0xCBDA
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 3,E", &Instruction1BitOperation::SET_3cE, 8),		//0xCBDB
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 3,H", &Instruction1BitOperation::SET_3cH, 8),		//0xCBDC
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 3,L", &Instruction1BitOperation::SET_3cL, 8),		//0xCBDD
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 3,(HL)", &Instruction1BitOperation::SET_3cpHLq, 16),	//0xCBDE
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 3,A", &Instruction1BitOperation::SET_3cA, 8),		//0xCBDF
		//0xCBE
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 4,B", &Instruction1BitOperation::SET_4cB, 8),		//0xCBE0
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 4,C", &Instruction1BitOperation::SET_4cC, 8),		//0xCBE1
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 4,D", &Instruction1BitOperation::SET_4cD, 8),		//0xCBE2
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 4,E", &Instruction1BitOperation::SET_4cE, 8),		//0xCBE3
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 4,H", &Instruction1BitOperation::SET_4cH, 8),		//0xCBE4
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 4,L", &Instruction1BitOperation::SET_4cL, 8),		//0xCBE5
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 4,(HL)", &Instruction1BitOperation::SET_4cpHLq, 16),	//0xCBE6
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 4,A", &Instruction1BitOperation::SET_4cA, 8),		//0xCBE7
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 5,B", &Instruction1BitOperation::SET_5cB, 8),		//0xCBE8
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 5,C", &Instruction1BitOperation::SET_5cC, 8),		//0xCBE9
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 5,D", &Instruction1BitOperation::SET_5cD, 8),		//0xCBEA
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 5,E", &Instruction1BitOperation::SET_5cE, 8),		//0xCBEB
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 5,H", &Instruction1BitOperation::SET_5cH, 8),		//0xCBEC
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 5,L", &Instruction1BitOperation::SET_5cL, 8),		//0xCBED
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 5,(HL)", &Instruction1BitOperation::SET_5cpHLq, 16),	//0xCBEE
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 5,A", &Instruction1BitOperation::SET_5cA, 8),		//0xCBEF
		//0xCBF
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 6,B", &Instruction1BitOperation::SET_6cB, 8),		//0xCBF0
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 6,C", &Instruction1BitOperation::SET_6cC, 8),		//0xCBF1
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 6,D", &Instruction1BitOperation::SET_6cD, 8),		//0xCBF2
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 6,E", &Instruction1BitOperation::SET_6cE, 8),		//0xCBF3
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 6,H", &Instruction1BitOperation::SET_6cH, 8),		//0xCBF4
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 6,L", &Instruction1BitOperation::SET_6cL, 8),		//0xCBF5
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 6,(HL)", &Instruction1BitOperation::SET_6cpHLq, 16),	//0xCBF6
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 6,A", &Instruction1BitOperation::SET_6cA, 8),		//0xCBF7
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 7,B", &Instruction1BitOperation::SET_7cB, 8),		//0xCBF8
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 7,C", &Instruction1BitOperation::SET_7cC, 8),		//0xCBF9
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 7,D", &Instruction1BitOperation::SET_7cD, 8),		//0xCBFA
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 7,E", &Instruction1BitOperation::SET_7cE, 8),		//0xCBFB
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 7,H", &Instruction1BitOperation::SET_7cH, 8),		//0xCBFC
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 7,L", &Instruction1BitOperation::SET_7cL, 8),		//0xCBFD
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 7,(HL)", &Instruction1BitOperation::SET_7cpHLq, 16),	//0xCBFE
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 7,A", &Instruction1BitOperation::SET_7cA, 8),		//0xCBFF
	};
}

u8 CPU::executeOpcode(u16 opcode)
{

	if (opcode == 0xCB) 
	{
		//read opcode
		return executeOpcodeCB(0x00);
	}

	(mInstructionSet[opcode]->getFunctionPointer())(*this);
	std::cout << mInstructionSet[opcode]->getName() << "\n";
	

	return mInstructionSet[opcode]->getClockCycle();
}

u8 CPU::executeOpcodeCB(u16 opcodeCB) 
{
	// read opcode
	//u16 opcodeCB = 0x00;
	(mInstructionSet[0x100 + opcodeCB]->getFunctionPointer())(*this);
	std::cout << mInstructionSet[0x100 + opcodeCB]->getName() << "\n";

	return (4 + mInstructionSet[0x100 + opcodeCB]->getClockCycle());
}

u8* CPU::getRegistries(const std::string& registry)
{
	using registryFuncPtr = u8*(Registries::*)();
	
	std::map<std::string, registryFuncPtr > registriesMap = {
		{"A", &Registries::getA},
		{"B", &Registries::getB},
		{"C", &Registries::getC},
		{"D", &Registries::getD},
		{"E", &Registries::getE},
		{"H", &Registries::getH},
		{"L", &Registries::getL}
	};

	return (mRegistries.*(registriesMap[registry]))();

}

combinedRegistries* CPU::getCombinedRegistries(const std::string& registries)
{
	using registryFuncPtr = combinedRegistries * (Registries::*)();

	std::map<std::string, registryFuncPtr > registriesMap = {
		{"AF", &Registries::getAF},
		{"BC", &Registries::getBC},
		{"DE", &Registries::getDE},
		{"HL", &Registries::getHL}
	};

	return (mRegistries.*(registriesMap[registries]))();
}

void CPU::setRegistries(const std::string& registry, u8 value)
{
	using registryFuncPtr = void(Registries::*)(u8);

	std::map<std::string, registryFuncPtr > registriesMap = {
		{"A", &Registries::setA},
		{"B", &Registries::setB},
		{"C", &Registries::setC},
		{"D", &Registries::setD},
		{"E", &Registries::setE},
		{"H", &Registries::setH},
		{"L", &Registries::setL}
	};

	(mRegistries.*registriesMap[registry])(value);

}

void CPU::setCombinedRegistries(const std::string& registries, u16 value)
{
	using registryFuncPtr = void(Registries::*)(u16);

	std::map<std::string, registryFuncPtr > registriesMap = {
		{"AF", &Registries::setAF},
		{"BC", &Registries::setBC},
		{"DE", &Registries::setDE},
		{"HL", &Registries::setHL}
	};

	(mRegistries.*registriesMap[registries])(value);
}

void CPU::writeMemory(const u16 & address, const u8 value)
{
	//TODO Verifier si on peut stocker une reference au lieu d'une copie
	mBus->write(address, value);
}

void CPU::writeMemory(const combinedRegistries& registries, const u8 value)
{
	//TODO Verifier si on peut stocker une reference au lieu d'une copie
	u16 address = (*registries.reg1 << 8) + *registries.reg2;
	mBus->write(address, value);
}

u8 CPU::readMemory(const u16& address) const
{
	//TODO Verifier si on peut envoyer une reference au lieu d'une copie
	u8 value = mBus->read(address);
	return value;
}

u8 CPU::readMemory(const combinedRegistries& registries) const
{
	//TODO Verifier si on peut envoyer une reference au lieu d'une copie
	u16 address = (*registries.reg1 << 8) + *registries.reg2;
	u8 value = mBus->read(address);
	return value;
}
