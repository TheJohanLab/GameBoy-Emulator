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

public:
	ImGuiHandler(std::shared_ptr<Cartridge>, SDL_Window*, SDL_Renderer*);

	void setRegistriesReference(std::shared_ptr<Registries>);
	void setCPUReference(std::shared_ptr<CPU>);
	void setPPUReference(std::shared_ptr<PPU>);
	void setOpcodeReference(std::shared_ptr<u8>);

	void setStepMode(bool);
	void setGotoMode(std::string& input);

	void render();

private:
	bool isValidHex16(const std::string& input);
	u16 convertToU16(const std::string& input);

//callbacks
private:
	onSetModeCallback mOnSetMode{ nullptr };
	onGotoModeCallback mOnGotoMode{ nullptr };
public:
	void setOnStepModeCallback(onSetModeCallback callback);
	void setOnGotoModeCallback(onGotoModeCallback callback);
};