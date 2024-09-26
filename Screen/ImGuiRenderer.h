#pragma once

#include <SDL.h>
#include <fstream>
#include <windows.h> 
#include <commdlg.h>
#include <cstring> 

class ImGuiRenderer
{
private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

public:
	ImGuiRenderer(SDL_Window* window, SDL_Renderer* renderer);
	~ImGuiRenderer();

	void render() ;
	void processEvent(SDL_Event* event) const;
		

private:
	void initImGui() const;

	std::wstring openFileDialog() const;
	void loadFile(const std::wstring& filePath) const;
	std::string wstringToString(const std::wstring& wstr) const;
	bool mShow_demo_window = false;
};