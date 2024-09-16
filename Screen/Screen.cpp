#include "Screen.h"
#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"

#include "../PPU/PPU.h"


#include <fstream>
#include <windows.h> 
#include <commdlg.h>
#include <cstring> // Pour memset()
#include <string>

std::wstring OpenFileDialog()
{
	wchar_t filename[MAX_PATH];
	OPENFILENAMEW ofn; // Utilisation de la version W (Unicode)

	memset(&filename, 0, sizeof(filename));
	memset(&ofn, 0, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"Tous les fichiers\0*.*\0Fichiers texte\0*.TXT\0"; // Utiliser des chaînes Unicode
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
	ofn.lpstrDefExt = L"txt"; // Extension par défaut en Unicode

	std::wstring filePath;

	// Utiliser la version Unicode de GetOpenFileName
	if (GetOpenFileNameW(&ofn)) {
		filePath = filename;
	}
	else {
		std::wcout << L"Aucun fichier sélectionné ou erreur lors de la sélection." << std::endl;
	}

	return filePath;
}

void LoadFile(const std::wstring& filePath) {
	std::wifstream file(filePath); // Utiliser wifstream pour les fichiers en Unicode
	if (file.is_open()) {
		std::wstring line;
		while (std::getline(file, line)) {
			std::wcout << line << std::endl;
		}
		file.close();
	}
	else {
		std::wcerr << L"Erreur lors de l'ouverture du fichier : " << filePath << std::endl;
	}
}

std::string wstringToString(const std::wstring& wstr) {
	// Convertir wchar_t* vers char*
	std::string str(wstr.begin(), wstr.end());
	return str;
}

Screen::Screen(u16 width, u16 height)
	:mWidth(width), mHeight(height)
{
	initScreen();
}

Screen::~Screen()
{
	std::cout << "Screen destructor\n";

	// Nettoyage d'ImGui
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

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
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 576, 0);
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
	initImGui(mWindow, mRenderer);
	return 0;
}

void Screen::initImGui(SDL_Window* window, SDL_Renderer* renderer)
{
	// Initialiser ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// Initialiser le backend SDL2 pour la gestion des événements (souris/clavier)
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);

	// Initialiser le backend SDL_Renderer2 pour le rendu
	ImGui_ImplSDLRenderer2_Init(renderer);

	// Configuration du style ImGui (facultatif)
	ImGui::StyleColorsDark();
}


const SDL_Window* Screen::getWindow() const 
{
	return mWindow;
}

const SDL_Renderer* Screen::getRenderer() const 
{
	return mRenderer;
}


//void Screen::render() const
void Screen::render( std::array<std::array<Pixel, SCREEN_WIDTH>, SCREEN_HEIGHT>& pixelArray) const
{

	SDL_RenderClear(mRenderer);
	//SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	u8* pPixels;
	int pitch = 0;



	SDL_LockTexture(mTexture, nullptr, (void**)&pPixels, &pitch);

	memcpy(pPixels, static_cast<void const*>(&pixelArray), 160 * 144 * 4);

	SDL_UnlockTexture(mTexture);

	SDL_RenderCopy(mRenderer, mTexture, nullptr, nullptr);

	onImGuiRender();

	SDL_RenderPresent(mRenderer);
}

void Screen::onImGuiRender() const
{
	// Commencer un nouveau frame ImGui
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	bool show_demo_window = false;
	std::string loadedFilePath = "";

	// Créer une barre de menu en haut
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Load", "Ctrl+L"))
			{
				// Ouvrir une boîte de dialogue de sélection de fichier
				auto filePath = OpenFileDialog();
				if (!filePath.empty()) {
					loadedFilePath = wstringToString(filePath);
					LoadFile(filePath);  // Lire et traiter le fichier
				}
			}
			if (ImGui::MenuItem("Quit", "Ctrl+Q")) {
				//done = true;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::MenuItem("Cut", "Ctrl+X");
			ImGui::MenuItem("Copy", "Ctrl+C");
			ImGui::MenuItem("Paste", "Ctrl+V");
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Show Demo Window")) {
				//show_demo_window = !show_demo_window;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// Finir et rendre le frame ImGui
	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), mRenderer);
}

void Screen::setOnCloseEvent(closeEventFn callback)
{
	closeEventCallback = callback;
}

void Screen::handleEvents()
{
	while (SDL_PollEvent(&mEvent) != 0) {
		if (mEvent.type == SDL_QUIT) {
			closeEventCallback();
		}
		ImGui_ImplSDL2_ProcessEvent(&mEvent);
	}
}
