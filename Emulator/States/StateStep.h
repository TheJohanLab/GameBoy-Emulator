#pragma once

//#include <memory>

#include "EmulatorBaseState.h"
#include "Emulator/WindowEventManager.h"

//TODO Remove the includes
#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <cstdint>

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

#ifdef LOG_DEBUG
			mLogsCallback();
#endif
		}

		mDrawCallback();
	}

};