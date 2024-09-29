#include "ImGuiRenderer.h"
#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"

#include "Cartridge/CartridgeManager.h"
#include "Cartridge/Cartridge.h"

#include <string>
#include "Emulator/Emulator.h"

ImGuiRenderer::ImGuiRenderer(Cartridge* cartridge, SDL_Window* window, SDL_Renderer* renderer)
	:mCartridge(cartridge), mWindow(window), mRenderer(renderer)
{
	initImGui();
}

ImGuiRenderer::~ImGuiRenderer()
{
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiRenderer::initImGui()const
{
	// Initialiser ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// Initialiser le backend SDL2 pour la gestion des evenements (souris/clavier)
	ImGui_ImplSDL2_InitForSDLRenderer(mWindow, mRenderer);

	// Initialiser le backend SDL_Renderer2 pour le rendu
	ImGui_ImplSDLRenderer2_Init(mRenderer);

	ImGui::StyleColorsDark();
}

void ImGuiRenderer::render()
{
	// Commencer un nouveau frame ImGui
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	
	std::string loadedFilePath = "";

	// Créer une barre de menu en haut
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Load", "Ctrl+L"))
			{
				// Ouvrir une boîte de dialogue de sélection de fichier
				auto filePath = openFileDialog();
				if (!filePath.empty()) {
					loadedFilePath = wstringToString(filePath);
					loadFile(filePath);  // Lire et traiter le fichier
				}
			}
			if (ImGui::MenuItem("Quit", "Ctrl+Q")) {
				
			}
			ImGui::EndMenu();
		}
		//if (ImGui::BeginMenu("Edit"))
		//{
		//	ImGui::EndMenu();
		//}
		if (ImGui::BeginMenu("About"))
		{
			if (ImGui::MenuItem("Show Demo Window")) {
				mShow_demo_window = !mShow_demo_window;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	if (mShow_demo_window)
		ImGui::ShowDemoWindow(&mShow_demo_window);

	// Finir et rendre le frame ImGui
	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), mRenderer);
}

void ImGuiRenderer::processEvent(SDL_Event* event) const
{
	ImGui_ImplSDL2_ProcessEvent(event);
}


std::wstring ImGuiRenderer::openFileDialog() const
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

void ImGuiRenderer::loadFile(const std::wstring& filePath) const
{
	mCartridge->loadCartridge(filePath);
	//printRomInHex(filePath);
	
	//std::wifstream file(filePath); // Utiliser wifstream pour les fichiers en Unicode
	//if (file.is_open()) {
	//	std::wstring line;
	//	while (std::getline(file, line)) {
	//		std::wcout << line << std::endl;
	//	}
	//	file.close();
	//}
	//else {
	//	std::wcerr << L"Erreur lors de l'ouverture du fichier : " << filePath << std::endl;
	//}
}

std::string ImGuiRenderer::wstringToString(const std::wstring& wstr) const
{
	// Convertir wchar_t* vers char*
	std::string str(wstr.begin(), wstr.end());
	return str;
}
