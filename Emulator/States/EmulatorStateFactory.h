#pragma once

#include <memory>

#include "IEmulatorState.h"
#include "InitState.h"
#include "BootState.h"
#include "BootRom/BootRom.h"

class EmulatorStateFactory
{
private:
	std::shared_ptr<BootRom> mBootRom;

public:
	EmulatorStateFactory(std::shared_ptr<BootRom> bootRom)
		:mBootRom(bootRom)
	{}

	std::unique_ptr<class IEmulatorState> createState(EmulatorState stateType)
	{
		switch (stateType)
		{
			case EmulatorState::INIT:
				return std::make_unique<EmulatorInitState>();
			case EmulatorState::BOOT:
				return std::make_unique<EmulatorBootState>(mBootRom);
		
		}

	}
};