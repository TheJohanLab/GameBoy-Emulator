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
		//mWindowEventManager = std::make_shared<WindowEventManager>();
	}


	void execute() override
	{
		if (mWindowEventManager->isKeyPressed(SDLK_SPACE))
			mStepCallback();
		
		else
			mDrawCallback();


		//mHandleBootFrameCallback();
		//mBootRom->execute();
	}
};