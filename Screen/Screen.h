#pragma once

#include <array>
#include "SDL.h"
#include "../Utils/Utils.h"

class Pixel;

class Screen
{
	private:
		u16 mWidth;
		u16 mHeight;

		SDL_Renderer* mRenderer;
		SDL_Window* mWindow;
		SDL_Texture* mTexture;

	public:
		Screen(u16 width, u16 height);
		~Screen();

		const SDL_Window* getWindow() const;
		const SDL_Renderer* getRenderer() const;


		//void render() const;
		void render(std::array<std::array<Pixel, SCREEN_WIDTH>, SCREEN_HEIGHT>& pixelArray) const;

	private:
		int initScreen();

};

