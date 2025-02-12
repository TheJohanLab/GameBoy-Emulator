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

using closeEventFn = std::function<void()>;

class Screen
{
	private:
		//std::shared_ptr<ImGuiRenderer> mImGuiRenderer;
		//std::shared_ptr<WindowEventManager> mEventManager;

		u16 mWidth;
		u16 mHeight;

		SDL_Renderer* mRenderer;
		SDL_Window* mWindow;
		SDL_Texture* mTexture;
		SDL_Event mEvent;

		closeEventFn closeEventCallback;


	public:
		Screen(u16 width, u16 height);
		~Screen();

		SDL_Window* getWindow();
		SDL_Renderer* getRenderer();


		void startRendering() const;
		//void startRendering(u8* pixelArray) const;
		void startRendering(std::array<std::array<Pixel, SCREEN_WIDTH>, SCREEN_HEIGHT>& pixelArray) const;
		void render() const;
		//inline void renderImGui() const;

		void setOnCloseEvent(closeEventFn callback);

	private:
		int initScreen();
		//void initImGui(SDL_Window* window, SDL_Renderer* renderer);

};

