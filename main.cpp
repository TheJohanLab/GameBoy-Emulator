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
	std::unique_ptr<Screen> screen = std::make_unique<Screen>(SCREEN_WIDTH, SCREEN_HEIGHT);
	std::unique_ptr<Bus> bus = std::make_unique<Bus>();
	
	
	CPU cpu(bus.get());
	PPU ppu(bus.get(), screen.get());
	bus->setDMATransfertCallback(BIND_FUNC_1_ARG(ppu, PPU::startDMATransfer));

	//bus.write(0xFF46, 1);
	GameLoop gameLoop(cpu, &ppu);
	//ppu.writeOAM(0, 1, 2, 3, 4);
	//bus.write(0xFE00, 0x0A);
	//ppu.render();

	//ppu.writeOAM(0, 28, 20, 2, 0);
	ppu.writeOAM(1, 40, 20, 1, 0);
	ppu.writeOAM(2, 98, 20, 0, 0);
	ppu.writeOAM(3, 128, 20, 1, 0);
	gameLoop.startGame();


	return 0;
}