#pragma once

#include <SDL.h>
//#include <fstream>
#include <windows.h> 
#include <commdlg.h>
#include <cstring> 
//#include <memory>

class Cartridge;
class Registries;

class ImGuiRenderer
{
private:
	SDL_Window* mWindow{ nullptr };
	SDL_Renderer* mRenderer{ nullptr };

	std::shared_ptr<Cartridge> mCartridge{ nullptr };

	std::shared_ptr<Registries> mRegistries = nullptr;

	bool mShowRegistries{ false };

	static bool mStepMode;

public:
	ImGuiRenderer(std::shared_ptr<Cartridge>, SDL_Window*, SDL_Renderer*);
	~ImGuiRenderer();

	void render() ;
	void renderRegistries() const;
	void processEvent(SDL_Event* event) const;
		
	void setRegistries(std::shared_ptr<Registries>);

	static bool isStepMode();

private:
	void initImGui() const;

	std::wstring openFileDialog() const;
	void loadFile(const std::wstring& filePath) const;
	std::string wstringToString(const std::wstring& wstr) const;
	bool mShow_demo_window = false;
};