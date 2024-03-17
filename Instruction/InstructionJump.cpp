#include "InstructionJump.h"

/// Private methods
//TODO voir avec Merlin pour l'integration de l'instance ou trouver une autre solution
//void InstructionJump::JP_CCca16(CPU& cpu, Instruction& instance, const u8& flagCondition)
void InstructionJump::JP_CCca16(CPU& cpu, const u8& flag)
{
	u16* PC = cpu.getPC();
	u16 adress = readNextTwoOpcodes(cpu);

	
	if (flag)
	{
		*PC = adress;;
		//setClockCycle(instance, 16);
	}
	//else
		//setClockCycle(instance, 12);
}

void InstructionJump::JR_CCca16(CPU& cpu, const u8& flag)
{
	u16* PC = cpu.getPC();
	int8_t offset = static_cast<int8_t>(readNextOpcode(cpu));

	if (flag)
	{
		*PC += offset;
		//setClockCycle(instance, 12);
	}
	//else
		//setClockCycle(instance, 8);
}

void InstructionJump::RET_CC(CPU& cpu, const u8& flag)
{

	if (flag)
	{
		RET(cpu);
		//setClockCycle(instance, 20);
	}
	//else
		//setClockCycle(instance, 8);
}

void InstructionJump::CALL_CC(CPU& cpu, const u8& flag)
{
	
	u16 address = readNextTwoOpcodes(cpu);

	if (flag)
	{
		u16* PC = cpu.getPC();
		PUSH_PC(cpu);
		*PC = address;
		//setClockCycle(instance, 24);
	}
	//else
		//setClockCycle(instance, 12);
}

void InstructionJump::RST_VC(CPU& cpu, const u16& address)
{
	u16* PC = cpu.getPC();
	PUSH_PC(cpu);

	*PC = address;
}

void InstructionJump::PUSH_PC(CPU& cpu)
{
	u16* SP = cpu.getSP();
	u16* PC = cpu.getPC();

	u8 lowPC = *PC & 0x00FF;
	u8 highPC = (*PC & 0xFF00) >> 8;
	*SP -= 1;
	cpu.writeMemory(*SP, highPC);
	*SP -= 1;
	cpu.writeMemory(*SP, lowPC);
}


// Public methods
InstructionJump::InstructionJump(std::string const & name, void (*pInstruction)(CPU & cpu), u8 ClockCycle)
{
	mName = name;
	pmInstruction = pInstruction;
	mClockCycle = ClockCycle;
}

void InstructionJump::JR_r8(CPU& cpu)
{
	u16* PC = cpu.getPC();
	int8_t offset = static_cast<int8_t>(readNextOpcode(cpu));

	*PC += offset;
}

void InstructionJump::JR_NZcr8(CPU& cpu)
{
	flags* f = cpu.getFlagRegistry();
	JR_CCca16(cpu, !f->flags.Z);
}

void InstructionJump::JR_Zcr8(CPU& cpu)
{
	flags* f = cpu.getFlagRegistry();
	JR_CCca16(cpu, f->flags.Z);
}

void InstructionJump::JR_NCcr8(CPU& cpu)
{
	flags* f = cpu.getFlagRegistry();
	JR_CCca16(cpu, !f->flags.C);
}

void InstructionJump::JR_Ccr8(CPU& cpu)
{
	flags* f = cpu.getFlagRegistry();
	JR_CCca16(cpu, f->flags.C);
}

void InstructionJump::RET_NZ(CPU& cpu)
{
	flags* f = cpu.getFlagRegistry();
	RET_CC(cpu, !f->flags.Z);
}

void InstructionJump::JP_NZca16(CPU& cpu)
{
	flags* f = cpu.getFlagRegistry();
	JP_CCca16(cpu, !f->flags.Z);
}

//TODO Verifier cette instruction
void InstructionJump::JP_a16(CPU& cpu)
{
	u16* PC = cpu.getPC();
	u16 adress = readNextTwoOpcodes(cpu);

	*PC = adress;
}

void InstructionJump::CALL_NZca16(CPU& cpu)
{
	flags* f = cpu.getFlagRegistry();
	CALL_CC(cpu, !f->flags.Z);
}

void InstructionJump::RST_00H(CPU& cpu)
{
	RST_VC(cpu, 0x0000);
}

void InstructionJump::RET_Z(CPU& cpu)
{
	flags* f = cpu.getFlagRegistry();
	RET_CC(cpu, f->flags.Z);
}

void InstructionJump::RET(CPU& cpu)
{
	u16* SP = cpu.getSP();
	u16* PC = cpu.getPC();

	u8 lowPC = cpu.readMemory(*SP);
	*SP += 1;
	u8 highPC = cpu.readMemory(*SP);
	*SP += 1;

	*PC = ((highPC << 8) & 0xFF00) | (lowPC & 0x00FF);
}

void InstructionJump::JP_Zca16(CPU& cpu)
{
	flags* f = cpu.getFlagRegistry();
	JP_CCca16(cpu, f->flags.Z);
}

void InstructionJump::CALL_Zca16(CPU& cpu)
{
	flags* f = cpu.getFlagRegistry();
	CALL_CC(cpu, f->flags.Z);
}

void InstructionJump::CALL_a16(CPU& cpu)
{
	u16* PC = cpu.getPC();
	u16 address = readNextTwoOpcodes(cpu);

	PUSH_PC(cpu);

	*PC = address;
}

void InstructionJump::RST_08H(CPU& cpu)
{
	RST_VC(cpu, 0x0800);
}

void InstructionJump::RET_NC(CPU& cpu)
{
	flags* f = cpu.getFlagRegistry();
	RET_CC(cpu, !f->flags.C);
}

void InstructionJump::JP_NCca16(CPU& cpu)
{
	flags* f = cpu.getFlagRegistry();
	JP_CCca16(cpu, !f->flags.C);
}

void InstructionJump::CALL_NCca16(CPU& cpu)
{
	flags* f = cpu.getFlagRegistry();
	CALL_CC(cpu, !f->flags.C);
}

void InstructionJump::RST_10H(CPU& cpu)
{
	RST_VC(cpu, 0x1000);
}

void InstructionJump::RET_C(CPU& cpu)
{
	flags* f = cpu.getFlagRegistry();
	RET_CC(cpu, f->flags.C);
}

void InstructionJump::RETI(CPU& cpu)
{
	cpu.setIMEFlag();
	RET(cpu);
}

//TODO voir avec Merlin pour l'integration de l'instance ou trouver une autre solution
//void InstructionJump::JP_Cca16(CPU& cpu, Instruction& instance)
void InstructionJump::JP_Cca16(CPU& cpu)
{
	flags* f = cpu.getFlagRegistry();
	//JP_CCca16(cpu, instance, f->flags.C);
	JP_CCca16(cpu, f->flags.C);
	
}

void InstructionJump::CALL_Cca16(CPU& cpu)
{
	flags* f = cpu.getFlagRegistry();
	CALL_CC(cpu, f->flags.C);
}

void InstructionJump::RST_18H(CPU& cpu)
{
	RST_VC(cpu, 0x1800);
}

void InstructionJump::RST_20H(CPU& cpu)
{
}

// TODO Verifier que c'est bien la valeur de HL qui est stockee, et non la valeur à l'adresse HL
void InstructionJump::JP_pHLq(CPU& cpu)
{
	u16* PC = cpu.getPC();
	combinedRegistries* HL = cpu.getCombinedRegistries("HL");

	*PC = HL->getValue();

}

void InstructionJump::RST_28H(CPU& cpu)
{
	RST_VC(cpu, 0x2800);
}

void InstructionJump::RST_30H(CPU& cpu)
{
	RST_VC(cpu, 0x3000);
}

void InstructionJump::RST_38H(CPU& cpu)
{
	RST_VC(cpu, 0x3800);
}


