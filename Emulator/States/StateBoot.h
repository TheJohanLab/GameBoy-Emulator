#pragma once

//#include <memory>

#include "EmulatorBaseState.h"
#include "BootRom/BootRom.h"

class EmulatorBootState : public EmulatorBaseState
{
private:
	std::shared_ptr<BootRom> mBootRom;

public:
	EmulatorBootState(std::shared_ptr<BootRom> bootRom)
		:mBootRom(bootRom)
	{
		bootRom->initializeBootRom();
	}

	void execute() override
	{
		mHandleBootFrameCallback();
		mBootRom->execute();
	}
};