#include "GameLoop.h"

#include "../Utils/Log.h"

GameLoop::GameLoop(std::shared_ptr<CPU> cpu, std::shared_ptr<PPU> ppu)
	:mCPU(cpu), mPPU(ppu)
{
	mPPU->getScreen()->setOnCloseEvent(BIND_FUNC_NO_ARGS(this, GameLoop::stopGame));
}

void GameLoop::startGame()
{

	mFrameStart = SDL_GetPerformanceCounter();
	mIsRunning = true;

	
	if (mSequence.empty())
	{
		while (mIsRunning)
		{
			mPPU->handleWindowEvents();
			handleFrame();
		}
	}
	else
	{
		while (mIsRunning)
		{
			std::vector<std::function<void()>>::iterator sequenceIterator = mSequence.begin();

			for (sequenceIterator; sequenceIterator != mSequence.end(); sequenceIterator++)
			{
				waitForNextFrame();
				mPPU->handleWindowEvents();
				(*sequenceIterator)();
				handleScreenFrame();
			}

		}
		

	}
}



void GameLoop::handleFrame()
{
	if (mCycles < cyclesPerFrame)
	//if (mCycles < 20)
	{

		mCycles += step();
		//GBE_LOG_INFO("mCycles {0}", mCycles);
		return;
	}


	//std::cout << "Nombre d'instructions : " << mCycles / 4 << std::endl;
	//std::cout << "Nombre de cycles : " << mCycles << std::endl;
	
	mCycles -= cyclesPerFrame;

	//std::cout << "Nombre de cycles après reset : " << mCycles << std::endl;
	//TODO Faire une methode qui gere tous les processus du CPU par frame
	//u8 currCycle = mCPU.executeOpcode(0x01);
	//mCPU.callInterruptHandler();

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
	u8 currCycle = mCPU->executeOpcode(0x01);

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
