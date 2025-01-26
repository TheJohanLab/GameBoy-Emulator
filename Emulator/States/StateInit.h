#pragma once

#include "EmulatorBaseState.h"
//#include "Utils/Log.h"

#include "BootRom/BootRom.h"

class EmulatorInitState : public EmulatorBaseState
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

		mDrawCallback();
	}
};


