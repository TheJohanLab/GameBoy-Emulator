#pragma once

#include <memory>

#include "IEmulatorState.h"
#include "BootRom/BootRom.h"

class EmulatorBootState : public IEmulatorState
{
private:
	std::shared_ptr<BootRom> mBootRom;

public:
	EmulatorBootState(std::shared_ptr<BootRom> bootRom)
		:mBootRom(bootRom)
	{}

	void execute() override
	{
		mBootRom->execute();
	}
};