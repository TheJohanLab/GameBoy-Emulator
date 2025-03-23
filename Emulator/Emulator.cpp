#include "pch.h"

#include "Emulator.h"
#include "Interrupts/InterruptsManager.h"

#include "Timer/Timer.h"


namespace gbe {

	Emulator::Emulator()
	{
		gbe::Log::init();
		GBE_LOG_INFO("Game boy Emulator initialization");
	
		initEmulator();
		//boot();
	}

	Emulator::~Emulator()
	{
	}

	void Emulator::startEmulator()
	{
		mGameLoop->startGame();
	}

	void Emulator::initEmulator()
	{
		mMemory = std::make_shared<Memory>();
		mCartridge = std::make_shared<Cartridge>();
		mBus = std::make_shared<Bus>(mMemory, mCartridge);

		mScreen = std::make_shared<Screen>(SCREEN_WIDTH, SCREEN_HEIGHT);
		mPPU = std::make_shared<PPU>(mBus, mScreen);
		mCPU = std::make_shared<CPU>(mBus, mPPU);
		mImGui = std::make_shared<ImGuiHandler>(mScreen->getWindow(), mScreen->getRenderer());
		mTimer = std::make_shared<Timer>(mBus->read(TIMA), mBus->read(TMA), mBus->read(TAC));

		auto weak_cpu = std::weak_ptr(mCPU);
		if (weak_cpu.expired())
			GBE_LOG_ERROR("Expired");
		if (!weak_cpu.lock())
			GBE_LOG_ERROR("lock error");

		mCPU->createInternalComponents(weak_cpu);

		mImGui->setRegistriesReference(mCPU->getRegistriesRef());
		mImGui->setCPUReference(mCPU);
		mImGui->setPPUReference(mPPU);
		mImGui->setMemoryReference(mMemory);
		mImGui->setCartridgeReference(mCartridge);
		mImGui->setTimerReferences(mTimer);


		mGameLoop = std::make_shared<GameLoop>(mCPU, mPPU, mImGui, mTimer);

		setCallbacks();

	}



	void Emulator::setCallbacks()
	{


		mBus->setDMATransfertCallback(BIND_FUNC_1_ARG(mPPU, PPU::startDMATransfer));

		mCPU->getBootRom()->setStateCallback(BIND_FUNC_1_ARG(mGameLoop, GameLoop::setEmulatorState));

		mImGui->setOnLoadCartridgeCallback(BIND_FUNC_1_ARG(mCartridge, Cartridge::loadCartridge));
	}

	void Emulator::boot()
	{
	}

	void Emulator::quit()
	{
		//mGameLoop->stopGame();
	}
}
