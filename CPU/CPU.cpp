#include "pch.h"

#include "CPU.h"
#include "BootRom/BootRom.h"
#include "Interrupts/InterruptsManager.h"
//#include "Utils/Log.h"

#include "ImGui/ImGuiRenderer.h"


u16 CPU::mPC{ 0 };

CPU::CPU()
{
}

CPU::CPU(std::shared_ptr<Bus> bus, std::shared_ptr<PPU> ppu)
	:	mBus(bus), mPPU(ppu)
{
	initInstructionSet();
}

void CPU::initInstructionSet() 
{
	InstructionFactory instructionFactory(mRegistries, mBus);

	mInstructionSet =
	{
		//0x0
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"NOP",			&InstructionCPUControl::nop),		//0x00
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"LD BC,d16",	&Instruction16BitLoad::LD_BCcd16),	//0x01
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (BC),A",	&Instruction8BitLoad::LD_pBCqcA),	//0x02
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"INC BC",		&Instruction16BitLogic::INC_BC),	//0x03
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"INC B",		&Instruction8BitLogic::INC_B),		//0x04
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"DEC B",		&Instruction8BitLogic::DEC_B),		//0x05
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,d8",		&Instruction8BitLoad::LD_Bcd8),		//0x06
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT,	"RLCA",			&InstructionRotateShift::RLCA),		//0x07
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"LD (a16),SP",	&Instruction16BitLoad::LD_pa16qcSP),//0x08
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"ADD HL,BC",	&Instruction16BitLogic::ADD_HLcBC),	//0x09
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,(BC)",	&Instruction8BitLoad::LD_AcpBCq),	//0x0A
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"DEC BC",		&Instruction16BitLogic::DEC_BC),	//0x0B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"INC C",		&Instruction8BitLogic::INC_C),		//0x0C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"DEC C",		&Instruction8BitLogic::DEC_C),		//0x0D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,d8",		&Instruction8BitLoad::LD_Ccd8),		//0x0E
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT,	"RRCA",			&InstructionRotateShift::RRCA),		//0x0F
		//0x1
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"STOP 0",		&InstructionCPUControl::stop_0),	//0x10
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"LD DE,d16",	&Instruction16BitLoad::LD_DEcd16),	//0x11
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (DE),A",	&Instruction8BitLoad::LD_pDEqcA),	//0x12
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"INC DE",		&Instruction16BitLogic::INC_DE),	//0x13
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"INC D",		&Instruction8BitLogic::INC_D),		//0x14
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"DEC D",		&Instruction8BitLogic::DEC_D),		//0x15
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,d8",		&Instruction8BitLoad::LD_Dcd8),		//0x16
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT,	"RLA",			&InstructionRotateShift::RLA),		//0x17
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JR r8",		&InstructionJump::JR_r8),			//0x18
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"ADD HL,DE",	&Instruction16BitLogic::ADD_HLcDE),	//0x19
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,(DE)",	&Instruction8BitLoad::LD_AcpDEq),	//0x1A
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"DEC DE",		&Instruction16BitLogic::DEC_DE),	//0x1B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"INC E",		&Instruction8BitLogic::INC_E),		//0x1C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"DEC E",		&Instruction8BitLogic::DEC_E),		//0x1D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,d8",		&Instruction8BitLoad::LD_Ecd8),		//0x1E
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT,	"RRA",			&InstructionRotateShift::RRA),		//0x1F
		//0x2
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JR NZ,r8",		&InstructionJump::JR_NZcr8),		//0x20 
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"LD HL,d16",	&Instruction16BitLoad::LD_HLcd16),	//0x21
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LDI (HL),A",	&Instruction8BitLoad::LDI_pHLqcA),	//0x22
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"INC HL",		&Instruction16BitLogic::INC_HL),	//0x23
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"INC H",		&Instruction8BitLogic::INC_H),		//0x24
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"DEC H",		&Instruction8BitLogic::DEC_H),		//0x25
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,d8",		&Instruction8BitLoad::LD_Hcd8),		//0x26
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"DAA",			&Instruction8BitLogic::DAA),		//0x27
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JR Z,r8",		&InstructionJump::JR_Zcr8),			//0x28 
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"ADD HL,HL",	&Instruction16BitLogic::ADD_HLcHL),	//0x29
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LDI A,(HL)",	&Instruction8BitLoad::LDI_AcpHLq),	//0x2A
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"DEC HL",		&Instruction16BitLogic::DEC_HL),	//0x2B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"INC L",		&Instruction8BitLogic::INC_L),		//0x2C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"DEC L",		&Instruction8BitLogic::DEC_L),		//0x2D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,d8",		&Instruction8BitLoad::LD_Lcd8),		//0x2E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CPL",			&Instruction8BitLogic::CPL),		//0x2F
		//0x3
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JR NC,r8",		&InstructionJump::JR_NCcr8),		//0x30 
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"LD SP,d16",	&Instruction16BitLoad::LD_SPcd16),	//0x31
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LDD (HL),A",	&Instruction8BitLoad::LDD_pHLqcA),	//0x32
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"INC SP",		&Instruction16BitLogic::INC_SP),	//0x33
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"INC (HL)",		&Instruction8BitLogic::INC_pHLq),	//0x34
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"DEC (HL)",		&Instruction8BitLogic::DEC_pHLq),	//0x35
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),d8",	&Instruction8BitLoad::LD_pHLqcd8),	//0x36
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SCF",			&Instruction8BitLogic::SCF),		//0x37
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JR C,r8",		&InstructionJump::JR_Ccr8),			//0x38 
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"ADD HL,SP",	&Instruction16BitLogic::ADD_HLcSP),	//0x39
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LDD A,(HL)",	&Instruction8BitLoad::LDD_AcpHLq),	//0x3A
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"DEC SP",		&Instruction16BitLogic::DEC_SP),	//0x3B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"INC A",		&Instruction8BitLogic::INC_A),		//0x3C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"DEC A",		&Instruction8BitLogic::DEC_A),		//0x3D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,d8",		&Instruction8BitLoad::LD_Acd8),		//0x3E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CCF",			&Instruction8BitLogic::CCF),		//0x3F
		//0x4
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,B",		&Instruction8BitLoad::LD_BcB),		//0x40
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,C",		&Instruction8BitLoad::LD_BcC),		//0x41
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,D",		&Instruction8BitLoad::LD_BcD),		//0x42
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,E",		&Instruction8BitLoad::LD_BcE),		//0x43
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,H",		&Instruction8BitLoad::LD_BcH),		//0x44
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,L",		&Instruction8BitLoad::LD_BcL),		//0x45
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,(HL)",	&Instruction8BitLoad::LD_BcpHLq),	//0x46
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD B,A",		&Instruction8BitLoad::LD_BcA),		//0x47
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,B",		&Instruction8BitLoad::LD_CcB),		//0x48
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,C",		&Instruction8BitLoad::LD_CcC),		//0x49
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,D",		&Instruction8BitLoad::LD_CcD),		//0x4A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,E",		&Instruction8BitLoad::LD_CcE),		//0x4B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,H",		&Instruction8BitLoad::LD_CcH),		//0x4C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,L",		&Instruction8BitLoad::LD_CcL),		//0x4D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,(HL)",	&Instruction8BitLoad::LD_CcpHLq),	//0x4E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD C,A",		&Instruction8BitLoad::LD_CcA),		//0x4F
		//0x5
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,B",		&Instruction8BitLoad::LD_DcB),		//0x50
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,C",		&Instruction8BitLoad::LD_DcC),		//0x51
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,D",		&Instruction8BitLoad::LD_DcD),		//0x52
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,E",		&Instruction8BitLoad::LD_DcE),		//0x53
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,H",		&Instruction8BitLoad::LD_DcH),		//0x54
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,L",		&Instruction8BitLoad::LD_DcL),		//0x55
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,(HL)",	&Instruction8BitLoad::LD_DcpHLq),	//0x56
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD D,A",		&Instruction8BitLoad::LD_DcA),		//0x57
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,B",		&Instruction8BitLoad::LD_EcB),		//0x58
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,C",		&Instruction8BitLoad::LD_EcC),		//0x59
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,D",		&Instruction8BitLoad::LD_EcD),		//0x5A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,E",		&Instruction8BitLoad::LD_EcE),		//0x5B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,H",		&Instruction8BitLoad::LD_EcH),		//0x5C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,L",		&Instruction8BitLoad::LD_EcL),		//0x5D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,(HL)",	&Instruction8BitLoad::LD_EcpHLq),	//0x5E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD E,A",		&Instruction8BitLoad::LD_EcA),		//0x5F
		//0x6
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,B",		&Instruction8BitLoad::LD_HcB),		//0x60
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,C",		&Instruction8BitLoad::LD_HcC),		//0x61
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,D",		&Instruction8BitLoad::LD_HcD),		//0x62
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,E",		&Instruction8BitLoad::LD_HcE),		//0x63
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,H",		&Instruction8BitLoad::LD_HcH),		//0x64
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,L",		&Instruction8BitLoad::LD_HcL),		//0x65
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,(HL)",	&Instruction8BitLoad::LD_HcpHLq),	//0x66
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD H,A",		&Instruction8BitLoad::LD_HcA),		//0x67
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,B",		&Instruction8BitLoad::LD_LcB),		//0x68
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,C",		&Instruction8BitLoad::LD_LcC),		//0x69
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,D",		&Instruction8BitLoad::LD_LcD),		//0x6A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,E",		&Instruction8BitLoad::LD_LcE),		//0x6B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,H",		&Instruction8BitLoad::LD_LcH),		//0x6C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,L",		&Instruction8BitLoad::LD_LcL),		//0x6D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,(HL)",	&Instruction8BitLoad::LD_LcpHLq),	//0x6E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD L,A",		&Instruction8BitLoad::LD_LcA),		//0x6F
		//0x7
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),B",	&Instruction8BitLoad::LD_pHLqcB),	//0x70
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),C",	&Instruction8BitLoad::LD_pHLqcC),	//0x71
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),D",	&Instruction8BitLoad::LD_pHLqcD),	//0x72
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),E",	&Instruction8BitLoad::LD_pHLqcE),	//0x73
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),H",	&Instruction8BitLoad::LD_pHLqcH),	//0x74
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),L",	&Instruction8BitLoad::LD_pHLqcL),	//0x75
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"HALT",			&InstructionCPUControl::halt),		//0x76																																	//0x76
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (HL),A",	&Instruction8BitLoad::LD_pHLqcA),	//0x77
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,B",		&Instruction8BitLoad::LD_AcB),		//0x78
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,C",		&Instruction8BitLoad::LD_AcC),		//0x79
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,D",		&Instruction8BitLoad::LD_AcD),		//0x7A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,E",		&Instruction8BitLoad::LD_AcE),		//0x7B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,H",		&Instruction8BitLoad::LD_AcH),		//0x7C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,L",		&Instruction8BitLoad::LD_AcL),		//0x7D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,(HL)",	&Instruction8BitLoad::LD_AcpHLq),	//0x7E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,A",		&Instruction8BitLoad::LD_AcA),		//0x7F
		//0x8
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADD A,B",		&Instruction8BitLogic::ADD_AcB),	//0x80
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADD A,C",		&Instruction8BitLogic::ADD_AcC),	//0x81
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADD A,D",		&Instruction8BitLogic::ADD_AcD),	//0x82
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADD A,E",		&Instruction8BitLogic::ADD_AcE),	//0x83
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADD A,H",		&Instruction8BitLogic::ADD_AcH),	//0x84
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADD A,L",		&Instruction8BitLogic::ADD_AcL),	//0x85
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADD A,(HL)",	&Instruction8BitLogic::ADD_AcpHLq),	//0x86
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADD A,A",		&Instruction8BitLogic::ADD_AcA),	//0x87
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADC A,B",		&Instruction8BitLogic::ADC_AcB),	//0x88
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADC A,C",		&Instruction8BitLogic::ADC_AcC),	//0x89
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADC A,D",		&Instruction8BitLogic::ADC_AcD),	//0x8A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADC A,E",		&Instruction8BitLogic::ADC_AcE),	//0x8B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADC A,H",		&Instruction8BitLogic::ADC_AcH),	//0x8C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADC A,L",		&Instruction8BitLogic::ADC_AcL),	//0x8D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADC A,(HL)",	&Instruction8BitLogic::ADC_AcpHLq),	//0x8E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADC A,A",		&Instruction8BitLogic::ADC_AcA),	//0x8F
		//0x9
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SUB B",		&Instruction8BitLogic::SUB_B),		//0x90
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SUB C",		&Instruction8BitLogic::SUB_C),		//0x91
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SUB D",		&Instruction8BitLogic::SUB_D),		//0x92
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SUB E",		&Instruction8BitLogic::SUB_E),		//0x93
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SUB H",		&Instruction8BitLogic::SUB_H),		//0x94
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SUB L",		&Instruction8BitLogic::SUB_L),		//0x95
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SUB (HL)",		&Instruction8BitLogic::SUB_pHLq),	//0x96
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SUB A",		&Instruction8BitLogic::SUB_A),		//0x97
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SBC A,B",		&Instruction8BitLogic::SBC_AcB),	//0x98
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SBC A,C",		&Instruction8BitLogic::SBC_AcC),	//0x99
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SBC A,D",		&Instruction8BitLogic::SBC_AcD),	//0x9A
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SBC A,E",		&Instruction8BitLogic::SBC_AcE),	//0x9B
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SBC A,H",		&Instruction8BitLogic::SBC_AcH),	//0x9C
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SBC A,L",		&Instruction8BitLogic::SBC_AcL),	//0x9D
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SBC A,(HL)",	&Instruction8BitLogic::SBC_AcpHLq),	//0x9E
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SBC A,A",		&Instruction8BitLogic::SBC_AcA),	//0x9F		
		//0xA
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"AND B",		&Instruction8BitLogic::AND_B),		//0xA0
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"AND C",		&Instruction8BitLogic::AND_C),		//0xA1
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"AND D",		&Instruction8BitLogic::AND_D),		//0xA2
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"AND E",		&Instruction8BitLogic::AND_E),		//0xA3
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"AND H",		&Instruction8BitLogic::AND_H),		//0xA4
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"AND L",		&Instruction8BitLogic::AND_L),		//0xA5
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"AND (HL)",		&Instruction8BitLogic::AND_pHLq),	//0xA6
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"AND A",		&Instruction8BitLogic::AND_A),		//0xA7
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"XOR B",		&Instruction8BitLogic::XOR_B),		//0xA8
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"XOR C",		&Instruction8BitLogic::XOR_C),		//0xA9
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"XOR D",		&Instruction8BitLogic::XOR_D),		//0xAA
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"XOR E",		&Instruction8BitLogic::XOR_E),		//0xAB
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"XOR H",		&Instruction8BitLogic::XOR_H),		//0xAC
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"XOR L",		&Instruction8BitLogic::XOR_L),		//0xAD
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"XOR (HL)",		&Instruction8BitLogic::XOR_pHLq),	//0xAE
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"XOR A",		&Instruction8BitLogic::XOR_A),		//0xAF		
		//0xB
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"OR B",			&Instruction8BitLogic::OR_B),		//0xB0
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"OR C",			&Instruction8BitLogic::OR_C),		//0xB1
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"OR D",			&Instruction8BitLogic::OR_D),		//0xB2
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"OR E",			&Instruction8BitLogic::OR_E),		//0xB3
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"OR H",			&Instruction8BitLogic::OR_H),		//0xB4
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"OR L",			&Instruction8BitLogic::OR_L),		//0xB5
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"OR (HL)",		&Instruction8BitLogic::OR_pHLq),	//0xB6
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"OR A",			&Instruction8BitLogic::OR_A),		//0xB7
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CP B",			&Instruction8BitLogic::CP_B),		//0xB8
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CP C",			&Instruction8BitLogic::CP_C),		//0xB9
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CP D",			&Instruction8BitLogic::CP_D),		//0xBA
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CP E",			&Instruction8BitLogic::CP_E),		//0xBB
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CP H",			&Instruction8BitLogic::CP_H),		//0xBC
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CP L",			&Instruction8BitLogic::CP_L),		//0xBD
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CP (HL)",		&Instruction8BitLogic::CP_pHLq),	//0xBE
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CP A",			&Instruction8BitLogic::CP_A),		//0xBF
		//0xC
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RET NZ",		&InstructionJump::RET_NZ),			//0xC0 
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"POP BC",		&Instruction16BitLoad::POP_BC),		//0xC1
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JP NZ,a16",	&InstructionJump::JP_NZca16),		//0xC2 
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JP a16",		&InstructionJump::JP_a16),			//0xC3 
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"CALL NZ,a16",	&InstructionJump::CALL_NZca16),		//0xC4 
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"PUSH BC",		&Instruction16BitLoad::PUSH_BC),	//0xC5
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADD A,d8",		&Instruction8BitLogic::ADD_Acd8),	//0xC6
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RST 00H",		&InstructionJump::RST_00H),			//0xC7 
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RET Z",		&InstructionJump::RET_Z),			//0xC8 
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RET",			&InstructionJump::RET),				//0xC9 
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JP Z,a16",		&InstructionJump::JP_Zca16),		//0xCA 
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"PREFIX CB",	&InstructionCPUControl::prefix_cb),	//0xCB
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"CALL Z,a16",	&InstructionJump::CALL_Zca16),		//0xCC 
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"CALL a16",		&InstructionJump::CALL_a16),		//0xCD
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"ADC A,d8",		&Instruction8BitLogic::ADC_Acd8),	//0xCE
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RST 08H",		&InstructionJump::RST_08H),			//0xCF
		//0xD
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RET NC",		&InstructionJump::RET_NC),			//0xD0 
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"POP DE",		&Instruction16BitLoad::POP_DE),		//0xD1
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JP NC,a16",	&InstructionJump::JP_NCca16),		//0xD2 
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,  "",				&InstructionCPUControl::nop),		//0xD3
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"CALL NC,a16",	&InstructionJump::CALL_NCca16),		//0xD4 
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"PUSH DE",		&Instruction16BitLoad::PUSH_DE),	//0xD5
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SUB d8",		&Instruction8BitLogic::SUB_d8),		//0xD6
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RST 10H",		&InstructionJump::RST_10H),			//0xD7 
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RET C",		&InstructionJump::RET_C),			//0xD8 
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RETI",			&InstructionJump::RETI),			//0xD9 
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JP C,a16",		&InstructionJump::JP_Cca16),		//0xDA 
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop),		//0xDB
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"CALL C,a16",	&InstructionJump::CALL_Cca16),		//0xDC 
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop),		//0xDD
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"SBC A,d8",		&Instruction8BitLogic::SBC_Acd8),	//0xDE
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RST 18H",		&InstructionJump::RST_18H),			//0xDF
		//0xE
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LDH (a8),A",	&Instruction8BitLoad::LDH_pa8qcA),	//0xE0
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"POP HL",		&Instruction16BitLoad::POP_HL),		//0xE1
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (C),A",		&Instruction8BitLoad::LD_pCqcA),	//0xE2
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop),		//0xE3
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop),		//0xE4
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"PUSH HL",		&Instruction16BitLoad::PUSH_HL),	//0xE5
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"AND d8",		&Instruction8BitLogic::AND_d8),		//0xE6
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RST 20H",		&InstructionJump::RST_20H),			//0xE7
		instructionFactory.createInstruction(InstructionEnum::I16BITLOGIC,	"ADD SP,r8",	&Instruction16BitLogic::ADD_SPcr8),	//0xE8
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"JP (HL)",		&InstructionJump::JP_pHLq),			//0xE9
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD (a16),A",	&Instruction8BitLoad::LD_pa16qcA),	//0xEA
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop),		//0xEB
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop),		//0xEC
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop),		//0xED
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"XOR d8",		&Instruction8BitLogic::XOR_d8),		//0xEE
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RST 28H",		&InstructionJump::RST_28H),			//0xEF
		//0xF
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LDH A,(a8)",	&Instruction8BitLoad::LDH_Acpa8q),	//0xF0
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"POP AF",		&Instruction16BitLoad::POP_AF),		//0xF1
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,(C)",		&Instruction8BitLoad::LD_AcpCq),	//0xF2
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"DI",			&InstructionCPUControl::di),		//0xF3
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop),		//0xF4
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"PUSH AF",		&Instruction16BitLoad::PUSH_AF),	//0xF5
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"OR d8",		&Instruction8BitLogic::OR_d8),		//0xF6
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RST 30H",		&InstructionJump::RST_30H),			//0xF7
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"LDHL SP,r8",	&Instruction16BitLoad::LDHL_SPcr8),	//0xF8
		instructionFactory.createInstruction(InstructionEnum::I16BITLOAD,	"LD SP,HL",		&Instruction16BitLoad::LD_SPcHL),	//0xF9
		instructionFactory.createInstruction(InstructionEnum::I8BITLOAD,	"LD A,(a16)",	&Instruction8BitLoad::LD_Acpa16q),	//0xFA
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"EI",			&InstructionCPUControl::ei),		//0xFB
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop),		//0xFC
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL,	"",				&InstructionCPUControl::nop),		//0xFD
		instructionFactory.createInstruction(InstructionEnum::I8BITLOGIC,	"CP d8",		&Instruction8BitLogic::CP_d8),		//0xFE
		instructionFactory.createInstruction(InstructionEnum::IJUMP,		"RST 38H",		&InstructionJump::RST_38H),			//0xFF

		//0xCB0
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RLC B",	&InstructionRotateShift::RLC_B),		//0xCB00
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RLC C",	&InstructionRotateShift::RLC_C),		//0xCB01
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RLC D",	&InstructionRotateShift::RLC_D),		//0xCB02
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RLC E",	&InstructionRotateShift::RLC_E),		//0xCB03
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RLC H",	&InstructionRotateShift::RLC_H),		//0xCB04
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RLC L",	&InstructionRotateShift::RLC_L),		//0xCB05
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RLC (HL)", &InstructionRotateShift::RLC_pHLq),		//0xCB06
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RLC A",	&InstructionRotateShift::RLC_A),		//0xCB07
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RRC B",	&InstructionRotateShift::RRC_B),		//0xCB08
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RRC C",	&InstructionRotateShift::RRC_C),		//0xCB09
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RRC D",	&InstructionRotateShift::RRC_D),		//0xCB0A
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RRC E",	&InstructionRotateShift::RRC_E),		//0xCB0B
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RRC H",	&InstructionRotateShift::RRC_H),		//0xCB0C
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RRC L",	&InstructionRotateShift::RRC_L),		//0xCB0D
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RRC (HL)",	&InstructionRotateShift::RRC_pHLq),		//0xCB0E
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RRC A",	&InstructionRotateShift::RRC_A),		//0xCB0F
		//0xCB1
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RL B",		&InstructionRotateShift::RL_B),			//0xCB10
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RL C",		&InstructionRotateShift::RL_C),			//0xCB11
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RL D",		&InstructionRotateShift::RL_D),			//0xCB12
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RL E",		&InstructionRotateShift::RL_E),			//0xCB13
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RL H",		&InstructionRotateShift::RL_H),			//0xCB14
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RL L",		&InstructionRotateShift::RL_L),			//0xCB15
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RL (HL)",	&InstructionRotateShift::RL_pHLq),		//0xCB16
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RL A",		&InstructionRotateShift::RL_A),			//0xCB17
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RR B",		&InstructionRotateShift::RR_B),			//0xCB18
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RR C",		&InstructionRotateShift::RR_C),			//0xCB19
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RR D",		&InstructionRotateShift::RR_D),			//0xCB1A
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RR E",		&InstructionRotateShift::RR_E),			//0xCB1B
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RR H",		&InstructionRotateShift::RR_H),			//0xCB1C
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RR L",		&InstructionRotateShift::RR_L),			//0xCB1D
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RR (HL)",	&InstructionRotateShift::RR_pHLq),		//0xCB1E
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "RR A",		&InstructionRotateShift::RR_A),			//0xCB1F
		//0xCB2
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SLA B",	&InstructionRotateShift::SLA_B),		//0xCB20
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SLA C",	&InstructionRotateShift::SLA_C),		//0xCB21
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SLA D",	&InstructionRotateShift::SLA_D),		//0xCB22
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SLA E",	&InstructionRotateShift::SLA_E),		//0xCB23
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SLA H",	&InstructionRotateShift::SLA_H),		//0xCB24
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SLA L",	&InstructionRotateShift::SLA_L),		//0xCB25
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SLA (HL)",	&InstructionRotateShift::SLA_pHLq),		//0xCB26
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SLA A",	&InstructionRotateShift::SLA_A),		//0xCB27
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRA B",	&InstructionRotateShift::SRA_B),		//0xCB28
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRA C",	&InstructionRotateShift::SRA_C),		//0xCB29
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRA D",	&InstructionRotateShift::SRA_D),		//0xCB2A
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRA E",	&InstructionRotateShift::SRA_E),		//0xCB2B
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRA H",	&InstructionRotateShift::SRA_H),		//0xCB2C
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRA L",	&InstructionRotateShift::SRA_L),		//0xCB2D
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRA (HL)",	&InstructionRotateShift::SRA_pHLq),		//0xCB2E
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRA A",	&InstructionRotateShift::SRA_A),		//0xCB2F
		//0xCB3
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SWAP B", &InstructionRotateShift::SWAP_B),			//0xCB30
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SWAP C", &InstructionRotateShift::SWAP_C),			//0xCB31
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SWAP D", &InstructionRotateShift::SWAP_D),			//0xCB32
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SWAP E", &InstructionRotateShift::SWAP_E),			//0xCB33
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SWAP H", &InstructionRotateShift::SWAP_H),			//0xCB34
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SWAP L", &InstructionRotateShift::SWAP_L),			//0xCB35
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SWAP (HL)", &InstructionRotateShift::SWAP_pHLq),	//0xCB36
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SWAP A", &InstructionRotateShift::SWAP_A),			//0xCB37
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRL B", &InstructionRotateShift::SRL_B),			//0xCB38
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRL C", &InstructionRotateShift::SRL_C),			//0xCB39
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRL D", &InstructionRotateShift::SRL_D),			//0xCB3A
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRL E", &InstructionRotateShift::SRL_E),			//0xCB3B
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRL H", &InstructionRotateShift::SRL_H),			//0xCB3C
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRL L", &InstructionRotateShift::SRL_L),			//0xCB3D
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRL (HL)", &InstructionRotateShift::SRL_pHLq),		//0xCB3E
		instructionFactory.createInstruction(InstructionEnum::IROTATESHIFT, "SRL A", &InstructionRotateShift::SRL_A),			//0xCB3F
		//0xCB4
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,B", &Instruction1BitOperation::BIT_0cB),		//0xCB40
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,C", &Instruction1BitOperation::BIT_0cC),		//0xCB41
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,D", &Instruction1BitOperation::BIT_0cD),		//0xCB42
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,E", &Instruction1BitOperation::BIT_0cE),		//0xCB43
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,H", &Instruction1BitOperation::BIT_0cH),		//0xCB44
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,L", &Instruction1BitOperation::BIT_0cL),		//0xCB45
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,(HL)", &Instruction1BitOperation::BIT_0cpHLq),	//0xCB46
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,A", &Instruction1BitOperation::BIT_0cA),		//0xCB47
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 1,B", &Instruction1BitOperation::BIT_1cB),		//0xCB48
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 1,C", &Instruction1BitOperation::BIT_1cC),		//0xCB49
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 1,D", &Instruction1BitOperation::BIT_1cD),		//0xCB4A
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 1,E", &Instruction1BitOperation::BIT_1cE),		//0xCB4B
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 1,H", &Instruction1BitOperation::BIT_1cH),		//0xCB4C
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 1,L", &Instruction1BitOperation::BIT_1cL),		//0xCB4D
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 1,(HL)", &Instruction1BitOperation::BIT_1cpHLq),	//0xCB4E
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 1,A", &Instruction1BitOperation::BIT_1cA),		//0xCB4F
		//0xCB5
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 2,B", &Instruction1BitOperation::BIT_2cB),		//0xCB50
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 2,C", &Instruction1BitOperation::BIT_2cC),		//0xCB51
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 2,D", &Instruction1BitOperation::BIT_2cD),		//0xCB52
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 2,E", &Instruction1BitOperation::BIT_2cE),		//0xCB53
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 2,H", &Instruction1BitOperation::BIT_2cH),		//0xCB54
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 2,L", &Instruction1BitOperation::BIT_2cL),		//0xCB55
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 2,(HL)", &Instruction1BitOperation::BIT_2cpHLq),	//0xCB56
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 2,A", &Instruction1BitOperation::BIT_2cA),		//0xCB57
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 3,B", &Instruction1BitOperation::BIT_3cB),		//0xCB58
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 3,C", &Instruction1BitOperation::BIT_3cC),		//0xCB59
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 3,D", &Instruction1BitOperation::BIT_3cD),		//0xCB5A
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 3,E", &Instruction1BitOperation::BIT_3cE),		//0xCB5B
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 3,H", &Instruction1BitOperation::BIT_3cH),		//0xCB5C
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 3,L", &Instruction1BitOperation::BIT_3cL),		//0xCB5D
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 3,(HL)", &Instruction1BitOperation::BIT_3cpHLq),	//0xCB5E
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 3,A", &Instruction1BitOperation::BIT_3cA),		//0xCB5F
		//0xCB6
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 4,B", &Instruction1BitOperation::BIT_4cB),		//0xCB60
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 4,C", &Instruction1BitOperation::BIT_4cC),		//0xCB61
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 4,D", &Instruction1BitOperation::BIT_4cD),		//0xCB62
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 4,E", &Instruction1BitOperation::BIT_4cE),		//0xCB63
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 4,H", &Instruction1BitOperation::BIT_4cH),		//0xCB64
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 4,L", &Instruction1BitOperation::BIT_4cL),		//0xCB65
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 4,(HL)", &Instruction1BitOperation::BIT_4cpHLq),	//0xCB66
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 4,A", &Instruction1BitOperation::BIT_4cA),		//0xCB67
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 5,B", &Instruction1BitOperation::BIT_5cB),		//0xCB68
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 5,C", &Instruction1BitOperation::BIT_5cC),		//0xCB69
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 5,D", &Instruction1BitOperation::BIT_5cD),		//0xCB6A
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 5,E", &Instruction1BitOperation::BIT_5cE),		//0xCB6B
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 5,H", &Instruction1BitOperation::BIT_5cH),		//0xCB6C
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 5,L", &Instruction1BitOperation::BIT_5cL),		//0xCB6D
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 5,(HL)", &Instruction1BitOperation::BIT_5cpHLq),	//0xCB6E
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 5,A", &Instruction1BitOperation::BIT_5cA),		//0xCB6F
		//0xCB7
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 6,B", &Instruction1BitOperation::BIT_6cB),		//0xCB70
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 6,C", &Instruction1BitOperation::BIT_6cC),		//0xCB71
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 6,D", &Instruction1BitOperation::BIT_6cD),		//0xCB72
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 6,E", &Instruction1BitOperation::BIT_6cE),		//0xCB73
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 6,H", &Instruction1BitOperation::BIT_6cH),		//0xCB74
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 6,L", &Instruction1BitOperation::BIT_6cL),		//0xCB75
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 6,(HL)", &Instruction1BitOperation::BIT_6cpHLq),	//0xCB76
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 6,A", &Instruction1BitOperation::BIT_6cA),		//0xCB77
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 7,B", &Instruction1BitOperation::BIT_7cB),		//0xCB78
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 7,C", &Instruction1BitOperation::BIT_7cC),		//0xCB79
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 7,D", &Instruction1BitOperation::BIT_7cD),		//0xCB7A
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 7,E", &Instruction1BitOperation::BIT_7cE),		//0xCB7B
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 7,H", &Instruction1BitOperation::BIT_7cH),		//0xCB7C
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 7,L", &Instruction1BitOperation::BIT_7cL),		//0xCB7D
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 7,(HL)", &Instruction1BitOperation::BIT_7cpHLq),	//0xCB7E
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 7,A", &Instruction1BitOperation::BIT_7cA),		//0xCB7F
		//0xCB8
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 0,B", &Instruction1BitOperation::RES_0cB),		//0xCB80
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 0,C", &Instruction1BitOperation::RES_0cC),		//0xCB81
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 0,D", &Instruction1BitOperation::RES_0cD),		//0xCB82
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 0,E", &Instruction1BitOperation::RES_0cE),		//0xCB83
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 0,H", &Instruction1BitOperation::RES_0cH),		//0xCB84
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 0,L", &Instruction1BitOperation::RES_0cL),		//0xCB85
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 0,(HL)", &Instruction1BitOperation::RES_0cpHLq),	//0xCB86
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 0,A", &Instruction1BitOperation::RES_0cA),		//0xCB87
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 1,B", &Instruction1BitOperation::RES_1cB),		//0xCB88
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 1,C", &Instruction1BitOperation::RES_1cC),		//0xCB89
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 1,D", &Instruction1BitOperation::RES_1cD),		//0xCB8A
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 1,E", &Instruction1BitOperation::RES_1cE),		//0xCB8B
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 1,H", &Instruction1BitOperation::RES_1cH),		//0xCB8C
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 1,L", &Instruction1BitOperation::RES_1cL),		//0xCB8D
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 1,(HL)", &Instruction1BitOperation::RES_1cpHLq),	//0xCB8E
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 1,A", &Instruction1BitOperation::RES_1cA),		//0xCB8F
		//0xCB9
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 2,B", &Instruction1BitOperation::RES_2cB),		//0xCB90
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 2,C", &Instruction1BitOperation::RES_2cC),		//0xCB91
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 2,D", &Instruction1BitOperation::RES_2cD),		//0xCB92
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 2,E", &Instruction1BitOperation::RES_2cE),		//0xCB93
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 2,H", &Instruction1BitOperation::RES_2cH),		//0xCB94
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 2,L", &Instruction1BitOperation::RES_2cL),		//0xCB95
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 2,(HL)", &Instruction1BitOperation::RES_2cpHLq),	//0xCB96
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 2,A", &Instruction1BitOperation::RES_2cA),		//0xCB97
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 3,B", &Instruction1BitOperation::RES_3cB),		//0xCB98
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 3,C", &Instruction1BitOperation::RES_3cC),		//0xCB99
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 3,D", &Instruction1BitOperation::RES_3cD),		//0xCB9A
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 3,E", &Instruction1BitOperation::RES_3cE),		//0xCB9B
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 3,H", &Instruction1BitOperation::RES_3cH),		//0xCB9C
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 3,L", &Instruction1BitOperation::RES_3cL),		//0xCB9D
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 3,(HL)", &Instruction1BitOperation::RES_3cpHLq),	//0xCB9E
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 3,A", &Instruction1BitOperation::RES_3cA),		//0xCB9F
		//0xCBA
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 4,B", &Instruction1BitOperation::RES_4cB),		//0xCBA0
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 4,C", &Instruction1BitOperation::RES_4cC),		//0xCBA1
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 4,D", &Instruction1BitOperation::RES_4cD),		//0xCBA2
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 4,E", &Instruction1BitOperation::RES_4cE),		//0xCBA3
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 4,H", &Instruction1BitOperation::RES_4cH),		//0xCBA4
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 4,L", &Instruction1BitOperation::RES_4cL),		//0xCBA5
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 4,(HL)", &Instruction1BitOperation::RES_4cpHLq),	//0xCBA6
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 4,A", &Instruction1BitOperation::RES_4cA),		//0xCBA7
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 5,B", &Instruction1BitOperation::RES_5cB),		//0xCBA8
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 5,C", &Instruction1BitOperation::RES_5cC),		//0xCBA9
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 5,D", &Instruction1BitOperation::RES_5cD),		//0xCBAA
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 5,E", &Instruction1BitOperation::RES_5cE),		//0xCBAB
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 5,H", &Instruction1BitOperation::RES_5cH),		//0xCBAC
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 5,L", &Instruction1BitOperation::RES_5cL),		//0xCBAD
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 5,(HL)", &Instruction1BitOperation::RES_5cpHLq),	//0xCBAE
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 5,A", &Instruction1BitOperation::RES_5cA),		//0xCBAF
		//0xCBB
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 6,B", &Instruction1BitOperation::RES_6cB),		//0xCBB0
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 6,C", &Instruction1BitOperation::RES_6cC),		//0xCBB1
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 6,D", &Instruction1BitOperation::RES_6cD),		//0xCBB2
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 6,E", &Instruction1BitOperation::RES_6cE),		//0xCBB3
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 6,H", &Instruction1BitOperation::RES_6cH),		//0xCBB4
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 6,L", &Instruction1BitOperation::RES_6cL),		//0xCBB5
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 6,(HL)", &Instruction1BitOperation::RES_6cpHLq),	//0xCBB6
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 6,A", &Instruction1BitOperation::RES_6cA),		//0xCBB7
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 7,B", &Instruction1BitOperation::RES_7cB),		//0xCBB8
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 7,C", &Instruction1BitOperation::RES_7cC),		//0xCBB9
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 7,D", &Instruction1BitOperation::RES_7cD),		//0xCBBA
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 7,E", &Instruction1BitOperation::RES_7cE),		//0xCBBB
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 7,H", &Instruction1BitOperation::RES_7cH),		//0xCBBC
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 7,L", &Instruction1BitOperation::RES_7cL),		//0xCBBD
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 7,(HL)", &Instruction1BitOperation::RES_7cpHLq),	//0xCBBE
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "RES 7,A", &Instruction1BitOperation::RES_7cA),		//0xCBBF
		//0xCBC
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 0,B", &Instruction1BitOperation::SET_0cB),		//0xCBC0
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 0,C", &Instruction1BitOperation::SET_0cC),		//0xCBC1
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 0,D", &Instruction1BitOperation::SET_0cD),		//0xCBC2
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 0,E", &Instruction1BitOperation::SET_0cE),		//0xCBC3
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 0,H", &Instruction1BitOperation::SET_0cH),		//0xCBC4
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 0,L", &Instruction1BitOperation::SET_0cL),		//0xCBC5
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 0,(HL)", &Instruction1BitOperation::SET_0cpHLq),	//0xCBC6
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 0,A", &Instruction1BitOperation::SET_0cA),		//0xCBC7
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 1,B", &Instruction1BitOperation::SET_1cB),		//0xCBC8
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 1,C", &Instruction1BitOperation::SET_1cC),		//0xCBC9
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 1,D", &Instruction1BitOperation::SET_1cD),		//0xCBCA
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 1,E", &Instruction1BitOperation::SET_1cE),		//0xCBCB
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 1,H", &Instruction1BitOperation::SET_1cH),		//0xCBCC
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 1,L", &Instruction1BitOperation::SET_1cL),		//0xCBCD
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 1,(HL)", &Instruction1BitOperation::SET_1cpHLq),	//0xCBCE
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 1,A", &Instruction1BitOperation::SET_1cA),		//0xCBCF
		//0xCBD
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 2,B", &Instruction1BitOperation::SET_2cB),		//0xCBD0
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 2,C", &Instruction1BitOperation::SET_2cC),		//0xCBD1
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 2,D", &Instruction1BitOperation::SET_2cD),		//0xCBD2
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 2,E", &Instruction1BitOperation::SET_2cE),		//0xCBD3
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 2,H", &Instruction1BitOperation::SET_2cH),		//0xCBD4
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 2,L", &Instruction1BitOperation::SET_2cL),		//0xCBD5
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 2,(HL)", &Instruction1BitOperation::SET_2cpHLq),	//0xCBD6
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 2,A", &Instruction1BitOperation::SET_2cA),		//0xCBD7
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 3,B", &Instruction1BitOperation::SET_3cB),		//0xCBD8
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 3,C", &Instruction1BitOperation::SET_3cC),		//0xCBD9
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 3,D", &Instruction1BitOperation::SET_3cD),		//0xCBDA
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 3,E", &Instruction1BitOperation::SET_3cE),		//0xCBDB
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 3,H", &Instruction1BitOperation::SET_3cH),		//0xCBDC
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 3,L", &Instruction1BitOperation::SET_3cL),		//0xCBDD
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 3,(HL)", &Instruction1BitOperation::SET_3cpHLq),	//0xCBDE
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 3,A", &Instruction1BitOperation::SET_3cA),		//0xCBDF
		//0xCBE
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 4,B", &Instruction1BitOperation::SET_4cB),		//0xCBE0
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 4,C", &Instruction1BitOperation::SET_4cC),		//0xCBE1
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 4,D", &Instruction1BitOperation::SET_4cD),		//0xCBE2
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 4,E", &Instruction1BitOperation::SET_4cE),		//0xCBE3
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 4,H", &Instruction1BitOperation::SET_4cH),		//0xCBE4
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 4,L", &Instruction1BitOperation::SET_4cL),		//0xCBE5
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 4,(HL)", &Instruction1BitOperation::SET_4cpHLq),	//0xCBE6
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 4,A", &Instruction1BitOperation::SET_4cA),		//0xCBE7
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 5,B", &Instruction1BitOperation::SET_5cB),		//0xCBE8
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 5,C", &Instruction1BitOperation::SET_5cC),		//0xCBE9
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 5,D", &Instruction1BitOperation::SET_5cD),		//0xCBEA
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 5,E", &Instruction1BitOperation::SET_5cE),		//0xCBEB
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 5,H", &Instruction1BitOperation::SET_5cH),		//0xCBEC
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 5,L", &Instruction1BitOperation::SET_5cL),		//0xCBED
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 5,(HL)", &Instruction1BitOperation::SET_5cpHLq),	//0xCBEE
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 5,A", &Instruction1BitOperation::SET_5cA),		//0xCBEF
		//0xCBF
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 6,B", &Instruction1BitOperation::SET_6cB),		//0xCBF0
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 6,C", &Instruction1BitOperation::SET_6cC),		//0xCBF1
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 6,D", &Instruction1BitOperation::SET_6cD),		//0xCBF2
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 6,E", &Instruction1BitOperation::SET_6cE),		//0xCBF3
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 6,H", &Instruction1BitOperation::SET_6cH),		//0xCBF4
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 6,L", &Instruction1BitOperation::SET_6cL),		//0xCBF5
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 6,(HL)", &Instruction1BitOperation::SET_6cpHLq),	//0xCBF6
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 6,A", &Instruction1BitOperation::SET_6cA),		//0xCBF7
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 7,B", &Instruction1BitOperation::SET_7cB),		//0xCBF8
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 7,C", &Instruction1BitOperation::SET_7cC),		//0xCBF9
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 7,D", &Instruction1BitOperation::SET_7cD),		//0xCBFA
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 7,E", &Instruction1BitOperation::SET_7cE),		//0xCBFB
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 7,H", &Instruction1BitOperation::SET_7cH),		//0xCBFC
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 7,L", &Instruction1BitOperation::SET_7cL),		//0xCBFD
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 7,(HL)", &Instruction1BitOperation::SET_7cpHLq),	//0xCBFE
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "SET 7,A", &Instruction1BitOperation::SET_7cA),		//0xCBFF
	};
}

u8 CPU::executeOpcode(const u16 opcode) 
{

	setNextOpcodesValue("");

#ifdef _DEBUG 
	//Show PC and opcode for ImGui
	mPC = readPC();
	ImGuiRenderer::setOpcodeDesc(mInstructionSet[opcode]->getName()); // TODO changer la facon de recuperer la description
#endif

	//Attente d'une interruption pour reprendre
	if (mIsCPUStopped)
	{
		// TODO Verifier l'attente lors d'un stop
		return 4;
	}

	if (opcode == 0xCB) 
		return executeOpcodeCB(0x00);
	

	u8 cycles = (mInstructionSet[opcode]->getFunctionPointer())(*this);
	incPC();

	//DEBUG JLA : adresse ou je me suis arrete
	//C7F3

	return cycles;
}

u8 CPU::executeOpcodeCB(const u16 opcodeCB) 
{
	// read opcode
	//u16 opcodeCB = 0x00;
	//TODO voir avec Merlin pour l'integration de l'instance ou trouver une autre solution
	u8 cycles = (mInstructionSet[0x100 + opcodeCB]->getFunctionPointer())(*this);
	//GBE_LOG_INFO("{0}", mInstructionSet[0x100 + opcodeCB]->getName());

	incPC();

	//return (4 + mInstructionSet[0x100 + opcodeCB]->getClockCycle());
	return 4 + cycles; // TODO check with Merlin
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
	u16 address = (*registries.highRegistry << 8) + *registries.lowRegistry;
	mBus->write(address, value);
}

u8 CPU::getOpcode()
{
	//return mBus->read(readPC());
	const u16* PC = getPC();
	//TODO
	return mBus->read(*PC);
}

u8 CPU::getNextOpcodePreview() const
{
	auto pc = readPC();
	return mBus->read(++pc);
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
	u16 address = (*registries.highRegistry << 8) + *registries.lowRegistry;
	u8 value = mBus->read(address);
	return value;
}

u8* CPU::getMemoryDataPtr(const combinedRegistries& registries)
{
	u16 address = (*registries.highRegistry << 8) + *registries.lowRegistry;
	u8* value = mBus->getDataPtr(address);
	return value;
}

u8* CPU::getMemoryDataPtr(const u16& address)
{
	u8* value = mBus->getDataPtr(address);
	return value;
}

void CPU::setIMEFlag()
{
	mRegistries.setIME();
}

void CPU::clearIMEFlag()
{
	mRegistries.clearIME();
}

u8 CPU::getIMEFlag() const
{
	return mRegistries.getIME();
}


std::pair<interrupt_flag, interrupt_flag> CPU::getInterruptFlags() const
{
	interrupt_flag IE, IF;
	IE = mBus->getInterruptEnable();
	IF = mBus->getInterruptFlag();

	return std::make_pair(IE, IF);
}

void CPU::setInterruptFlag(const u8 flags)
{
	mBus->setInterruptFlag(flags);
}

void CPU::setInterruptEnable(const u8 flags)
{
	mBus->setInterruptEnable(flags);
}

std::shared_ptr<BootRom> CPU::getBootRom()
{
	return mBootRom;
}

std::shared_ptr<InterruptsManager> CPU::getInterruptsManager()
{
	return mInterruptsManager;
}

void CPU::createInternalComponents(std::weak_ptr<CPU> cpu_weak)
{
	mInterruptsManager  = std::make_shared<InterruptsManager>();
	InterruptsManager::setCPU(cpu_weak);
	mBootRom = std::make_shared<BootRom>(mBus, mPPU, cpu_weak);
}

void CPU::stopCPU()
{
	mIsCPUStopped = true;
}

void CPU::resumeCPUFromInterrupt()
{
	mIsCPUStopped = false;
}

void CPU::resetMemory()
{
	mBus->reset();
}

void CPU::logRegistries()
{
	auto F = getFlagRegistry();
	auto C = F->flags.C;
	auto H = F->flags.H;
	auto N = F->flags.N;
	auto Z = F->flags.Z;

	GBE_LOG_INFO("Registry A : {:#x}", *getRegistries("A"));
	GBE_LOG_INFO("Registry B : {:#x}", *getRegistries("B"));
	GBE_LOG_INFO("Registry C : {:#x}", *getRegistries("C"));
	GBE_LOG_INFO("Registry D : {:#x}", *getRegistries("D"));
	GBE_LOG_INFO("Registry E : {:#x}", *getRegistries("E"));
	GBE_LOG_INFO("Registry H : {:#x}", *getRegistries("H"));
	GBE_LOG_INFO("Registry L : {:#x}", *getRegistries("L"));
	GBE_LOG_INFO("Registry F : {:#x}", F->F);
	GBE_LOG_INFO("Registry F.C : {:#x}", C);
	GBE_LOG_INFO("Registry F.H : {:#x}", H);
	GBE_LOG_INFO("Registry F.N : {:#x}", N);
	GBE_LOG_INFO("Registry F.Z : {:#x}", Z);
	GBE_LOG_INFO("Registry SP : {:#x}", *getSP());
	GBE_LOG_INFO("LY : {:#x}", mBus->read(0xFF44));
	

}

void CPU::logOpcodesInfos(u8 opcode)
{
	GBE_LOG_INFO("\n##########################################");
	GBE_LOG_INFO("{0}", mInstructionSet[opcode]->getName());
	GBE_LOG_INFO("PC : {:#x}", *getPC());
	GBE_LOG_INFO("Opcode  : {:#x}", opcode);


}

