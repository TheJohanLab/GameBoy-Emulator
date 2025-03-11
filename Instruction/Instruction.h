#pragma once
//#include <string>
//#include "Utils/Utils.h"
#include "Utils/Log.h"

class CPU;
class Registries;
class Bus;

class Instruction
{
protected:
	const char* mName;

	std::function<u8(CPU& cpu)> mInstruction;


	static u8 readNextOpcode(CPU& cpu);
	static u16 readNextTwoOpcodes(CPU& cpu);
	static u8 getBit(u8 byte, u8 pos) { return (byte >> pos) & 0x01; }
	static void setBit(u8& byte, u8 pos, u8 val) { byte = (byte & ~(0x01 << pos) | (val << pos)); }
	
	static void updateHFlag(CPU& cpu, u8 byte, bool substract);
	static void setHFlag(CPU& cpu, u8 registry, u8 addValue, bool substract);
	static void setHFlag(CPU& cpu, u8 value);
	static void setZFlag(CPU& cpu, u8 value);
	static void setNFlag(CPU& cpu, u8 value);
	static void setCFlag(CPU& cpu, const u8& baseValue, const u8& additionnalValue, bool substract = false);
	static void setCFlag(CPU& cpu, u8 value);
	
	static void clearFlag(CPU& cpu, const char& flag);
	static void setFlags(CPU& cpu, const u8& flags);
	static bool isHalfOverflow(const u8& baseValue, const u8& additionalValue, bool substract = false);
	static bool isHalfOverflow(const u16& baseValue, const u16& additionalValue, bool substract = false);
	static bool isOverflow(const u8& baseValue, const u8& additionalValue, bool substract = false);
	static bool isOverflow(const u16& baseValue, const u16& additionalValue, bool substract = false);

	static void setClockCycle(Instruction& instance, const u8& clockCycle);

	//New approch
	std::vector<std::reference_wrapper<uint8_t>>& mRegistries; 
	uint16_t& mPC;
	uint16_t& mSP;
	uint16_t& mBC;
	uint16_t& mDE;
	uint16_t& mHL;
	uint16_t& mAF;
	std::shared_ptr<Bus> mBus;

public:
	//Instruction();
	//Instruction(const char* name, u8(*pInstruction)(CPU& cpu), u8 clockCycles);
	Instruction(const char* name, std::function<u8(CPU& cpu)> instruction, Registries&, std::shared_ptr<Bus>);
	virtual ~Instruction() = default;

	std::string getName() const { return mName; }
	//auto getFunctionPointer() const { return pmInstruction; }
	//New approch
	auto getFunctionPointer() const { return mInstruction; }
};

