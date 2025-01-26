#pragma once

#include "EmulatorBaseState.h"
//#include "Utils/Log.h"


class EmulatorRunState : public EmulatorBaseState
{
private:
	
public:
	void execute() override
	{
		mHandleFrameCallback();
	}
};


