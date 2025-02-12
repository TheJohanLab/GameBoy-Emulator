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

	//callbacks
	mImGuiRenderer->setOnStepOption(BIND_FUNC_1_ARG(this, ImGuiHandler::setStepMode));
}

void ImGuiHandler::setOnStepModeCallback(onSetModeCallback callback)
{
	mOnSetMode = callback;
}

void ImGuiHandler::setRegistriesReference(std::shared_ptr<Registries> registries)
{
	mImGuiRenderer->setRegistries(registries);
}

void ImGuiHandler::setStepMode(bool stepMode)
{
	mOnSetMode(stepMode ? EmulatorState::STEP : EmulatorState::RUN);
}

void ImGuiHandler::render()
{
	mImGuiRenderer->render();
}
