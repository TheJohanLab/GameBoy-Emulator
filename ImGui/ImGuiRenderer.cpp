#include "pch.h"

#include "ImGuiRenderer.h"
//#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"

#include "Cartridge/CartridgeManager.h"
#include "Cartridge/Cartridge.h"

#include "Registries/Registries.h"


//#include <string>
//#include "Emulator/Emulator.h"
#include "CPU/CPU.h"

std::string ImGuiRenderer::mOpcodeDescription{ "" };

ImGuiRenderer::ImGuiRenderer(std::shared_ptr<Cartridge> cartridge, 
							SDL_Window* window, 
							SDL_Renderer* renderer)
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


void ImGuiRenderer::initImGui() const
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
		if (ImGui::BeginMenu("Tools"))
		{
			if (ImGui::MenuItem("Enable Step Debugging", nullptr, mStepMode))
			{
				mStepMode = !mStepMode;
				mOnStepOption(mStepMode);
			}

			if (ImGui::Button("Goto adress"))
			{
				ImGui::OpenPopup("goto");
			}
			//if (ImGui::MenuItem("Goto adress", nullptr, mGotoMode))
			//
			if (ImGui::BeginPopup("goto"))
			{
				char buff[10] = "";
				/*if (ImGui::InputText("Your name?", buff, 4))
				{

				}*/
				ImGui::Text(" Enter a 16 bit hex address you want to go to :");
				ImGui::InputText("##hexInput", buff, IM_ARRAYSIZE(buff), ImGuiInputTextFlags_CharsHexadecimal);

				if (ImGui::Button("Accept")) {
					// Convert to u16
					mShowGotoPopup = false;
					ImGui::CloseCurrentPopup();
				}

				ImGui::SameLine();

				if (ImGui::Button("Cancel")) {
					mShowGotoPopup = false;
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();	
			}
				//mShowGotoPopup = true;
				//char inputBuffer[4] = "";
				//renderGotoPopUp(inputBuffer);
				
				//mGotoMode = !mGotoMode;
				//mStepMode = true;
				//mOnStepOption(true); // STEP mode to be able to use the goto address
				//mOnGotoMode(0x216);
			
			ImGui::EndMenu();
		}
		
		if (ImGui::MenuItem("Registries", nullptr, mShowRegistries)) {
			mShowRegistries = !mShowRegistries;
		}
		if (ImGui::MenuItem("Emulator's Data", nullptr, mShowEmulatorData)) {
			mShowEmulatorData = !mShowEmulatorData;
		}

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

	renderDataWindows();

	// Finir et rendre le frame ImGui
	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), mRenderer);
}

void ImGuiRenderer::renderDataWindows() const
{
	ImVec2 screenSize = ImGui::GetIO().DisplaySize;
	ImVec2 windowSize1 = ImVec2(screenSize.x * 0.35f, screenSize.y * 0.40f);
	ImVec2 windowSize2 = ImVec2(screenSize.x * 0.35f, screenSize.y * 0.20f);

	ImVec2 pos1 = ImVec2(screenSize.x * 0.65f, 0.05f);
	ImVec2 pos2 = ImVec2(screenSize.x * 0.65f, screenSize.y * 0.40f);

	if (!mShowRegistries && mShowEmulatorData) 
		pos2 = pos1;
	
	renderRegistries(pos1, windowSize1);
	renderEmulatorData(pos2, windowSize2);
}

void ImGuiRenderer::renderRegistries(const ImVec2& pos, const ImVec2& size) const
{
	if (mShowRegistries) 
	{
		ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
		ImGui::SetNextWindowSize(size, ImGuiCond_Always);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
		
		ImGui::Begin("Registries");
		ImGui::Text("A: 0x%X", *(mRegistries->getA()));
		ImGui::Text("B: 0x%X", *(mRegistries->getB()));
		ImGui::Text("C: 0x%X", *(mRegistries->getC()));
		ImGui::Text("D: 0x%X", *(mRegistries->getD()));
		ImGui::Text("E: 0x%X", *(mRegistries->getE()));
		ImGui::Text("H: 0x%X", *(mRegistries->getH()));
		ImGui::Text("L: 0x%X", *(mRegistries->getL()));
		ImGui::Text("Flags");
		ImGui::Text("C: 0x%X", (mRegistries->getF()->flags.C));
		ImGui::Text("H: 0x%X", (mRegistries->getF()->flags.H));
		ImGui::Text("N: 0x%X", (mRegistries->getF()->flags.N));
		ImGui::Text("Z: 0x%X", (mRegistries->getF()->flags.Z));

		ImGui::End();

		ImGui::PopStyleColor();
	}
}

void ImGuiRenderer::renderEmulatorData(const ImVec2& pos, const ImVec2& size) const
{
	if (mShowEmulatorData)
	{
		ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
		ImGui::SetNextWindowSize(size, ImGuiCond_Always);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));


		ImGui::Begin("Data");
		ImGui::Text("OpCode: %s", mOpcodeDescription.c_str());
		ImGui::Text("Value:  0x%X", *mOpcodeValue);
		ImGui::Text("PC:     0x%X", *(mCPU->getPC()));
		ImGui::Text("SP:     0x%X", *(mCPU->getSP()));

		ImGui::End();

		ImGui::PopStyleColor();
	}
}

void ImGuiRenderer::renderGotoPopUp(char* input)
{
	//if (mShowGotoPopup)
	//{
		ImGui::OpenPopup("Enter 16 bit hex value");

		if (ImGui::BeginPopupModal("Enter value", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
			ImGui::Text(" (16 bits) :");
			ImGui::InputText("##hexInput", input, IM_ARRAYSIZE(input), ImGuiInputTextFlags_CharsHexadecimal);

			if (ImGui::Button("Accept")) {
				// Convert to u16
				mShowGotoPopup = false;
				ImGui::CloseCurrentPopup();
			}

			ImGui::SameLine();

			if (ImGui::Button("Cancel")) {
				mShowGotoPopup = false;
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();

		}
	//}
}


void ImGuiRenderer::processEvent(SDL_Event* event) const
{
	ImGui_ImplSDL2_ProcessEvent(event);
}

void ImGuiRenderer::setRegistriesReference(std::shared_ptr<Registries> registries)
{
	mRegistries = registries;
}

void ImGuiRenderer::setCPUReference(const std::shared_ptr<CPU> cpu)
{
	mCPU = cpu;
}

void ImGuiRenderer::setPPUReference(const std::shared_ptr<PPU> ppu)
{
	mPPU = ppu;
}

void ImGuiRenderer::setOpcodeReference(std::shared_ptr<u8> opcode)
{
	mOpcodeValue = opcode;
}


void ImGuiRenderer::setOpcodeDesc(const std::string& description)
{
	mOpcodeDescription = description;
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
	//printRomInHex(filePath);
	mCartridge->loadCartridge(filePath);
	
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

void ImGuiRenderer::setOnStepOption(onStepOption callback)
{
	mOnStepOption = callback;
}

void ImGuiRenderer::setOnGotoMode(onGotoMode callback)
{
	mOnGotoMode = callback;
}
