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
		mScreen = std::make_unique<Screen>(SCREEN_WIDTH, SCREEN_HEIGHT);
		mBus = std::make_unique<Bus>();

		mCPU = std::make_unique<CPU>(mBus.get());
		mPPU = std::make_unique<PPU>(mBus.get(), mScreen.get());

		mGameLoop = std::make_unique<GameLoop>(mCPU.get(), mPPU.get());

		setCallbacks();

		mBus->write(0xC000, 0x14);
		mBus->write(0xC001, 0x1C);
		mBus->write(0xC002, 2);
		mBus->write(0xC003, 0);

		mBus->write(DMA, 0xC0);
	}

	void Emulator::setCallbacks()
	{
		mBus->setDMATransfertCallback(BIND_FUNC_1_ARG(*mPPU, PPU::startDMATransfer));
	}

	void Emulator::boot()
	{

	}

}
