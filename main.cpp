#include <iostream>
#include "Bus/Bus.h"
#include "Clock/Clock.h"
#include <chrono>
#include "CPU/CPU.h"


#include <SDL.h>
#include "GameLoop/GameLoop.h"

int main(int argc, char** argv)
{
	

	Bus bus;
	CPU cpu(&bus);
	GameLoop gameLoop(cpu);

	gameLoop.startGame();

	return 0;
}