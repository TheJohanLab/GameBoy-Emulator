#pragma once

#include <windows.h> 
#include <commdlg.h>
#include <cstring> 

#include "ImGuiRenderer.h"
#include "Emulator/States/EmulatorBaseState.h"
#include "Registries/Registries.h"
#include "Cartridge/Cartridge.h"

class CPU;
class PPU;

class ImGuiHandler
{


private:
	std::unique_ptr<ImGuiRenderer> mImGuiRenderer{nullptr};
	std::shared_ptr<Cartridge> mCartridge;

	std::wstring mRomFilePath;

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
	std::wstring openFileDialog() const;
	void loadFile(const std::wstring& filePath) const;
	std::string wstringToString(const std::wstring& wstr) const;

	bool isValidHex16(const std::string& input);
	u16 convertToU16(const std::string& input);

	void loadRom(bool reload);

//callbacks
private:
	using onSetModeCallback = std::function<void(EmulatorState)>;
	using onGotoModeCallback = std::function<void(u16)>;
	using onRomLoaded = std::function<void()>;

	onSetModeCallback mOnSetMode{ nullptr };
	onGotoModeCallback mOnGotoMode{ nullptr };
	onRomLoaded mOnRomLoaded{ nullptr };

public:
	void setOnStepModeCallback(onSetModeCallback callback);
	void setOnGotoModeCallback(onGotoModeCallback callback);
	void setOnRomLoadedCallback(onRomLoaded callback);
};