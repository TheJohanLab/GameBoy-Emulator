#include <iostream>
#include "Bus/Bus.h"
#include "Clock/Clock.h"
#include <chrono>
#include "CPU/CPU.h"

#include <SDL.h>
#include "GameLoop/GameLoop.h"
#include "Screen/Screen.h"
#include <memory>
#include <functional>

int main(int argc, char** argv)
{
	std::unique_ptr<Screen> pScreen = std::make_unique<Screen>(SCREENWIDTH, SCREENHEIGHT);
	Bus bus;
	CPU cpu(&bus);
	GameLoop gameLoop(cpu);
	gameLoop.startGame();

	return 0;
}