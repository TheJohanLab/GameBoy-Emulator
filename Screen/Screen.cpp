#include "Screen.h"
#include <iostream>

Screen::Screen(u16 width, u16 height)
	:mWidth(width), mHeight(height)
{
	initScreen();
}

Screen::~Screen()
{
	std::cout << "Screen destructor\n";
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

int Screen::initScreen()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Error: Couldn't initialize SDL Video = " << SDL_GetError() << std::endl;
		return 1;
	}
	else
	{

		//Create the window.
		mWindow = SDL_CreateWindow("Gameboy emulator",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 160, 144, 0);
		if (mWindow == nullptr)
		{
			std::cout << "Error: Couldn't create window = " << SDL_GetError() << std::endl;
			return 1;
		}
		else
		{
			//Create a renderer for GPU accelerated drawing.
			mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED |
				SDL_RENDERER_PRESENTVSYNC);
			if (mRenderer == nullptr) {
				std::cout << "Error: Couldn't create renderer = " << SDL_GetError() << std::endl;
				return 1;
			}
			else {
				//Ensure transparent graphics are drawn correctly.
				SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);

				//Output the name of the render driver.
				SDL_RendererInfo rendererInfo;
				SDL_GetRendererInfo(mRenderer, &rendererInfo);
				std::cout << "Renderer = " << rendererInfo.name << std::endl;
			}
		}
	}
}


const SDL_Window* Screen::getWindow() const 
{
	return mWindow;
}

const SDL_Renderer* Screen::getRenderer() const 
{
	return mRenderer;
}