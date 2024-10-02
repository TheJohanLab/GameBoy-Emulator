#pragma once

#include "IEmulatorState.h"
#include "Utils/Log.h"

#include "BootRom/BootRom.h"

class EmulatorInitState : public IEmulatorState
{
private:
	bool mIsEmulatorInitialized{ false };
public:
	void execute() override
	{
		if (!mIsEmulatorInitialized)
		{
			GBE_LOG_INFO("Select 'file/load' to load a rom file");
			mIsEmulatorInitialized = true;
		}
	}
};


