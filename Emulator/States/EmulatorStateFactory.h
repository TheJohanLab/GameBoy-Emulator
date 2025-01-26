#pragma once

//#include <memory>
//#include <functional>

#include "EmulatorBaseState.h"
#include "StateInit.h"
#include "StateBoot.h"
#include "StateRun.h"
#include "StateStep.h"
#include "BootRom/BootRom.h"
#include "Emulator/WindowEventManager.h"

class EmulatorStateFactory
{
	using frameCallback = std::function<void()>;

protected:
	std::shared_ptr<WindowEventManager> mEventManager;

private:
	std::shared_ptr<BootRom> mBootRom;
	frameCallback mHandleFrameCallback{ nullptr };
	frameCallback mHandleBootFrameCallback{ nullptr };
	frameCallback mDrawCallback{ nullptr };
	frameCallback mStepCallback{ nullptr };

public:
	EmulatorStateFactory(std::shared_ptr<WindowEventManager> eventManager, std::shared_ptr<BootRom> bootRom)
		:mEventManager(eventManager), mBootRom(bootRom)
	{}

	void setHandleFrameCallback(std::function<void()> callback) { mHandleFrameCallback = callback; }
	void setHandleBootFrameCallback(std::function<void()> callback) { mHandleBootFrameCallback = callback; }
	
	void setDrawCallback(std::function<void()> callback) { mDrawCallback = callback; }
	void setStepCallback(std::function<void()> callback) { mStepCallback = callback; }

	std::unique_ptr<class EmulatorBaseState> createState(EmulatorState stateType)
	{
		std::unique_ptr<class EmulatorBaseState> state;

		switch (stateType)
		{
			case EmulatorState::INIT:
				state = std::make_unique<EmulatorInitState>();
				break;
			case EmulatorState::BOOT:
				state = std::make_unique<EmulatorBootState>(mBootRom);
				break;
			case EmulatorState::RUN:
				state = std::make_unique<EmulatorRunState>();
				break;
			case EmulatorState::STEP:
				state = std::make_unique<EmulatorStepState>(mEventManager);
				break;
			default:
				GBE_LOG_ERROR("The state is undefined");
				break;
		}

		state->setHandleFrameCallback(mHandleFrameCallback);
		state->setHandleBootFrameCallback(mHandleBootFrameCallback);
		state->setDrawCallback(mDrawCallback);
		state->setStepCallback(mStepCallback);

		return state;
	}
};