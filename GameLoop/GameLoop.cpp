#include "GameLoop.h"

GameLoop::GameLoop(CPU & cpu, PPU* ppu)
	:mCPU(cpu), mPPU(ppu)
{
}

void GameLoop::startGame()
{

	mFrameStart = SDL_GetPerformanceCounter();
	mIsRunning = true;
	//int cnt = 0;
	u32 cycles = 0;

	while (mIsRunning)
	{
		handleFrame(cycles);
	}
}


void GameLoop::handleFrame(u32 & cycles)
{
	while (cycles < cyclesPerFrame)
	{
		cycles += step();

	}
	std::cout << "Nombre d'instructions : " << cycles / 4 << std::endl;
	std::cout << "Nombre de cycles : " << cycles << std::endl;

	cycles -= cyclesPerFrame;

	std::cout << "Nombre de cycles après reset : " << cycles << std::endl;
	//TODO Faire une methode qui gere tous les processus du CPU par frame
	//u8 currCycle = mCPU.executeOpcode(0x01);
	//mCPU.callInterruptHandler();

	synchroniseFrame();
	
	
}


u8 GameLoop::step()
{
	u8 currCycle = mCPU.executeOpcode(0x01);


	mPPU->render(currCycle);

	//mCPU.callInterruptHandler();

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
			std::cout << "frameElapsedInSec" << frameElapsedInSec << "\n";
			//cnt++;
			break;
		}
	}

	mFrameStart = mFrameEnd;

	/*if (cnt >= 60)
	{
		std::cout << "fin du programme" << "\n";
		break;
	}*/
}