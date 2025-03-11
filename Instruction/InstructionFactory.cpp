#include "pch.h"

#include "InstructionFactory.h"
#include "Bus/Bus.h"
#include "Registries/Registries.h"

InstructionFactory::InstructionFactory(Registries& registries, std::shared_ptr<Bus> bus)
	:mRegistriesRef(registries), mBusRef(bus)
{
}



Instruction* InstructionFactory::createInstruction(InstructionEnum instructionEnum, const char* name, std::function<u8(CPU& cpu)> instruction) const
{
	switch (instructionEnum)
	{
	case InstructionEnum::I1BITOPERATION:	return new Instruction1BitOperation(name, instruction, mRegistriesRef, mBusRef); break;
	case InstructionEnum::I8BITLOAD:		return new Instruction8BitLoad(name, instruction, mRegistriesRef, mBusRef);		 break;
	case InstructionEnum::I8BITLOGIC:		return new Instruction8BitLogic(name, instruction, mRegistriesRef, mBusRef);     break;
	case InstructionEnum::I16BITLOAD:		return new Instruction16BitLoad(name, instruction, mRegistriesRef, mBusRef);     break;
	case InstructionEnum::I16BITLOGIC:		return new Instruction16BitLogic(name, instruction, mRegistriesRef, mBusRef);    break;
	case InstructionEnum::ICPUCONTROL:		return new InstructionCPUControl(name, instruction, mRegistriesRef, mBusRef);    break;
	case InstructionEnum::IJUMP:			return new InstructionJump(name, instruction, mRegistriesRef, mBusRef);          break;
	case InstructionEnum::IROTATESHIFT:		return new InstructionRotateShift(name, instruction, mRegistriesRef, mBusRef);   break;
	}
}
