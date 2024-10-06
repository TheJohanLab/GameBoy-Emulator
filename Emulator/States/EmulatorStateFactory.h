#pragma once

#include <memory>
#include <functional>

#include "EmulatorBaseState.h"
#include "StateInit.h"
#include "StateBoot.h"
#include "StateRun.h"
#include "BootRom/BootRom.h"

class EmulatorStateFactory
{
private:
	std::shared_ptr<BootRom> mBootRom;
	std::function<void()> mHandleFrameCallback{ nullptr };
	std::function<void()> mHandleBootFrameCallback{ nullptr };
	std::function<void()> mDrawCallback{ nullptr };

public:
	EmulatorStateFactory(std::shared_ptr<BootRom> bootRom)
		:mBootRom(bootRom)
	{}

	void setHandleFrameCallback(std::function<void()> callback) { mHandleFrameCallback = callback; }
	void setHandleBootFrameCallback(std::function<void()> callback) { mHandleBootFrameCallback = callback; }
	void setDrawCallback(std::function<void()> callback) { mDrawCallback = callback; }

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
			default:
				GBE_LOG_ERROR("The state is undefined");
				break;
		}

		state->setHandleFrameCallback(mHandleFrameCallback);
		state->setHandleBootFrameCallback(mHandleBootFrameCallback);
		state->setDrawCallback(mDrawCallback);

		return state;
	}
};