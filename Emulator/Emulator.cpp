#include "pch.h"

#include "Emulator.h"
#include "Interrupts/InterruptsManager.h"


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
		mBus = std::make_shared<Bus>();

		mEventManager = std::make_shared<WindowEventManager>();
		mScreen = std::make_shared<Screen>(mEventManager, mBus->getCartrige(), SCREEN_WIDTH, SCREEN_HEIGHT);
		mPPU = std::make_shared<PPU>(mBus, mScreen);
		mCPU = std::make_shared<CPU>(mBus, mPPU);
		auto weak_cpu = std::weak_ptr(mCPU);
		if (weak_cpu.expired())
			GBE_LOG_ERROR("Expired");
		if (!weak_cpu.lock())
			GBE_LOG_ERROR("lock error");
		mCPU->createInternalComponents(weak_cpu);
		mPPU->setRegistriesRef(mCPU->getRegistries2());

		//mBootRom = std::make_shared<BootRom>(mBus, mPPU, mCPU);

		mGameLoop = std::make_shared<GameLoop>(mCPU, mPPU, mEventManager);

		setCallbacks();

		//mPPU->writeOAM(1, 20, 50, 2, 0);
		//mPPU->writeOAM(2, 22, 52, 2, 0);
		//mBus->write(DMA, 0xC0);
	}

	void Emulator::setCallbacks()
	{
		mBus->setDMATransfertCallback(BIND_FUNC_1_ARG(mPPU, PPU::startDMATransfer));
		//mBus->setLoadCartridgeCallback(std::bind(&Emulator::startEmulator, this));
		mBus->setLoadCartridgeCallback(BIND_FUNC_NO_ARGS(mGameLoop, GameLoop::setCartridgeLoaded));
		mPPU->setOnVBlankListener(BIND_FUNC_1_ARG(mCPU->getInterruptsManager(), InterruptsManager::setInterrupt));
		mCPU->getBootRom()->setStateCallback(BIND_FUNC_1_ARG(mGameLoop, GameLoop::setEmulatorState));
	}

	void Emulator::boot()
	{
	}

	void Emulator::quit()
	{
		mGameLoop->stopGame();
	}
}
