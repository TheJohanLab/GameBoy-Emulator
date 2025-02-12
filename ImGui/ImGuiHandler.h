#pragma once

#include "ImGuiRenderer.h"
#include "Emulator/States/EmulatorBaseState.h"
#include "Registries/Registries.h"
#include "Cartridge/Cartridge.h"

class ImGuiHandler
{
using onSetModeCallback = std::function<void(EmulatorState)>;

private:
	
	std::unique_ptr<ImGuiRenderer> mImGuiRenderer{nullptr};
	std::shared_ptr<Cartridge> mCartridge;

	onSetModeCallback mSetModeCallback{ nullptr };


public:

	ImGuiHandler(std::shared_ptr<Cartridge>, SDL_Window*, SDL_Renderer*);

	void setOnStepModeCallback(onSetModeCallback callback);
	void setRegistriesReference(std::shared_ptr<Registries>);
	void setMode(EmulatorState);
	void render();

};