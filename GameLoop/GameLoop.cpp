#include "pch.h"

#include "GameLoop.h"

#include "ImGui/ImGuiHandler.h"
//#include "Utils/Log.h"

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
	mPPU->getScreen()->setOnCloseEvent(BIND_FUNC_NO_ARGS(this, GameLoop::stopGame));
	mPPU->setOnRenderListener(BIND_FUNC_1_ARG(this, GameLoop::render));

	mStateFactory->setHandleFrameCallback(BIND_FUNC_NO_ARGS(this, GameLoop::handleFrame));
	mStateFactory->setHandleBootFrameCallback(BIND_FUNC_NO_ARGS(this, GameLoop::handleBootFrame));
	mStateFactory->setDrawCallback(BIND_FUNC_NO_ARGS(mPPU, PPU::draw));
	mStateFactory->setStepCallback(BIND_FUNC_NO_ARGS(this, GameLoop::step));

	//mImGuiHandler->setOnStepModeCallback([this](EmulatorState state) {this->setEmulatorState(state); });
	mImGuiHandler->setOnStepModeCallback(BIND_FUNC_1_ARG(this, GameLoop::setEmulatorState));
	mScreen = mPPU->getScreen(); //TODO check what to do with screen in GameLoop (singleton ?)

	mWindowEventManager = WindowEventManager::GetInstance();
	//mWindowEventManager = std::make_shared<WindowEventManager>();

	setEmulatorState(EmulatorState::INIT);

}

void GameLoop::setEmulatorState(EmulatorState state)
{
	mCurrentEmulatorState = mStateFactory->createState(state);

}

void GameLoop::setEmulatorState2()
{
}

void GameLoop::startGame()
{
	
	mFrameStart = SDL_GetPerformanceCounter();
	mIsRunning = true;

	while (mIsRunning)
	{
		mWindowEventManager->handleEvents();
		//mScreen->startRendering()
		//mPPU->handleWindowEvents();
		mCurrentEmulatorState->execute();
	}
	
	//if (mSequence.empty())
	//{
	//	while (mIsRunning)
	//	{
	//		if (!mIsCartridgeLoaded)
	//		{
	//			//mBootRom->execute();
	//			mPPU->handleWindowEvents();
	//			mPPU->draw();
	//		}
	//		else
	//		{
	//			mPPU->handleWindowEvents();
	//			handleFrame();
	//			//handleScreenFrame();
	//		}

	//	}
	//}
	//else
	//{
	//	while (mIsRunning)
	//	{
	//		std::vector<std::function<void()>>::iterator sequenceIterator = mSequence.begin();
	//
	//		for (sequenceIterator; sequenceIterator != mSequence.end(); sequenceIterator++)
	//		{
	//			waitForNextFrame();
	//			mPPU->handleWindowEvents();
	//			(*sequenceIterator)();
	//			handleScreenFrame();
	//		}	
	//	}
	//}
}


void GameLoop::handleBootFrame()
{
	if (mCycles < cyclesPerFrame)
	//if (mCycles < 20)
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

void GameLoop::handleFrame()
{
	if (mCycles < cyclesPerFrame)
	//if (mCycles < 20)
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
	u8 currCycle = mCPU->executeOpcode(mCPU->getOpcode());

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


void GameLoop::setCartridgeLoaded()
{
	setEmulatorState(EmulatorState::BOOT);
	mCPU->getInterruptsManager()->initInterrupts();
	//mIsCartridgeLoaded = true;
	/*mBootRom->initializeBootRom();*/
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
