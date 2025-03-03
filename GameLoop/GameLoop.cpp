#include "pch.h"

#include "GameLoop.h"

#include "ImGui/ImGuiHandler.h"

EmulatorState GameLoop::mInitCurrState{ EmulatorState::INIT };

u16 GameLoop::waitingDots = 0;

void GameLoop::addVirtualWaitingDots(u16 dots)
{
	GameLoop::waitingDots = dots;
}
void GameLoop::decVirtualWaitingDots(u16 dots)
{
	GameLoop::waitingDots -= dots;
}

GameLoop::GameLoop(std::shared_ptr<CPU> cpu, std::shared_ptr<PPU> ppu, std::shared_ptr<ImGuiHandler> imGui)
	:	mCPU(cpu),
		mPPU(ppu),
		mImGuiHandler(imGui),
		mStateFactory(std::make_unique<EmulatorStateFactory>(cpu->getBootRom()))
{

	mScreen = mPPU->getScreen(); //TODO check what to do with screen in GameLoop (singleton ?)
	mWindowEventManager = WindowEventManager::GetInstance();
	mImGuiHandler->setOpcodeReference(std::shared_ptr<u8>(&mCurrentOpcode));
	
	setCallbacks();

	setEmulatorState(EmulatorState::INIT);

}

void GameLoop::setEmulatorState(EmulatorState state)
{
	//TODO print directly the state using the enum if possible
	switch (state)
	{
		case EmulatorState::INIT:
			GBE_LOG_INFO("Change emulator state to INIT");
			break;
		case EmulatorState::BOOT:
			GBE_LOG_INFO("Change emulator state to BOOT");
			break;
		case EmulatorState::RUN:
			GBE_LOG_INFO("Change emulator state to RUN");
			mInitCurrState = state;
			break;
		case EmulatorState::STEP:
			GBE_LOG_INFO("Change emulator state to STEP");
			mInitCurrState = state;
			break;
		case EmulatorState::GOTO:
			GBE_LOG_INFO("Change emulator state to GOTO");
			mInitCurrState = state;

			break;
	}
	
	mCurrentEmulatorState = mStateFactory->createState(state, mGotoAddress);
}

void GameLoop::onSetEmulatorStateStep(EmulatorState state)
{
	if (!(mInitCurrState == EmulatorState::INIT || mInitCurrState == EmulatorState::BOOT))
	{
		setEmulatorState(state);
	}
	
	// This line is necessary for the end of the boot rom routine
	mInitCurrState = state;

}

void GameLoop::onSetEmulatorStateGoto(u16 address)
{
	mGotoAddress = address;

	if (!(mInitCurrState == EmulatorState::INIT || mInitCurrState == EmulatorState::BOOT))
	{
		setEmulatorState(EmulatorState::GOTO);
	}

	// This line is necessary for the end of the boot rom routine
	mInitCurrState = EmulatorState::GOTO;
}

void GameLoop::startGame()
{
	
	mFrameStart = SDL_GetPerformanceCounter();
	mIsRunning = true;

	// Main loop
	while (mIsRunning)
	{
		mWindowEventManager->handleEvents();
		mCurrentEmulatorState->execute();
	}

}


void GameLoop::handleBootFrame()
{
	if (mCycles < cyclesPerFrame)
	{

		mCycles += bootStep();
	
		//GBE_LOG_INFO("cycles : {0}", mCycles);
		return;
	}


	//std::cout << "Nombre d'instructions : " << mCycles / 4 << std::endl;
	//std::cout << "Nombre de cycles : " << mCycles << std::endl;
	
	mCycles -= cyclesPerFrame;

	//std::cout << "Nombre de cycles après reset : " << mCycles << std::endl;
	//TODO Faire une methode qui gere tous les processus du CPU par frame
	//u8 currCycle = mCPU.executeOpcode(0x01);
	//mCPU.callInterruptHandler();

	//GBE_LOG_INFO("synchronise frame");
	synchroniseFrame();
	
	
}

inline void GameLoop::setCallbacks()
{
	//mPPU->getScreen()->setOnCloseEvent(BIND_FUNC_NO_ARGS(this, GameLoop::stopGame));
	mPPU->setOnRenderListener(BIND_FUNC_1_ARG(this, GameLoop::render));

	mStateFactory->setHandleFrameCallback(BIND_FUNC_NO_ARGS(this, GameLoop::handleFrame));
	mStateFactory->setHandleBootFrameCallback(BIND_FUNC_NO_ARGS(this, GameLoop::handleBootFrame));
	mStateFactory->setDrawCallback(BIND_FUNC_NO_ARGS(mPPU, PPU::draw));
	mStateFactory->setStepCallback(BIND_FUNC_NO_ARGS(this, GameLoop::step)); //TODO revoir ce callback pour le mode step
	mStateFactory->setLogsCallback(BIND_FUNC_NO_ARGS(this, GameLoop::logInfos));
	mStateFactory->setModeCallback(BIND_FUNC_1_ARG(this, GameLoop::setEmulatorState));

	mImGuiHandler->setOnStepModeCallback(BIND_FUNC_1_ARG(this, GameLoop::onSetEmulatorStateStep));
	mImGuiHandler->setOnGotoModeCallback(BIND_FUNC_1_ARG(this, GameLoop::onSetEmulatorStateGoto));
	mImGuiHandler->setOnRomLoadedCallback(BIND_FUNC_NO_ARGS(this, GameLoop::onRomLoaded));
	mImGuiHandler->setOnQuitCallback(BIND_FUNC_NO_ARGS(this, GameLoop::onStopGame));

	mWindowEventManager->setOnQuitCallback(BIND_FUNC_NO_ARGS(this, GameLoop::onStopGame));
}

void GameLoop::handleFrame()
{
	if (mCycles < cyclesPerFrame)
	{
		if (GameLoop::waitingDots != 0)
		{
			mCycles += GameLoop::waitingDots;
			GBE_LOG_INFO("waiting {0} dots", GameLoop::waitingDots);
			GameLoop::waitingDots = 0;
		}
		else
		{	
			mCycles += step();
		}

		//GBE_LOG_INFO("cycles : {0}", mCycles);
		return;
	}


	//std::cout << "Nombre d'instructions : " << mCycles / 4 << std::endl;
	//std::cout << "Nombre de cycles : " << mCycles << std::endl;
	
	mCycles -= cyclesPerFrame;

	//std::cout << "Nombre de cycles après reset : " << mCycles << std::endl;
	//TODO Faire une methode qui gere tous les processus du CPU par frame
	//u8 currCycle = mCPU.executeOpcode(0x01);
	//mCPU.callInterruptHandler();

	//GBE_LOG_INFO("synchronise frame");
	synchroniseFrame();
	
	
}

void GameLoop::handleScreenFrame()
{
	mPPU->executeFullFrameRender();

	synchroniseFrame();

}

u8 GameLoop::bootStep()
{

	u8 currentCycle{ 12 };
	mPPU->render(currentCycle);
	mCPU->getInterruptsManager()->callInterruptHandler();

	return currentCycle;
}

u8 GameLoop::step()
{	
	mCurrentOpcode = mCPU->getOpcode();

	u8 currCycle = mCPU->executeOpcode(mCurrentOpcode);

	mPPU->render(currCycle);

	mCPU->getInterruptsManager()->callInterruptHandler();

	return currCycle;
}

void GameLoop::synchroniseFrame()
{
	mFrameEnd = SDL_GetPerformanceCounter();

	while (true)
	{
		mFrameEnd = SDL_GetPerformanceCounter();
		double frameElapsedInSec = (double)(mFrameEnd - mFrameStart) / SDL_GetPerformanceFrequency();

		if (frameElapsedInSec >= timePerFrame)
		{
			//GBE_LOG_INFO("frameElapsedInSec : {0}", frameElapsedInSec);
			break;
		}
	}

	mFrameStart = mFrameEnd;

}

inline void GameLoop::render(std::array<std::array<Pixel, SCREEN_WIDTH>, SCREEN_HEIGHT>& pixelArray)
{
	mScreen->startRendering(pixelArray);
	mImGuiHandler->render();
	mScreen->render();
}

inline void GameLoop::logInfos() const
{
	mCPU->logOpcodesInfos(mCurrentOpcode);
	mCPU->logRegistries();
}

inline void GameLoop::reset()
{
	mPPU->reset();
	mCPU->resetMemory();
}


void GameLoop::onRomLoaded()
{
	reset();
	setEmulatorState(EmulatorState::BOOT);
	mCPU->getInterruptsManager()->initInterrupts();
}

void GameLoop::addToSequence(std::function<void()> task)
{
	mSequence.push_back(task);
}

void GameLoop::endSequence()
{
	mIsRunning = true;
}

void GameLoop::waitForNextFrame()
{
	mCycles = cyclesPerFrame;
}
