#include "Instruction1BitOperation.h"

Instruction1BitOperation::Instruction1BitOperation(std::string const& name, void (*pInstruction)(CPU & cpu), u8 ClockCycle)
{
	mName = name;
	pmInstruction = pInstruction;
	mClockCycle = ClockCycle;
}

// Instructions test bit
// TODO : refactor ?
void Instruction1BitOperation::BIT_0cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x00, cpu);
}

void Instruction1BitOperation::BIT_0cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x00, cpu);
}

void Instruction1BitOperation::BIT_0cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x00, cpu);
}

void Instruction1BitOperation::BIT_0cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x00, cpu);
}

void Instruction1BitOperation::BIT_0cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x00, cpu);
}

void Instruction1BitOperation::BIT_0cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x00, cpu);
}

void Instruction1BitOperation::BIT_0cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	BIT_bcr(*registry, *flagRegistry, 0x00, cpu);
}

void Instruction1BitOperation::BIT_0cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x00, cpu);
}

void Instruction1BitOperation::BIT_1cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x01, cpu);
}

void Instruction1BitOperation::BIT_1cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x01, cpu);
}

void Instruction1BitOperation::BIT_1cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x01, cpu);
}

void Instruction1BitOperation::BIT_1cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x01, cpu);
}

void Instruction1BitOperation::BIT_1cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x01, cpu);
}

void Instruction1BitOperation::BIT_1cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x01, cpu);
}

void Instruction1BitOperation::BIT_1cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	BIT_bcr(*registry, *flagRegistry, 0x01, cpu);
}

void Instruction1BitOperation::BIT_1cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x01, cpu);
}

void Instruction1BitOperation::BIT_2cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x02, cpu);
}

void Instruction1BitOperation::BIT_2cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x02, cpu);
}

void Instruction1BitOperation::BIT_2cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x02, cpu);
}

void Instruction1BitOperation::BIT_2cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x02, cpu);
}

void Instruction1BitOperation::BIT_2cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x02, cpu);
}

void Instruction1BitOperation::BIT_2cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x02, cpu);
}

void Instruction1BitOperation::BIT_2cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	BIT_bcr(*registry, *flagRegistry, 0x02, cpu);
}

void Instruction1BitOperation::BIT_2cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x02, cpu);
}

void Instruction1BitOperation::BIT_3cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x03, cpu);
}

void Instruction1BitOperation::BIT_3cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x03, cpu);
}

void Instruction1BitOperation::BIT_3cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x03, cpu);
}

void Instruction1BitOperation::BIT_3cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x03, cpu);
}

void Instruction1BitOperation::BIT_3cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x03, cpu);
}

void Instruction1BitOperation::BIT_3cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x03, cpu);
}

void Instruction1BitOperation::BIT_3cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	BIT_bcr(*registry, *flagRegistry, 0x03, cpu);
}

void Instruction1BitOperation::BIT_3cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x03, cpu);
}

void Instruction1BitOperation::BIT_4cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x04, cpu);
}

void Instruction1BitOperation::BIT_4cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x04, cpu);
}

void Instruction1BitOperation::BIT_4cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x04, cpu);
}

void Instruction1BitOperation::BIT_4cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x04, cpu);
}

void Instruction1BitOperation::BIT_4cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x04, cpu);
}

void Instruction1BitOperation::BIT_4cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x04, cpu);
}

void Instruction1BitOperation::BIT_4cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	BIT_bcr(*registry, *flagRegistry, 0x04, cpu);
}

void Instruction1BitOperation::BIT_4cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x04, cpu);
}

void Instruction1BitOperation::BIT_5cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x05, cpu);
}

void Instruction1BitOperation::BIT_5cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x05, cpu);
}

void Instruction1BitOperation::BIT_5cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x05, cpu);
}

void Instruction1BitOperation::BIT_5cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x05, cpu);
}

void Instruction1BitOperation::BIT_5cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x05, cpu);
}

void Instruction1BitOperation::BIT_5cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x05, cpu);
}

void Instruction1BitOperation::BIT_5cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	BIT_bcr(*registry, *flagRegistry, 0x05, cpu);
}

void Instruction1BitOperation::BIT_5cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x05, cpu);
}

void Instruction1BitOperation::BIT_6cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x06, cpu);
}

void Instruction1BitOperation::BIT_6cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x06, cpu);
}

void Instruction1BitOperation::BIT_6cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x06, cpu);
}

void Instruction1BitOperation::BIT_6cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x06, cpu);
}

void Instruction1BitOperation::BIT_6cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x06, cpu);
}

void Instruction1BitOperation::BIT_6cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x06, cpu);
}

void Instruction1BitOperation::BIT_6cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	BIT_bcr(*registry, *flagRegistry, 0x06, cpu);
}

void Instruction1BitOperation::BIT_6cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x06, cpu);
}

void Instruction1BitOperation::BIT_7cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x07, cpu);
}

void Instruction1BitOperation::BIT_7cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x07, cpu);
}

void Instruction1BitOperation::BIT_7cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x07, cpu);
}

void Instruction1BitOperation::BIT_7cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x07, cpu);
}

void Instruction1BitOperation::BIT_7cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x07, cpu);
}

void Instruction1BitOperation::BIT_7cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x07, cpu);
}

void Instruction1BitOperation::BIT_7cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	BIT_bcr(*registry, *flagRegistry, 0x07, cpu);
}

void Instruction1BitOperation::BIT_7cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	BIT_bcr(*registry, *flagRegistry, 0x07, cpu);
}

// Instructions reset bit
// TODO : refactor ?
void Instruction1BitOperation::RES_0cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x00);
}

void Instruction1BitOperation::RES_0cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x00);
}

void Instruction1BitOperation::RES_0cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x00);
}

void Instruction1BitOperation::RES_0cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x00);
}

void Instruction1BitOperation::RES_0cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x00);
}

void Instruction1BitOperation::RES_0cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x00);
}

void Instruction1BitOperation::RES_0cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	RES_bcpHLq(*registry, *flagRegistry, 0x00, cpu);
}

void Instruction1BitOperation::RES_0cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x00);
}

void Instruction1BitOperation::RES_1cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x01);
}

void Instruction1BitOperation::RES_1cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x01);
}

void Instruction1BitOperation::RES_1cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x01);
}

void Instruction1BitOperation::RES_1cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x01);
}

void Instruction1BitOperation::RES_1cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x01);
}

void Instruction1BitOperation::RES_1cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x01);
}

void Instruction1BitOperation::RES_1cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	RES_bcpHLq(*registry, *flagRegistry, 0x01, cpu);
}

void Instruction1BitOperation::RES_1cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x01);
}

void Instruction1BitOperation::RES_2cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x02);
}

void Instruction1BitOperation::RES_2cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x02);
}

void Instruction1BitOperation::RES_2cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x02);
}

void Instruction1BitOperation::RES_2cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x02);
}

void Instruction1BitOperation::RES_2cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x02);
}

void Instruction1BitOperation::RES_2cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x02);
}

void Instruction1BitOperation::RES_2cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	RES_bcpHLq(*registry, *flagRegistry, 0x02, cpu);
}

void Instruction1BitOperation::RES_2cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x02);
}

void Instruction1BitOperation::RES_3cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x03);
}

void Instruction1BitOperation::RES_3cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x03);
}

void Instruction1BitOperation::RES_3cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x03);
}

void Instruction1BitOperation::RES_3cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x03);
}

void Instruction1BitOperation::RES_3cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x03);
}

void Instruction1BitOperation::RES_3cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x03);
}

void Instruction1BitOperation::RES_3cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	RES_bcpHLq(*registry, *flagRegistry, 0x03, cpu);
}

void Instruction1BitOperation::RES_3cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x03);
}

void Instruction1BitOperation::RES_4cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x04);
}

void Instruction1BitOperation::RES_4cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x04);
}

void Instruction1BitOperation::RES_4cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x04);
}

void Instruction1BitOperation::RES_4cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x04);
}

void Instruction1BitOperation::RES_4cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x04);
}

void Instruction1BitOperation::RES_4cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x04);
}

void Instruction1BitOperation::RES_4cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	RES_bcpHLq(*registry, *flagRegistry, 0x04, cpu);

}

void Instruction1BitOperation::RES_4cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x04);
}

void Instruction1BitOperation::RES_5cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x05);
}

void Instruction1BitOperation::RES_5cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x05);
}

void Instruction1BitOperation::RES_5cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x05);
}

void Instruction1BitOperation::RES_5cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x05);
}

void Instruction1BitOperation::RES_5cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x05);
}

void Instruction1BitOperation::RES_5cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x05);
}

void Instruction1BitOperation::RES_5cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	RES_bcpHLq(*registry, *flagRegistry, 0x05, cpu);
}

void Instruction1BitOperation::RES_5cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x05);
}

void Instruction1BitOperation::RES_6cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x06);
}

void Instruction1BitOperation::RES_6cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x06);
}

void Instruction1BitOperation::RES_6cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x06);
}

void Instruction1BitOperation::RES_6cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x06);
}

void Instruction1BitOperation::RES_6cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x06);
}

void Instruction1BitOperation::RES_6cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x06);
}

void Instruction1BitOperation::RES_6cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	RES_bcpHLq(*registry, *flagRegistry, 0x06, cpu);
}

void Instruction1BitOperation::RES_6cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x06);
}

void Instruction1BitOperation::RES_7cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x07);
}

void Instruction1BitOperation::RES_7cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x07);
}

void Instruction1BitOperation::RES_7cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x07);
}

void Instruction1BitOperation::RES_7cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x07);
}

void Instruction1BitOperation::RES_7cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x07);
}

void Instruction1BitOperation::RES_7cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x07);
}

void Instruction1BitOperation::RES_7cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	RES_bcpHLq(*registry, *flagRegistry, 0x07, cpu);
}

void Instruction1BitOperation::RES_7cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	RES_bcr(*registry, *flagRegistry, 0x07);
}

// Instructions set bit
// TODO : refactor ?
void Instruction1BitOperation::SET_0cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x00);
}

void Instruction1BitOperation::SET_0cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x00);
}

void Instruction1BitOperation::SET_0cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x00);
}

void Instruction1BitOperation::SET_0cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x00);
}

void Instruction1BitOperation::SET_0cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x00);
}

void Instruction1BitOperation::SET_0cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x00);
}

void Instruction1BitOperation::SET_0cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	SET_bcpHLq(*registry, *flagRegistry, 0x00, cpu);
}

void Instruction1BitOperation::SET_0cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x00);
}

void Instruction1BitOperation::SET_1cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x01);
}

void Instruction1BitOperation::SET_1cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x01);
}

void Instruction1BitOperation::SET_1cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x01);
}

void Instruction1BitOperation::SET_1cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x01);
}

void Instruction1BitOperation::SET_1cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x01);
}

void Instruction1BitOperation::SET_1cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x01);
}

void Instruction1BitOperation::SET_1cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	SET_bcpHLq(*registry, *flagRegistry, 0x01, cpu);
}

void Instruction1BitOperation::SET_1cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x01);
}

void Instruction1BitOperation::SET_2cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x02);
}

void Instruction1BitOperation::SET_2cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x02);
}

void Instruction1BitOperation::SET_2cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x02);
}

void Instruction1BitOperation::SET_2cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x02);
}

void Instruction1BitOperation::SET_2cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x02);
}

void Instruction1BitOperation::SET_2cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x02);
}

void Instruction1BitOperation::SET_2cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	SET_bcpHLq(*registry, *flagRegistry, 0x02, cpu);
}

void Instruction1BitOperation::SET_2cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x02);
}

void Instruction1BitOperation::SET_3cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x03);
}

void Instruction1BitOperation::SET_3cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x03);
}

void Instruction1BitOperation::SET_3cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x03);
}

void Instruction1BitOperation::SET_3cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x03);
}

void Instruction1BitOperation::SET_3cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x03);
}

void Instruction1BitOperation::SET_3cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x03);
}

void Instruction1BitOperation::SET_3cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	SET_bcpHLq(*registry, *flagRegistry, 0x03, cpu);
}

void Instruction1BitOperation::SET_3cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x03);
}

void Instruction1BitOperation::SET_4cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x04);
}

void Instruction1BitOperation::SET_4cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x04);
}

void Instruction1BitOperation::SET_4cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x04);
}

void Instruction1BitOperation::SET_4cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x04);
}

void Instruction1BitOperation::SET_4cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x04);
}

void Instruction1BitOperation::SET_4cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x04);
}

void Instruction1BitOperation::SET_4cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	SET_bcpHLq(*registry, *flagRegistry, 0x04, cpu);
}

void Instruction1BitOperation::SET_4cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x04);
}

void Instruction1BitOperation::SET_5cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x05);
}

void Instruction1BitOperation::SET_5cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x05);
}

void Instruction1BitOperation::SET_5cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x05);
}

void Instruction1BitOperation::SET_5cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x05);
}

void Instruction1BitOperation::SET_5cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x05);
}

void Instruction1BitOperation::SET_5cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x05);
}

void Instruction1BitOperation::SET_5cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	SET_bcpHLq(*registry, *flagRegistry, 0x05, cpu);
}

void Instruction1BitOperation::SET_5cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x05);
}

void Instruction1BitOperation::SET_6cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x06);
}

void Instruction1BitOperation::SET_6cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x06);
}

void Instruction1BitOperation::SET_6cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x06);
}

void Instruction1BitOperation::SET_6cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x06);
}

void Instruction1BitOperation::SET_6cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x06);
}

void Instruction1BitOperation::SET_6cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x06);
}

void Instruction1BitOperation::SET_6cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	SET_bcpHLq(*registry, *flagRegistry, 0x06, cpu);
}

void Instruction1BitOperation::SET_6cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x06);
}

void Instruction1BitOperation::SET_7cB(CPU& cpu)
{
	u8* registry = cpu.getRegistries("B");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x07);
}

void Instruction1BitOperation::SET_7cC(CPU& cpu)
{
	u8* registry = cpu.getRegistries("C");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x07);
}

void Instruction1BitOperation::SET_7cD(CPU& cpu)
{
	u8* registry = cpu.getRegistries("D");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x07);
}

void Instruction1BitOperation::SET_7cE(CPU& cpu)
{
	u8* registry = cpu.getRegistries("E");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x07);
}

void Instruction1BitOperation::SET_7cH(CPU& cpu)
{
	u8* registry = cpu.getRegistries("H");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x07);
}

void Instruction1BitOperation::SET_7cL(CPU& cpu)
{
	u8* registry = cpu.getRegistries("L");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x07);
}

void Instruction1BitOperation::SET_7cpHLq(CPU& cpu)
{
	flags* flagRegistry = cpu.getFlagRegistry();
	u8* registry = cpu.getMemoryDataPtr(*cpu.getCombinedRegistries("HL"));
	SET_bcpHLq(*registry, *flagRegistry, 0x07, cpu);
}

void Instruction1BitOperation::SET_7cA(CPU& cpu)
{
	u8* registry = cpu.getRegistries("A");
	flags* flagRegistry = cpu.getFlagRegistry();
	SET_bcr(*registry, *flagRegistry, 0x07);
}

void Instruction1BitOperation::BIT_bcr(u8& registry, flags& flagRegistry, u8 bit, CPU& cpu)
{
	setZFlag(cpu, getBit(registry, bit));
	setHFlag(cpu, 1);
	setNFlag(cpu, 0);
}

void Instruction1BitOperation::RES_bcr(u8& registry, flags& flagRegistry, u8 bit)
{
	setBit(registry, bit, 0x00);
}

void Instruction1BitOperation::RES_bcpHLq(u8& registry, flags& flagRegistry, u8 bit, CPU& cpu)
{
	setBit(registry, bit, 0x00);
	cpu.writeMemory(*cpu.getCombinedRegistries("HL"), registry);
}

void Instruction1BitOperation::SET_bcr(u8& registry, flags& flagRegistry, u8 bit)
{
	setBit(registry, bit, 0x01);
}

void Instruction1BitOperation::SET_bcpHLq(u8& registry, flags& flagRegistry, u8 bit, CPU& cpu)
{
	setBit(registry, bit, 0x01);
	cpu.writeMemory(*cpu.getCombinedRegistries("HL"), registry);
}