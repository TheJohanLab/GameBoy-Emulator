#pragma once

#include <memory>
#include <functional>

#include "EmulatorBaseState.h"
#include "InitState.h"
#include "BootState.h"
#include "BootRom/BootRom.h"

class EmulatorStateFactory
{
private:
	std::shared_ptr<BootRom> mBootRom;
	std::function<void()> mHandleFrameCallback{ nullptr };
	std::function<void()> mDrawCallback{ nullptr };

public:
	EmulatorStateFactory(std::shared_ptr<BootRom> bootRom)
		:mBootRom(bootRom)
	{}

	void setHandleFrameCallback(std::function<void()> callback) { mHandleFrameCallback = callback; }
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
		}

		state->setHandleFrameCallback(mHandleFrameCallback);
		state->setDrawCallback(mDrawCallback);
		return state;
	}
};