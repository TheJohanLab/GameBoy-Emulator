#pragma once

#include <SDL.h>
//#include <fstream>
//#include <windows.h> 
//#include <commdlg.h>
//#include <cstring> 
//#include <memory>

#include "Memory/Memory.h"

#include "imgui.h"

class Cartridge;
class Registries;
class CPU;
class PPU;

class ImGuiRenderer
{
private:
	SDL_Window* mWindow{ nullptr };
	SDL_Renderer* mRenderer{ nullptr };

	std::shared_ptr<Registries> mRegistries{ nullptr };
	std::shared_ptr<CPU> mCPURef{ nullptr };
	std::shared_ptr<PPU> mPPURef{ nullptr };

	std::shared_ptr<const Memory> mMemoryRef{ nullptr };
	std::shared_ptr<const Cartridge> mCartridgeRef{ nullptr };
	
	std::shared_ptr<u8> mOpcodeValue{ nullptr };
	static std::string mOpcodeDescription;

	bool mShowRegistries{ false };
	bool mShowEmulatorData{ false };
	bool mShowGotoPopup{ false };
	bool mShowMemory{ false };

	bool mStepMode{ false };
	bool mGotoMode{ false };

	u16 gotoAddressValue{ 0x0000 };
	
	//GOTO address renderer
	char mGotoAddrbuffer[16] = "";


	char mSearchBuffer[10] = "";
	int mSearchAddress{ -1 };
	bool mSearchScrolled{ false };

public:
	ImGuiRenderer(SDL_Window*, SDL_Renderer*);
	~ImGuiRenderer();

	void render() ;
	void renderDataWindows() const;
	void renderRegistries(const ImVec2& pos,const ImVec2& size) const;
	void renderEmulatorData(const ImVec2& pos, const ImVec2& size) const;
	void renderMemory();

	void renderGotoPopUp(std::string& input);
	void processEvent(SDL_Event* event) const;
		
	void setRegistriesReference(std::shared_ptr<Registries>);
	void setCPUReference(const std::shared_ptr<CPU>);
	void setPPUReference(const std::shared_ptr<PPU>);
	void setOpcodeReference(std::shared_ptr<u8>);
	void setMemoryReference(std::shared_ptr<const Memory>);
	void setCartridgeReference(std::shared_ptr<const Cartridge>);

	static void setOpcodeDesc(const std::string&);

private:
	void initImGui() const;

	bool mShow_demo_window = false;

//callbacks
private:
	using onStepMode = std::function<void(bool)>;
	using onGotoMode = std::function<void(std::string&)>;
	using onRomLoaded = std::function<void(bool)>;
	using onQuit = std::function<void()>;


	onStepMode mOnStepMode{ nullptr };
	onGotoMode mOnGotoMode{ nullptr };
	onRomLoaded mOnRomLoaded{ nullptr };
	onQuit mOnQuit{ nullptr };

public:
	void setOnStepModeCallback(onStepMode callback);
	void setOnGotoModeCallback(onGotoMode callback);
	void setOnRomLoadedCallback(onRomLoaded callback);
	void setOnQuitCallback(onQuit callback);
};