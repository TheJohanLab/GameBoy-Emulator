#include "GameLoop.h"

#include "../Utils/Log.h"

u16 GameLoop::waitingDots = 0;
void GameLoop::addVirtualWaitingDots(u16 dots)
{
	GameLoop::waitingDots = dots;
}
void GameLoop::decVirtualWaitingDots(u16 dots)
{
	GameLoop::waitingDots -= dots;
}

GameLoop::GameLoop(std::shared_ptr<CPU> cpu, std::shared_ptr<PPU> ppu, std::shared_ptr<BootRom> bootRom)
	:mCPU(cpu), mPPU(ppu), mBootRom(bootRom), 
	mStateFactory(std::make_unique<EmulatorStateFactory>(bootRom))
{
	mPPU->getScreen()->setOnCloseEvent(BIND_FUNC_NO_ARGS(this, GameLoop::stopGame));
	mStateFactory->setHandleFrameCallback(BIND_FUNC_NO_ARGS(this, GameLoop::handleFrame));
	mStateFactory->setDrawCallback(BIND_FUNC_NO_ARGS(mPPU, PPU::draw));
	setEmulatorState(EmulatorState::INIT);

}

void GameLoop::setEmulatorState(EmulatorState state)
{
	mCurrentEmulatorState = mStateFactory->createState(state);

}

void GameLoop::startGame()
{
	
	mFrameStart = SDL_GetPerformanceCounter();
	mIsRunning = true;

	while (mIsRunning)
	{
		mPPU->handleWindowEvents();
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
	//mCPU.callInterruptHandler();

	synchroniseFrame();

}

u8 GameLoop::step()
{
	u8 currCycle = mCPU->executeOpcode(*mCPU->getPC());

	//mPPU->writeOAM(0, 20, 20, 1, 0);
	//m_XPos++;

	mPPU->render(currCycle);

	//mPPU->render(12);

	//mCPU.callInterruptHandler();

	//return 12;
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


void GameLoop::setCartridgeLoaded()
{
	setEmulatorState(EmulatorState::BOOT);
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
