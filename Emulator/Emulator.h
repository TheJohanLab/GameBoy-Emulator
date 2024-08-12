#pragma once

#include <iostream>
#include "../Bus/Bus.h"
#include "../Clock/Clock.h"
#include <chrono>
#include "../CPU/CPU.h"

#include <SDL.h>
#include "../GameLoop/GameLoop.h"
#include "../Screen/Screen.h"
#include "../PPU/PPU.h"
#include <memory>
#include <functional>

#include "../Utils/Log.h"
#include "../Utils/Utils.h"
#include "../Utils/Addresses.h"

namespace gbe {

	class Emulator 
	{
	private:
		std::unique_ptr<Screen> mScreen;
		std::unique_ptr<Bus> mBus;
		std::unique_ptr<CPU> mCPU;
		std::unique_ptr<PPU> mPPU;
		std::unique_ptr<GameLoop> mGameLoop;

	public:
		Emulator();
		~Emulator();

		void startEmulator();

	private:

		void initEmulator();
		void setCallbacks();
		void boot();

	};
}