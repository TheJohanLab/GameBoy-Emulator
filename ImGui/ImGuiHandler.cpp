#include "pch.h"

#include "ImGuiHandler.h"

ImGuiHandler::ImGuiHandler(std::shared_ptr<Cartridge> cartridge, 
							SDL_Window* window, 
							SDL_Renderer* renderer)
	: mCartridge(cartridge)
{
	mImGuiRenderer = std::make_unique<ImGuiRenderer>(
		cartridge,
		window,
		renderer);
}

void ImGuiHandler::setOnStepModeCallback(onSetModeCallback callback)
{
	mSetModeCallback = callback;
}

void ImGuiHandler::setRegistriesReference(std::shared_ptr<Registries> registries)
{
	mImGuiRenderer->setRegistries(registries);
}

void ImGuiHandler::setMode(EmulatorState emulatorState)
{
	mSetModeCallback(emulatorState);
}

void ImGuiHandler::render()
{
	mImGuiRenderer->render();
}
