#pragma once

#include <iostream>
#include "Bus/Bus.h"
#include "Clock/Clock.h"
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
	protected:
		std::shared_ptr<Screen> mScreen;
		std::shared_ptr<Bus> mBus;
		std::shared_ptr<CPU> mCPU;
		std::shared_ptr<PPU> mPPU;
		std::shared_ptr<GameLoop> mGameLoop;

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