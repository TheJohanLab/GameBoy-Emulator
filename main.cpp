#include <iostream>
#include "Bus/Bus.h"
#include "Clock/Clock.h"
#include <chrono>
#include "CPU/CPU.h"

#include <SDL.h>

int main(int argc, char** argv)
{
	

	Bus bus;
	CPU cpu = CPU(bus);
	cpu.executeOpcode();
	Uint64 frameStart;
	Uint64 frameEnd;
	/*Clock clock = Clock();*/

	int cycles = 0;
	const int cyclesPerFrame = 70224;
	const double timePerFrame = 1.0 / 60.0;
	// frameStart
	frameStart = SDL_GetPerformanceCounter();
	bool isRunning = true;
	int cnt = 0;

	//std::cout << "SDL_GetPerformanceCounter start " << frameStart << "\n";

	while (isRunning)
	{
		while (cycles < cyclesPerFrame)
		{
			cpu.executeOpcode();
			cycles += 4 ;
		}
		std::cout << "Nombre d'instructions : " << cycles / 4 << std::endl; // 17556
		std::cout << "Nombre de cycles : " << cycles<< std::endl; // 70224

		cycles -= cyclesPerFrame;

		std::cout << "Nombre de cycles après reset : " << cycles << std::endl; // 0


		frameEnd = SDL_GetPerformanceCounter();

		while (true)
		{
			frameEnd = SDL_GetPerformanceCounter();
			double frameElapsedInSec = (double)(frameEnd - frameStart) / SDL_GetPerformanceFrequency();
			//std::cout << "get performance frequency " << SDL_GetPerformanceFrequency() << "\n";
			//std::cout << "SDL_GetPerformanceCounter end " << frameEnd << "\n";

			if (frameElapsedInSec >= timePerFrame)
			{
				std::cout << "frameElapsedInSec" << frameElapsedInSec << "\n";
				cnt++;
				break;
			}
		}

		frameStart = frameEnd;

		if (cnt >= 60)
		{
			std::cout << "fin du programme" << "\n";
			break;
		}
	}
		// while (cycles < CyclesPerFrame)
			// excution opcode
			// cycles += cyclesInstruction
		// cycles -= cyclesPerFrame
		// frameEnd
		// while(true)
			// frameEnd
			// elapsedTimeInFrame
			// if elapsedTimeInFrame >= 1/60s
			// break
		// frameStart = frameEnd



	return 0;
}