#pragma once

//#include <array>
//#include "SDL.h"
//#include "Utils/Utils.h"
//#include "ImGuiRenderer.h"
//#include <functional>
#include "Cartridge/Cartridge.h"
#include "Emulator/WindowEventManager.h"

class Pixel;
class Registries;

enum class WindowEvent
{
	CLOSE_EVENT
};


class Screen
{
	private:

		u16 mWidth;
		u16 mHeight;

		SDL_Renderer* mRenderer;
		SDL_Window* mWindow;
		SDL_Texture* mTexture;
		SDL_Event mEvent;


	public:
		Screen(u16 width, u16 height);
		~Screen();

		SDL_Window* getWindow();
		SDL_Renderer* getRenderer();


		void startRendering() const;
		void startRendering(std::array<std::array<Pixel, SCREEN_WIDTH>, SCREEN_HEIGHT>& pixelArray) const;
		void render() const;

	private:
		int initScreen();

};

