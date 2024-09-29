#pragma once

#include <array>
#include "SDL.h"
#include "Utils/Utils.h"
#include "ImGuiRenderer.h"
#include <functional>
#include "Cartridge/Cartridge.h"

class Pixel;

enum class WindowEvent
{
	CLOSE_EVENT
};

using closeEventFn = std::function<void()>;

class Screen
{
	private:
		u16 mWidth;
		u16 mHeight;

		SDL_Renderer* mRenderer;
		SDL_Window* mWindow;
		SDL_Texture* mTexture;
		SDL_Event mEvent;

		closeEventFn closeEventCallback;

		std::shared_ptr<ImGuiRenderer> mImGuiRenderer { nullptr };

	public:
		Screen(Cartridge* cartridge, u16 width, u16 height);
		~Screen();

		const SDL_Window* getWindow() const;
		const SDL_Renderer* getRenderer() const;


		//void render() const;
		void render(std::array<std::array<Pixel, SCREEN_WIDTH>, SCREEN_HEIGHT>& pixelArray) const;
		inline void renderImGui() const;

		void setOnCloseEvent(closeEventFn callback);
		void handleEvents();

	private:
		int initScreen();
		void initImGui(SDL_Window* window, SDL_Renderer* renderer);

};

