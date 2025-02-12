#pragma once

//#include <memory>
//#include <functional>

#include "EmulatorBaseState.h"
#include "StateInit.h"
#include "StateBoot.h"
#include "StateRun.h"
#include "StateStep.h"
#include "StateGotoAddress.h"
#include "BootRom/BootRom.h"
//#include "Emulator/WindowEventManager.h"

class EmulatorStateFactory
{
	using Callback = std::function<void()>;
	using ModeCallback = std::function<void(EmulatorState)>;

protected:
	//std::shared_ptr<WindowEventManager> mEventManager;

private:
	std::shared_ptr<BootRom> mBootRom;
	Callback mHandleFrameCallback{ nullptr };
	Callback mHandleBootFrameCallback{ nullptr };
	Callback mDrawCallback{ nullptr };
	Callback mStepCallback{ nullptr };
	Callback mLogsCallback{ nullptr };
	ModeCallback mSetModeCallback{ nullptr };

public:
	EmulatorStateFactory( std::shared_ptr<BootRom> bootRom)
		: mBootRom(bootRom)
	{}

	void setHandleFrameCallback(std::function<void()> callback) { mHandleFrameCallback = callback; }
	void setHandleBootFrameCallback(std::function<void()> callback) { mHandleBootFrameCallback = callback; }
	
	void setDrawCallback(std::function<void()> callback) { mDrawCallback = callback; }
	void setStepCallback(std::function<void()> callback) { mStepCallback = callback; }
	void setLogsCallback(std::function<void()> callback) { mLogsCallback = callback; }
	void setModeCallback(std::function<void(EmulatorState)> callback) { mSetModeCallback = callback; }

	std::unique_ptr<class EmulatorBaseState> createState(EmulatorState stateType, u16 gotoAddress = 0x0000)
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
				state = std::make_unique<EmulatorStepState>();
				break;
			case EmulatorState::GOTO:
				//auto address = GameLoop::getGotoAddress();
				state = std::make_unique<EmulatorGotoAddressState>(gotoAddress);
				break;
			default:
				GBE_LOG_ERROR("The state is undefined");
				break;
		}

		state->setHandleFrameCallback(mHandleFrameCallback);
		state->setHandleBootFrameCallback(mHandleBootFrameCallback);
		state->setDrawCallback(mDrawCallback);
		state->setStepCallback(mStepCallback);
		state->setLogsCallback(mLogsCallback);
		state->setSetModeCallback(mSetModeCallback);

		return state;
	}
};