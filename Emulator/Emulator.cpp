#include "Emulator.h"

namespace gbe {

	Emulator::Emulator()
	{
		gbe::Log::init();
		GBE_LOG_INFO("Game boy Emulator initialization");
	
		initEmulator();
		boot();
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


		mScreen = std::make_shared<Screen>(mBus->getCartrige(), SCREEN_WIDTH, SCREEN_HEIGHT);
		mCPU = std::make_shared<CPU>(mBus);
		mPPU = std::make_shared<PPU>(mBus, mScreen);
		mBootRom = std::make_shared<BootRom>(mBus, mPPU);

		mGameLoop = std::make_shared<GameLoop>(mCPU, mPPU, mBootRom);

		setCallbacks();

		//mPPU->writeOAM(1, 20, 50, 2, 0);
		//mPPU->writeOAM(2, 22, 52, 2, 0);
		//mBus->write(DMA, 0xC0);
	}

	void Emulator::setCallbacks()
	{
		mBus->setDMATransfertCallback(BIND_FUNC_1_ARG(*mPPU, PPU::startDMATransfer));
		//mBus->setLoadCartridgeCallback(std::bind(&Emulator::startEmulator, this));
		mBus->setLoadCartridgeCallback(BIND_FUNC_NO_ARGS(*mGameLoop, GameLoop::setCartridgeLoaded));
	}

	void Emulator::boot()
	{

	}

}
