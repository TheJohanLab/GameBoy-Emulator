#pragma once

#include <iostream>
#include <chrono>
#include <memory>
#include <functional>
#include <SDL.h>

#include "Clock/Clock.h"
#include "Bus/Bus.h"
#include "CPU/CPU.h"
#include "GameLoop/GameLoop.h"
#include "Screen/Screen.h"
#include "PPU/PPU.h"
#include "Interrupts/InterruptsManager.h"

#include "Utils/Log.h"
#include "Utils/Utils.h"
#include "Utils/Addresses.h"

namespace gbe {

	class Emulator 
	{
	protected:
		std::shared_ptr<Screen> mScreen;
		std::shared_ptr<Bus> mBus;
		std::shared_ptr<CPU> mCPU;
		std::shared_ptr<PPU> mPPU;
		std::shared_ptr<BootRom> mBootRom;
		std::shared_ptr<GameLoop> mGameLoop;
		std::shared_ptr<InterruptsManager> mInterruptsManager;

	public:
		Emulator();
		~Emulator();

		void startEmulator();

	private:

		void initEmulator();
		void setCallbacks();
		void boot();
		void quit();

	};
}