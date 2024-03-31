#pragma once
#include "SDL.h"
#include "../Utils/Utils.h"

class Screen
{
	private:
		u16 mWidth;
		u16 mHeight;

		SDL_Renderer* mRenderer;
		SDL_Window* mWindow;

	public:
		Screen(u16 width, u16 height);
		~Screen();

		const SDL_Window* getWindow() const;
		const SDL_Renderer* getRenderer() const;


	private:

		int initScreen();

};

