#include <iostream>
#include "Bus/Bus.h"
#include "Clock/Clock.h"
#include <chrono>
#include "CPU/CPU.h"

#include <SDL.h>
#include "GameLoop/GameLoop.h"
#include "Screen/Screen.h"
#include "PPU/PPU.h"
#include <memory>
#include <functional>

#include "Utils/Log.h"
#include "Utils/Utils.h"

int main(int argc, char** argv)
{
	gbe::Log::init();
	GBE_LOG_ERROR("error");
	GBE_LOG_INFO("info");
	GBE_LOG_TRACE("trace");
	GBE_LOG_WARN("warn");
	//std::unique_ptr<Screen> pScreen = std::make_unique<Screen>(SCREEN_WIDTH, SCREEN_HEIGHT);
	Screen screen(SCREEN_WIDTH, SCREEN_HEIGHT);
	Bus bus;
	
	
	CPU cpu(&bus);
	PPU ppu(&bus, &screen);
	bus.setDMATransfertCallback(BIND_FUNC(ppu, PPU::startDMATransfer));

	bus.write(0xFF46, 1);
	//GameLoop gameLoop(cpu, &ppu);
	//ppu.writeOAM(0, 1, 2, 3, 4);
	//bus.write(0xFE00, 0x0A);
	//ppu.render();
	//gameLoop.startGame();



	

	return 0;
}