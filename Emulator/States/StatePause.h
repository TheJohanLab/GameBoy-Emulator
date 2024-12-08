#pragma once

#include <memory>

#include "EmulatorBaseState.h"
#include "BootRom/BootRom.h"

class EmulatorPauseState : public EmulatorBaseState
{
private:

public:


	void execute() override
	{
		//mHandleBootFrameCallback();
		//mBootRom->execute();
	}
};