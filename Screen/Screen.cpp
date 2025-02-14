#include "pch.h"

#include "Screen.h"
//#include <iostream>

#include "PPU/PPU.h"
//#include "ImGui/ImGuiHandler.h"

Screen::Screen(u16 width, u16 height)
	:mWidth(width), mHeight(height)
{
	//TODO remove cartridge from Screen
	initScreen();
	//mImGuiRenderer = std::make_shared<ImGuiRenderer>(cartridge, mWindow, mRenderer);
}

Screen::~Screen()
{
	std::cout << "Screen destructor\n";

	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyTexture(mTexture);
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
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
			SCREEN_WIDTH * 5,
			SCREEN_HEIGHT * 5, 
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

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
			
				//ARGB format


			}

			mTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_BGRA8888, SDL_TEXTUREACCESS_STREAMING, 160, 144);
			if (mTexture == nullptr) {
				// Handle error
				SDL_Log("Failed to create texture: %s", SDL_GetError());
				return 1;
			}
		}
	}
	
	return 0;
}


SDL_Window* Screen::getWindow()
{
	return mWindow;
}

SDL_Renderer* Screen::getRenderer()
{
	return mRenderer;
}


void Screen::startRendering() const
{
	SDL_RenderClear(mRenderer);
}

void Screen::startRendering( std::array<std::array<Pixel, SCREEN_WIDTH>, SCREEN_HEIGHT>& pixelArray) const
{

	SDL_RenderClear(mRenderer);
	//SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	u8* pPixels;
	int pitch = 0;

	//SDL_LockTexture(mTexture, nullptr, (void**)&pixelArray, &pitch);
	SDL_LockTexture(mTexture, nullptr, (void**)&pPixels, &pitch);
	memcpy(pPixels, static_cast<void const*>(&pixelArray), SCREEN_WIDTH * SCREEN_HEIGHT * 4);
	SDL_UnlockTexture(mTexture);
	SDL_RenderCopy(mRenderer, mTexture, nullptr, nullptr);

	//renderImGui();

	
}

void Screen::render() const
{
	SDL_RenderPresent(mRenderer);
}


