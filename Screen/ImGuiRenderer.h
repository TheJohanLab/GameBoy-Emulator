#pragma once

#include <SDL.h>
//#include <fstream>
#include <windows.h> 
#include <commdlg.h>
#include <cstring> 
//#include <memory>

#include "Cartridge/Cartridge.h"
#include "Registries/Registries.h"


class ImGuiRenderer
{
private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	Cartridge* mCartridge;

	Registries* mRegistries = nullptr;

	bool mShowRegistries = false;

public:
	ImGuiRenderer(Cartridge* mCartridge, SDL_Window* window, SDL_Renderer* renderer);
	~ImGuiRenderer();

	void render() ;
	void renderRegistries() const;
	void processEvent(SDL_Event* event) const;
		
	void setRegistries(Registries* registries);

private:
	void initImGui() const;

	std::wstring openFileDialog() const;
	void loadFile(const std::wstring& filePath) const;
	std::string wstringToString(const std::wstring& wstr) const;
	bool mShow_demo_window = false;
};