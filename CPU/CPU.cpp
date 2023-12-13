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
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"NOP",			&InstructionCPUControl::nop,		4),		//0x00
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"LD BC,d16",	&Instruction16BitLoad::LD_BCcd16,	12),	//0x01
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (BC),A",	&Instruction8BitLoad::LD_pBCqcA,	8),		//0x02
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"INC BC",		&Instruction16BitLogic::INC_BC,		8),		//0x03
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"INC B",		&Instruction8BitLogic::INC_B,		4),		//0x04
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"DEC B",		&Instruction8BitLogic::DEC_B,		4),		//0x05
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,d8",		&Instruction8BitLoad::LD_Bcd8,		8),		//0x06
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT,	"RLCA",			&InstructionRotateShift::RLCA,		4),		//0x07
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"LD (a16),SP",	&Instruction16BitLoad::LD_pa16qcSP,	20),	//0x08
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"ADD HL,BC",	&Instruction16BitLogic::ADD_HLcBC,	8),		//0x09
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,(BC)",	&Instruction8BitLoad::LD_AcpBCq,	8),		//0x0A
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"DEC BC",		&Instruction16BitLogic::DEC_BC,		8),		//0x0B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"INC C",		&Instruction8BitLogic::INC_C,		4),		//0x0C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"DEC C",		&Instruction8BitLogic::DEC_C,		4),		//0x0D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,d8",		&Instruction8BitLoad::LD_Ccd8,		8),		//0x0E
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT,	"RLRA",			&InstructionRotateShift::RRCA,		4),		//0x0F
		//0x1
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"STOP 0",		&InstructionCPUControl::stop_0,		4),		//0x10
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"LD DE,d16",	&Instruction16BitLoad::LD_BCcd16,	12),	//0x11
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (DE),A",	&Instruction8BitLoad::LD_pDEqcA,	8),		//0x12
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"INC DE",		&Instruction16BitLogic::INC_DE,		8),		//0x13
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"INC D",		&Instruction8BitLogic::INC_D,		4),		//0x14
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"DEC D",		&Instruction8BitLogic::DEC_D,		4),		//0x15
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,d8",		&Instruction8BitLoad::LD_Dcd8,		8),		//0x16
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT,	"RLA",			&InstructionRotateShift::RLA,		4),		//0x17
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JR r8",		&InstructionJump::JR_r8,			12),	//0x18
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"ADD HL,DE",	&Instruction16BitLogic::ADD_HLcDE,	8),		//0x19
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,(DE)",	&Instruction8BitLoad::LD_AcpDEq,	8),		//0x1A
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"DEC DE",		&Instruction16BitLogic::DEC_DE,		8),		//0x1B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"INC E",		&Instruction8BitLogic::INC_E,		4),		//0x1C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"DEC E",		&Instruction8BitLogic::DEC_E,		4),		//0x1D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,d8",		&Instruction8BitLoad::LD_Ecd8,		8),		//0x1E
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT,	"RRA",			&InstructionRotateShift::RRA,		4),		//0x1F
		//0x2
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JR NZ,r8",		&InstructionJump::JR_NZcr8,			12),	//0x20 TODO Verifier 12/8 cycles 
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"LD HL,d16",	&Instruction16BitLoad::LD_HLcd16,	12),	//0x21
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LDI (HL),A",	&Instruction8BitLoad::LDI_pHLqcA,	8),		//0x22
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"INC HL",		&Instruction16BitLogic::INC_HL,		8),		//0x23
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"INC H",		&Instruction8BitLogic::INC_H,		4),		//0x24
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"DEC H",		&Instruction8BitLogic::DEC_H,		4),		//0x25
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,d8",		&Instruction8BitLoad::LD_Hcd8,		8),		//0x26
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"DAA",			&Instruction8BitLogic::DAA,			4),		//0x27
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JR Z,r8",		&InstructionJump::JR_Zcr8,			12),	//0x28 TODO Verifier 12/8 cycles 
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"ADD HL,HL",	&Instruction16BitLogic::ADD_HLcHL,	8),		//0x29
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LDI A,(HL)",	&Instruction8BitLoad::LDI_AcpHLq,	8),		//0x2A
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"DEC HL",		&Instruction16BitLogic::DEC_HL,		8),		//0x2B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"INC L",		&Instruction8BitLogic::INC_L,		4),		//0x2C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"DEC L",		&Instruction8BitLogic::DEC_L,		4),		//0x2D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,d8",		&Instruction8BitLoad::LD_Lcd8,		8),		//0x2E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CPL",			&Instruction8BitLogic::CPL,			4),		//0x2F
		//0x3
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JR NC,r8",		&InstructionJump::JR_NCcr8,			12),	//0x30 TODO Verifier 12/8 cycles 
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"LD SP,d16",	&Instruction16BitLoad::LD_SPcd16,	12),	//0x31
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LDD (HL),A",	&Instruction8BitLoad::LDD_pHLqcA,	8),		//0x32
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"INC SP",		&Instruction16BitLogic::INC_SP,		8),		//0x33
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"INC (HL)",		&Instruction8BitLogic::INC_pHLq,	4),		//0x34
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"DEC (HL)",		&Instruction8BitLogic::DEC_pHLq,	4),		//0x35
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),d8",	&Instruction8BitLoad::LD_pHLqcd8,	12),	//0x36
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SCF",			&Instruction8BitLogic::SCF,			4),		//0x37
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JR C,r8",		&InstructionJump::JR_Ccr8,			12),	//0x38 TODO Verifier 12/8 cycles 
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"ADD HL,SP",	&Instruction16BitLogic::ADD_HLcSP,	8),		//0x39
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LDD A,(HL)",	&Instruction8BitLoad::LDD_AcpHLq,	8),		//0x3A
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"DEC SP",		&Instruction16BitLogic::DEC_SP,		8),		//0x3B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"INC A",		&Instruction8BitLogic::INC_A,		4),		//0x3C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"DEC A",		&Instruction8BitLogic::DEC_A,		4),		//0x3D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,d8",		&Instruction8BitLoad::LD_Acd8,		8),		//0x3E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CCF",			&Instruction8BitLogic::CCF,			4),		//0x3F
		//0x4
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,B",		&Instruction8BitLoad::LD_BcB,		4),		//0x40
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,C",		&Instruction8BitLoad::LD_BcC,		4),		//0x41
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,D",		&Instruction8BitLoad::LD_BcD,		4),		//0x42
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,E",		&Instruction8BitLoad::LD_BcE,		4),		//0x43
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,H",		&Instruction8BitLoad::LD_BcH,		4),		//0x44
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,L",		&Instruction8BitLoad::LD_BcL,		4),		//0x45
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,(HL)",	&Instruction8BitLoad::LD_BcpHLq,	8),		//0x46
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,A",		&Instruction8BitLoad::LD_BcA,		4),		//0x47
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,B",		&Instruction8BitLoad::LD_CcB,		4),		//0x48
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,C",		&Instruction8BitLoad::LD_CcC,		4),		//0x49
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,D",		&Instruction8BitLoad::LD_CcD,		4),		//0x4A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,E",		&Instruction8BitLoad::LD_CcE,		4),		//0x4B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,H",		&Instruction8BitLoad::LD_CcH,		4),		//0x4C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,L",		&Instruction8BitLoad::LD_CcL,		4),		//0x4D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,(HL)",	&Instruction8BitLoad::LD_CcpHLq,	8),		//0x4E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,A",		&Instruction8BitLoad::LD_CcA,		4),		//0x4F
		//0x5
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,B",		&Instruction8BitLoad::LD_DcB,		4),		//0x50
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,C",		&Instruction8BitLoad::LD_DcC,		4),		//0x51
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,D",		&Instruction8BitLoad::LD_DcD,		4),		//0x52
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,E",		&Instruction8BitLoad::LD_DcE,		4),		//0x53
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,H",		&Instruction8BitLoad::LD_DcH,		4),		//0x54
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,L",		&Instruction8BitLoad::LD_DcL,		4),		//0x55
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,(HL)",	&Instruction8BitLoad::LD_DcpHLq,	8),		//0x56
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,A",		&Instruction8BitLoad::LD_DcA,		4),		//0x57
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,B",		&Instruction8BitLoad::LD_EcB,		4),		//0x58
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,C",		&Instruction8BitLoad::LD_EcC,		4),		//0x59
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,D",		&Instruction8BitLoad::LD_EcD,		4),		//0x5A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,E",		&Instruction8BitLoad::LD_EcE,		4),		//0x5B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,H",		&Instruction8BitLoad::LD_EcH,		4),		//0x5C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,L",		&Instruction8BitLoad::LD_EcL,		4),		//0x5D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,(HL)",	&Instruction8BitLoad::LD_EcpHLq,	8),		//0x5E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,A",		&Instruction8BitLoad::LD_EcA,		4),		//0x5F
		//0x6
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,B",		&Instruction8BitLoad::LD_HcB,		4),		//0x60
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,C",		&Instruction8BitLoad::LD_HcC,		4),		//0x61
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,D",		&Instruction8BitLoad::LD_HcD,		4),		//0x62
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,E",		&Instruction8BitLoad::LD_HcE,		4),		//0x63
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,H",		&Instruction8BitLoad::LD_HcH,		4),		//0x64
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,L",		&Instruction8BitLoad::LD_HcL,		4),		//0x65
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,(HL)",	&Instruction8BitLoad::LD_HcpHLq,	8),		//0x66
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,A",		&Instruction8BitLoad::LD_HcA,		4),		//0x67
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,B",		&Instruction8BitLoad::LD_LcB,		4),		//0x68
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,C",		&Instruction8BitLoad::LD_LcC,		4),		//0x69
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,D",		&Instruction8BitLoad::LD_LcD,		4),		//0x6A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,E",		&Instruction8BitLoad::LD_LcE,		4),		//0x6B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,H",		&Instruction8BitLoad::LD_LcH,		4),		//0x6C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,L",		&Instruction8BitLoad::LD_LcL,		4),		//0x6D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,(HL)",	&Instruction8BitLoad::LD_LcpHLq,	8),		//0x6E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,A",		&Instruction8BitLoad::LD_LcA,		4),		//0x6F
		//0x7
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),B",	&Instruction8BitLoad::LD_pHLqcB,	8),		//0x70
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),C",	&Instruction8BitLoad::LD_pHLqcC,	8),		//0x71
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),D",	&Instruction8BitLoad::LD_pHLqcD,	8),		//0x72
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),E",	&Instruction8BitLoad::LD_pHLqcE,	8),		//0x73
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),H",	&Instruction8BitLoad::LD_pHLqcH,	8),		//0x74
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),L",	&Instruction8BitLoad::LD_pHLqcL,	8),		//0x75
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"HALT",			&InstructionCPUControl::halt,		4),		//0x76																																	//0x76
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),A",	&Instruction8BitLoad::LD_pHLqcA,	8),		//0x77
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,B",		&Instruction8BitLoad::LD_AcB,		4),		//0x78
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,C",		&Instruction8BitLoad::LD_AcC,		4),		//0x79
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,D",		&Instruction8BitLoad::LD_AcD,		4),		//0x7A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,E",		&Instruction8BitLoad::LD_AcE,		4),		//0x7B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,H",		&Instruction8BitLoad::LD_AcH,		4),		//0x7C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,L",		&Instruction8BitLoad::LD_AcL,		4),		//0x7D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,(HL)",	&Instruction8BitLoad::LD_AcpHLq,	8),		//0x7E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,A",		&Instruction8BitLoad::LD_AcA,		4),		//0x7F
		//0x8
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADD A,B",		&Instruction8BitLogic::ADD_AcB,		4),		//0x80
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADD A,C",		&Instruction8BitLogic::ADD_AcC,		4),		//0x81
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADD A,D",		&Instruction8BitLogic::ADD_AcD,		4),		//0x82
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADD A,E",		&Instruction8BitLogic::ADD_AcE,		4),		//0x83
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADD A,H",		&Instruction8BitLogic::ADD_AcH,		4),		//0x84
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADD A,L",		&Instruction8BitLogic::ADD_AcL,		4),		//0x85
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADD A,(HL)",	&Instruction8BitLogic::ADD_AcpHLq,	8),		//0x86
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADD A,A",		&Instruction8BitLogic::ADD_AcA,		4),		//0x87
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADC A,B",		&Instruction8BitLogic::ADC_AcB,		4),		//0x88
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADC A,C",		&Instruction8BitLogic::ADC_AcC,		4),		//0x89
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADC A,D",		&Instruction8BitLogic::ADC_AcD,		4),		//0x8A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADC A,E",		&Instruction8BitLogic::ADC_AcE,		4),		//0x8B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADC A,H",		&Instruction8BitLogic::ADC_AcH,		4),		//0x8C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADC A,L",		&Instruction8BitLogic::ADC_AcL,		4),		//0x8D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADC A,(HL)",	&Instruction8BitLogic::ADC_AcpHLq,	8),		//0x8E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADC A,A",		&Instruction8BitLogic::ADC_AcA,		4),		//0x8F
		//0x9
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SUB B",		&Instruction8BitLogic::SUB_B,		4),		//0x90
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SUB C",		&Instruction8BitLogic::SUB_C,		4),		//0x91
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SUB D",		&Instruction8BitLogic::SUB_D,		4),		//0x92
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SUB E",		&Instruction8BitLogic::SUB_E,		4),		//0x93
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SUB H",		&Instruction8BitLogic::SUB_H,		4),		//0x94
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SUB L",		&Instruction8BitLogic::SUB_L,		4),		//0x95
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SUB (HL)",		&Instruction8BitLogic::SUB_pHLq,	8),		//0x96
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SUB A",		&Instruction8BitLogic::SUB_A,		4),		//0x97
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SBC A,B",		&Instruction8BitLogic::SBC_AcB,		4),		//0x98
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SBC A,C",		&Instruction8BitLogic::SBC_AcC,		4),		//0x99
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SBC A,D",		&Instruction8BitLogic::SBC_AcD,		4),		//0x9A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SBC A,E",		&Instruction8BitLogic::SBC_AcE,		4),		//0x9B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SBC A,H",		&Instruction8BitLogic::SBC_AcH,		4),		//0x9C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SBC A,L",		&Instruction8BitLogic::SBC_AcL,		4),		//0x9D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SBC A,(HL)",	&Instruction8BitLogic::SBC_AcpHLq,	8),		//0x9E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SBC A,A",		&Instruction8BitLogic::SBC_AcA,		4),		//0x9F		
		//0xA
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"AND B",		&Instruction8BitLogic::AND_B,		4),		//0xA0
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"AND C",		&Instruction8BitLogic::AND_C,		4),		//0xA1
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"AND D",		&Instruction8BitLogic::AND_D,		4),		//0xA2
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"AND E",		&Instruction8BitLogic::AND_E,		4),		//0xA3
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"AND H",		&Instruction8BitLogic::AND_H,		4),		//0xA4
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"AND L",		&Instruction8BitLogic::AND_L,		4),		//0xA5
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"AND (HL)",		&Instruction8BitLogic::AND_pHLq,	8),		//0xA6
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"AND A",		&Instruction8BitLogic::AND_A,		4),		//0xA7
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"XOR B",		&Instruction8BitLogic::XOR_B,		4),		//0xA8
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"XOR C",		&Instruction8BitLogic::XOR_C,		4),		//0xA9
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"XOR D",		&Instruction8BitLogic::XOR_D,		4),		//0xAA
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"XOR E",		&Instruction8BitLogic::XOR_E,		4),		//0xAB
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"XOR H",		&Instruction8BitLogic::XOR_H,		4),		//0xAC
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"XOR L",		&Instruction8BitLogic::XOR_L,		4),		//0xAD
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"XOR (HL)",		&Instruction8BitLogic::XOR_pHLq,	8),		//0xAE
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"XOR A",		&Instruction8BitLogic::XOR_A,		4),		//0xAF		
		//0xB
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"OR B",			&Instruction8BitLogic::OR_B,		4),		//0xB0
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"OR C",			&Instruction8BitLogic::OR_C,		4),		//0xB1
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"OR D",			&Instruction8BitLogic::OR_D,		4),		//0xB2
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"OR E",			&Instruction8BitLogic::OR_E,		4),		//0xB3
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"OR H",			&Instruction8BitLogic::OR_H,		4),		//0xB4
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"OR L",			&Instruction8BitLogic::OR_L,		4),		//0xB5
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"OR (HL)",		&Instruction8BitLogic::OR_pHLq,		8),		//0xB6
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"OR A",			&Instruction8BitLogic::OR_A,		4),		//0xB7
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CP B",			&Instruction8BitLogic::CP_B,		4),		//0xB8
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CP C",			&Instruction8BitLogic::CP_C,		4),		//0xB9
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CP D",			&Instruction8BitLogic::CP_D,		4),		//0xBA
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CP E",			&Instruction8BitLogic::CP_E,		4),		//0xBB
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CP H",			&Instruction8BitLogic::CP_H,		4),		//0xBC
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CP L",			&Instruction8BitLogic::CP_L,		4),		//0xBD
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CP (HL)",		&Instruction8BitLogic::CP_pHLq,		8),		//0xBE
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CP A",			&Instruction8BitLogic::CP_A,		4),		//0xBF
		//0xC
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RET NZ",		&InstructionJump::RET_NZ,			20),	//0xC0 TODO Verifier 20/8 cycles 
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"POP BC",		&Instruction16BitLoad::POP_BC,		12),	//0xC1
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JP NZ,a16",	&InstructionJump::JP_NZca16,		16),	//0xC2 TODO Verifier 16/12 cycles 
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JP a16",		&InstructionJump::JP_a16,			16),	//0xC3 
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"CALL NZ,a16",	&InstructionJump::CALL_NZca16,		24),	//0xC4 TODO Verifier 24/12 cycles
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"PUSH BC",		&Instruction16BitLoad::PUSH_BC,		16),	//0xC5
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADD A,d8",		&Instruction8BitLogic::ADD_Acd8,	8),		//0xC6
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RST 00H",		&InstructionJump::RST_00H,			16),	//0xC7 
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RET Z",		&InstructionJump::RET_Z,			20),	//0xC8 TODO Verifier 20/8 cycles
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RET",			&InstructionJump::RET,				16),	//0xC9 
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JP Z,a16",		&InstructionJump::JP_Zca16,			16),	//0xCA TODO Verifier 16/12 cycles
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"PREFIX CB",	&InstructionCPUControl::prefix_cb,	4),		//0xCB
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"CALL Z,a16",	&InstructionJump::CALL_Zca16,		24),	//0xCC TODO Verifier 24/12 cycles
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"CALL a16",		&InstructionJump::CALL_a16,			24),	//0xCD
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADC A,d8",		&Instruction8BitLogic::ADC_Acd8,	8),		//0xCE
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RST 08H",		&InstructionJump::RST_08H,			16),	//0xCF
		//0xD
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RET NC",		&InstructionJump::RET_NC,			20),	//0xD0 TODO Verifier 20/8 cycles 
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"POP DE",		&Instruction16BitLoad::POP_DE,		12),	//0xD1
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JP NC,a16",	&InstructionJump::JP_NCca16,		16),	//0xD2 TODO Verifier 16/12 cycles 
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,  "",				&InstructionCPUControl::nop,		4),		//0xD3
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"CALL NC,a16",	&InstructionJump::CALL_NCca16,		24),	//0xD4 TODO Verifier 24/12 cycles
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"PUSH DE",		&Instruction16BitLoad::PUSH_DE,		16),	//0xD5
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SUB d8",		&Instruction8BitLogic::SUB_d8,		8),		//0xD6
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RST 10H",		&InstructionJump::RST_10H,			16),	//0xD7 
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RET C",		&InstructionJump::RET_C,			20),	//0xD8 TODO Verifier 20/8 cycles
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RETI",			&InstructionJump::RETI,				16),	//0xD9 
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JP C,a16",		&InstructionJump::JP_Cca16,			16),	//0xDA TODO Verifier 16/12 cycles
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop,		4),		//0xDB
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"CALL C,a16",	&InstructionJump::CALL_Cca16,		24),	//0xDC TODO Verifier 24/12 cycles
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop,		4),		//0xDD
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SBC A,d8",		&Instruction8BitLogic::SBC_Acd8,	8),		//0xDE
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RST 18H",		&InstructionJump::RST_18H,			16),	//0xDF
		//0xE
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LDH (a8),A",	&Instruction8BitLoad::LDH_pa8qcA,	4),		//0xE0
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"POP HL",		&Instruction16BitLoad::POP_HL,		12),	//0xE1
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (C),A",		&Instruction8BitLoad::LD_pCqcA,		4),		//0xE2
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop,		4),		//0xE3
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop,		4),		//0xE4
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"PUSH HL",		&Instruction16BitLoad::PUSH_HL,		16),	//0xE5
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"AND d8",		&Instruction8BitLogic::AND_d8,		8),		//0xE6
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RST 20H",		&InstructionJump::RST_20H,			16),	//0xE7
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"ADD SP,r8",	&Instruction16BitLogic::ADD_SPcr8,	16),	//0xE8
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JP (HL)",		&InstructionJump::JP_pHLq,			4),		//0xE9
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LDH (a16),A",	&Instruction8BitLoad::LDH_pa16qcA,	4),		//0xEA
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop,		4),		//0xEB
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop,		4),		//0xEC
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop,		4),		//0xED
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"XOR d8",		&Instruction8BitLogic::XOR_d8,		8),		//0xEE
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RST 28H",		&InstructionJump::RST_28H,			16),	//0xEF
		//0xF
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LDH A,(a8)",	&Instruction8BitLoad::LDH_Acpa8q,	4),		//0xF0
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"POP AF",		&Instruction16BitLoad::POP_AF,		12),	//0xF1
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,(C)",		&Instruction8BitLoad::LD_AcpCq,		4),		//0xF2
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"DI",			&InstructionCPUControl::di,			4),		//0xF3
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop,		4),		//0xF4
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"PUSH AF",		&Instruction16BitLoad::PUSH_AF,		16),	//0xF5
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"OR d8",		&Instruction8BitLogic::OR_d8,		8),		//0xF6
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RST 30H",		&InstructionJump::RST_30H,			16),	//0xF7
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"LDHL SP,r8",	&Instruction16BitLoad::LDHL_SPcr8,	12),	//0xF8
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"LD SP,HL",		&Instruction16BitLoad::LD_SPcHL,	8),		//0xF9
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LDH A,(a16)",	&Instruction8BitLoad::LDH_Acpa16q,	4),		//0xFA
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"EI",			&InstructionCPUControl::ei,			4),		//0xFB
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop,		4),		//0xFC
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop,		4),		//0xFD
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CP d8",		&Instruction8BitLogic::CP_d8,		8),		//0xFE
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RST 38H",		&InstructionJump::RST_38H,			16),	//0xFF

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

u8 CPU::executeOpcode(u16 opcode) 
{

	if (opcode == 0xCB) 
	{
		return executeOpcodeCB();
	}

	(mInstructionSet[opcode]->getFunctionPointer())(*this);
	std::cout << mInstructionSet[opcode]->getName() << "\n";
	

	return mInstructionSet[opcode]->getClockCycle();
}

u8 CPU::executeOpcodeCB() 
{
	// read opcode
	u16 opcodeCB = 0x00;
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
