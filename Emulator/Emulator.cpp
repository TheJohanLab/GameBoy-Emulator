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
		mScreen = std::make_shared<Screen>(SCREEN_WIDTH, SCREEN_HEIGHT);
		mBus = std::make_shared<Bus>();

		mCPU = std::make_shared<CPU>(mBus);
		mPPU = std::make_shared<PPU>(mBus, mScreen);

		mGameLoop = std::make_shared<GameLoop>(mCPU, mPPU);

		setCallbacks();

		BootRom bootRom(mPPU);
		bootRom.initializeBootRom();

		//mPPU->writeOAM(1, 20, 50, 2, 0);
		//mPPU->writeOAM(2, 22, 52, 2, 0);
		//mBus->write(DMA, 0xC0);
	}

	void Emulator::setCallbacks()
	{
		mBus->setDMATransfertCallback(BIND_FUNC_1_ARG(*mPPU, PPU::startDMATransfer));
	}

	void Emulator::boot()
	{

	}

}
