#include "pch.h"

#include "ImGuiHandler.h"
#include "CPU/CPU.h"
#include "PPU/PPU.h"

ImGuiHandler::ImGuiHandler(std::shared_ptr<Cartridge> cartridge, 
							SDL_Window* window, 
							SDL_Renderer* renderer)
	: mCartridge(cartridge)
{
	mImGuiRenderer = std::make_unique<ImGuiRenderer>(
		cartridge,
		window,
		renderer);

	//callbacks
	mImGuiRenderer->setOnStepOption(BIND_FUNC_1_ARG(this, ImGuiHandler::setStepMode));
	mImGuiRenderer->setOnGotoMode(BIND_FUNC_1_ARG(this, ImGuiHandler::setGotoMode));
}

void ImGuiHandler::setOnStepModeCallback(onSetModeCallback callback)
{
	mOnSetMode = callback;
}

void ImGuiHandler::setOnGotoModeCallback(onGotoModeCallback callback)
{
	mOnGotoMode = callback;
}

void ImGuiHandler::setRegistriesReference(std::shared_ptr<Registries> registries)
{
	mImGuiRenderer->setRegistriesReference(registries);
}

void ImGuiHandler::setCPUReference(std::shared_ptr<CPU> cpu)
{
	mImGuiRenderer->setCPUReference(cpu);
}

void ImGuiHandler::setPPUReference(std::shared_ptr<PPU> ppu)
{
	mImGuiRenderer->setPPUReference(ppu);
}

void ImGuiHandler::setOpcodeReference(std::shared_ptr<u8> opcode)
{
	mImGuiRenderer->setOpcodeReference(opcode);
}

void ImGuiHandler::setStepMode(bool stepMode)
{
	mOnSetMode(stepMode ? EmulatorState::STEP : EmulatorState::RUN);
}

void ImGuiHandler::setGotoMode(u16 address)
{
	mOnGotoMode(address);
}

void ImGuiHandler::render()
{
	mImGuiRenderer->render();
}
