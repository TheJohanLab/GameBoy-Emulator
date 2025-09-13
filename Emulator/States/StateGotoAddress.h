#pragma once

#include "EmulatorBaseState.h"
#include "Emulator/WindowEventManager.h"

class EmulatorGotoAddressState : public EmulatorBaseState
{
private:
	std::shared_ptr<WindowEventManager> mWindowEventManager{ nullptr };
	u16 mGoToAddress;

public:

	EmulatorGotoAddressState(u16 gotoAddress)
		:mGoToAddress(gotoAddress)
	{
		mWindowEventManager = WindowEventManager::GetInstance();
	}

	void execute() override
	{

		auto pc = CPU::getCurrPC();
		if (pc == mGoToAddress || mWindowEventManager->isKeyPressed(SDLK_RETURN))
		{
			mSetModeCallback(EmulatorState::STEP);
			return;
		}

		mHandleFrameCallback();

	}

};