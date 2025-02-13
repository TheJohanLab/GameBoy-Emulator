#include "pch.h"

#include "ImGuiHandler.h"
#include "CPU/CPU.h"
#include "PPU/PPU.h"

#include <regex>

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
	mImGuiRenderer->setOnStepModeCallback(BIND_FUNC_1_ARG(this, ImGuiHandler::setStepMode));
	mImGuiRenderer->setOnGotoModeCallback(BIND_FUNC_1_ARG(this, ImGuiHandler::setGotoMode));
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

void ImGuiHandler::setGotoMode(std::string& inputBuffer)
{
	if (!isValidHex16(inputBuffer)) {
		GBE_LOG_ERROR("Invalid format. Please enter a correct 16 bits hex value : {0}\n", 
			inputBuffer.c_str());

		mOnSetMode(EmulatorState::STEP);
		return;
	}

	mOnGotoMode(convertToU16(inputBuffer));
}

void ImGuiHandler::render()
{
	mImGuiRenderer->render();
}


bool ImGuiHandler::isValidHex16(const std::string& input) {
	std::regex hexPattern("^(0x|0X)?[0-9a-fA-F]{1,4}$");
	return std::regex_match(input, hexPattern);
}

uint16_t ImGuiHandler::convertToU16(const std::string& input) {
	u16 value;
	std::stringstream ss;
	ss << std::hex << input;
	ss >> value;
	return value;
}