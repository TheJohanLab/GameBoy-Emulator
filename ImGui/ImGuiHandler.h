#pragma once

#include "ImGuiRenderer.h"
#include "Emulator/States/EmulatorBaseState.h"
#include "Registries/Registries.h"
#include "Cartridge/Cartridge.h"

class CPU;
class PPU;

class ImGuiHandler
{
using onSetModeCallback = std::function<void(EmulatorState)>;
using onGotoModeCallback = std::function<void(u16)>;

private:
	std::unique_ptr<ImGuiRenderer> mImGuiRenderer{nullptr};
	std::shared_ptr<Cartridge> mCartridge;

	onSetModeCallback mOnSetMode{ nullptr };
	onGotoModeCallback mOnGotoMode{ nullptr };

public:

	ImGuiHandler(std::shared_ptr<Cartridge>, SDL_Window*, SDL_Renderer*);

	void setOnStepModeCallback(onSetModeCallback callback);
	void setOnGotoModeCallback(onGotoModeCallback callback);

	void setRegistriesReference(std::shared_ptr<Registries>);
	void setCPUReference(std::shared_ptr<CPU>);
	void setPPUReference(std::shared_ptr<PPU>);
	void setOpcodeReference(std::shared_ptr<u8>);

	void setStepMode(bool);
	void setGotoMode(u16);

	void render();

};