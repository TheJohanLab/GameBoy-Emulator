#pragma once

#include <memory>

#include "EmulatorBaseState.h"
#include "Emulator/WindowEventManager.h"

class EmulatorStepState : public EmulatorBaseState
{
private:
	std::shared_ptr<WindowEventManager> mWindowEventManager;

public:
	EmulatorStepState(std::shared_ptr<WindowEventManager> eventManager)
		:mWindowEventManager(eventManager)
	{}


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