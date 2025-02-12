#pragma once

//#include <memory>

#include "EmulatorBaseState.h"
#include "Emulator/WindowEventManager.h"

#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <cstdint>

class EmulatorStepState : public EmulatorBaseState
{
private:
	std::shared_ptr<WindowEventManager> mWindowEventManager{ nullptr };

	bool goToAddressEnable{ false };
	u16 mGoToAddress;

public:

	EmulatorStepState()
	{
		mWindowEventManager = WindowEventManager::GetInstance();
	}

	void execute() override
	{
		if (goToAddressEnable)
		{
			auto pc = CPU::getCurrPC();
			if (pc == mGoToAddress || mWindowEventManager->isKeyPressed(SDLK_RETURN))
				goToAddressEnable = false;
			else
				mHandleFrameCallback();

			return;
		}

		if (mWindowEventManager->isKeyPressed(SDLK_SPACE))
		{
			mStepCallback();
			mLogsCallback();
		}
		else if (mWindowEventManager->isKeyPressed(SDLK_RETURN))
		{
			GBE_LOG_INFO("Please enter a valid value you want to go to :");
			std::string input;
			std::cin >> input;
			if (!isValidHex16(input)) {
				std::cerr << "Invalid format. Please enter a correct 16 bits hex value.\n";
				return;
			}
			mGoToAddress = hexStringToUint16(input);
			goToAddressEnable = true;
		}
		mDrawCallback();
	}

private:

	bool isValidHex16(const std::string& input) {
		std::regex hexPattern("^(0x|0X)?[0-9a-fA-F]{1,4}$");
		return std::regex_match(input, hexPattern);
	}

	uint16_t hexStringToUint16(const std::string& input) {
		uint16_t value;
		std::stringstream ss;
		ss << std::hex << input;
		ss >> value;
		return value;
	}
};