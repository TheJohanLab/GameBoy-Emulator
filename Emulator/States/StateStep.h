#pragma once

//#include <memory>

#include "EmulatorBaseState.h"
#include "Emulator/WindowEventManager.h"

class EmulatorStepState : public EmulatorBaseState
{
private:
	std::shared_ptr<WindowEventManager> mWindowEventManager{ nullptr };

public:
	EmulatorStepState()
	{
		mWindowEventManager = WindowEventManager::GetInstance();
	}


	void execute() override
	{

		if (mWindowEventManager->isKeyPressed(SDLK_SPACE))
		{
			mStepCallback();
			mLogsCallback();
		}
		
		mDrawCallback();
		

	}
};