#include "pch.h"

#include "InstructionFactory.h"
#include "Bus/Bus.h"
#include "Registries/Registries.h"

InstructionFactory::InstructionFactory(Registries& registries, std::shared_ptr<Bus> bus)
	:mRegistriesRef(registries), mBusRef(bus)
{
}



std::unique_ptr<Instruction> InstructionFactory::createInstruction(InstructionEnum instructionEnum, const char* name, std::function<u8(CPU& cpu)> instruction) const
{
	switch (instructionEnum)
	{
	case InstructionEnum::I1BITOPERATION:	return std::make_unique<Instruction1BitOperation>(name, instruction, mRegistriesRef, mBusRef); break;
	case InstructionEnum::I8BITLOAD:		return std::make_unique<Instruction8BitLoad>(name, instruction, mRegistriesRef, mBusRef);	   break;
	case InstructionEnum::I8BITLOGIC:		return std::make_unique<Instruction8BitLogic>(name, instruction, mRegistriesRef, mBusRef);     break;
	case InstructionEnum::I16BITLOAD:		return std::make_unique<Instruction16BitLoad>(name, instruction, mRegistriesRef, mBusRef);     break;
	case InstructionEnum::I16BITLOGIC:		return std::make_unique<Instruction16BitLogic>(name, instruction, mRegistriesRef, mBusRef);    break;
	case InstructionEnum::ICPUCONTROL:		return std::make_unique<InstructionCPUControl>(name, instruction, mRegistriesRef, mBusRef);    break;
	case InstructionEnum::IJUMP:			return std::make_unique<InstructionJump>(name, instruction, mRegistriesRef, mBusRef);          break;
	case InstructionEnum::IROTATESHIFT:		return std::make_unique<InstructionRotateShift>(name, instruction, mRegistriesRef, mBusRef);   break;
	}
}
