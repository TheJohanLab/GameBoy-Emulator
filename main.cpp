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
#include "Utils/Addresses.h"

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

	bus->write(0xC000, 0x14);
	bus->write(0xC001, 0x1C);
	bus->write(0xC002, 2);
	bus->write(0xC003, 0);

	bus->write(DMA, 0xC0);

	gameLoop.startGame();


	return 0;
}