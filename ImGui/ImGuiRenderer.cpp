#include "pch.h"

#include "ImGuiRenderer.h"
//#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"

#include "Cartridge/CartridgeManager.h"
#include "Cartridge/Cartridge.h"

#include "Registries/Registries.h"

#include "Timer/Timer.h"


//#include <string>
//#include "Emulator/Emulator.h"
#include "CPU/CPU.h"

std::string ImGuiRenderer::mOpcodeDescription{ "NOP" };

ImGuiRenderer::ImGuiRenderer(SDL_Window* window, SDL_Renderer* renderer)
	:mWindow(window), mRenderer(renderer)
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
				mOnRomLoaded(false);
			
			if (ImGui::MenuItem("Reload", "Ctrl+R"))
				mOnRomLoaded(true);
			
			if (ImGui::MenuItem("Quit", "Ctrl+Q"))
				mOnQuit();

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Tools"))
		{
			if (ImGui::MenuItem("Enable Step Debugging", nullptr, mStepMode))
			{
				mStepMode = !mStepMode;
				mOnStepMode(mStepMode);
			}

			if (ImGui::Button("Goto address"))
			{
				ImGui::OpenPopup("goto");
				mShowGotoPopup = true;
			}

			std::string inputBuffer;
			renderGotoPopUp(inputBuffer);
			
			ImGui::EndMenu();
		}
		
		if (ImGui::MenuItem("Registries", nullptr, mShowRegistries)) 
		{
			mShowRegistries = !mShowRegistries;
		}
		if (ImGui::MenuItem("Data", nullptr, mShowEmulatorData)) 
		{
			mShowEmulatorData = !mShowEmulatorData;
		}

		if (ImGui::BeginMenu("About"))
		{
			if (ImGui::MenuItem("Show Demo Window")) {
				mShow_demo_window = !mShow_demo_window;
			}
			ImGui::EndMenu();
		}



		if (ImGui::MenuItem("Memory", nullptr, mShowMemory))
		{
			mShowMemory = !mShowMemory;
		}



		ImGui::EndMainMenuBar();
	}



	if (mShow_demo_window)
		ImGui::ShowDemoWindow(&mShow_demo_window);

	renderDataWindows();
	renderMemory();

	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), mRenderer);
}

void ImGuiRenderer::renderDataWindows() const
{
	float mainMenuHeight = 0.0f;
	if (ImGui::BeginMainMenuBar()) {
		mainMenuHeight = ImGui::GetWindowSize().y;
		ImGui::EndMainMenuBar();
	}

	ImVec2 screenSize = ImGui::GetIO().DisplaySize;
	ImVec2 windowSize1 = ImVec2(screenSize.x * 0.35f, screenSize.y * 0.30f - mainMenuHeight);
	ImVec2 windowSize2 = ImVec2(screenSize.x * 0.35f, screenSize.y * 0.20f - mainMenuHeight);

	ImVec2 pos1 = ImVec2(screenSize.x * 0.65f, mainMenuHeight);
	ImVec2 pos2 = ImVec2(screenSize.x * 0.65f, screenSize.y * 0.30f);

	if (!mShowRegistries && mShowEmulatorData) 
		pos2 = pos1;
	
	renderRegistries(pos1, windowSize1);
	renderEmulatorData(pos2, windowSize2);
}

void ImGuiRenderer::renderRegistries(const ImVec2& pos, const ImVec2& size) const
{
	if (mShowRegistries) 
	{

		ImGui::SetNextWindowPos(pos);
		ImGui::SetNextWindowSize(size);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
		
		auto registries = mRegistries->getRegistriesRef();

		ImGui::Begin("Registries");
		ImGui::Text("A: 0x%X", (registries[Reg::A].get()));
		ImGui::SameLine();
		ImGui::Text("F: 0x%X", (registries[Reg::F].get()));
		ImGui::Text("B: 0x%X", (registries[Reg::B].get()));
		ImGui::SameLine();
		ImGui::Text("C: 0x%X", (registries[Reg::C].get()));
		ImGui::Text("D: 0x%X", (registries[Reg::D].get()));
		ImGui::SameLine();
		ImGui::Text("E: 0x%X", (registries[Reg::E].get()));
		ImGui::Text("H: 0x%X", (registries[Reg::H].get()));
		ImGui::SameLine();
		ImGui::Text("L: 0x%X", (registries[Reg::L].get()));
		ImGui::Text("Flags");
		ImGui::Text("C: 0x%X", (mRegistries->getFlagsRef().flags.C));
		ImGui::SameLine();
		ImGui::Text("H: 0x%X", (mRegistries->getFlagsRef().flags.H));
		ImGui::Text("N: 0x%X", (mRegistries->getFlagsRef().flags.N));
		ImGui::SameLine();
		ImGui::Text("Z: 0x%X", (mRegistries->getFlagsRef().flags.Z));
		ImGui::Text("LCD STAT: 0x%X", (mMemoryRef->read(LCD_STATUS)));
		ImGui::Text("TIMER :");
		ImGui::Text("TIMA: 0x%X", (mTimerRef->getTIMA()));
		ImGui::SameLine();
		ImGui::Text("TMA: 0x%X", (mTimerRef->getTMA()));
		ImGui::SameLine();
		ImGui::Text("TAC: 0x%X", (mTimerRef->getTAC().raw));
		ImGui::Text("clock select: 0x%X", (mTimerRef->getTAC().bits.clock_select));
		ImGui::SameLine();
		ImGui::Text("enable: 0x%X", (mTimerRef->getTAC().bits.enable));
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
		ImGui::Text("PC:     0x%X", CPU::getCurrPC()); //TODO Change this static mPC to a private variable
		ImGui::Text("OpCode: %s", mOpcodeDescription.c_str());
		ImGui::Text("Next Opcodes:  %s", mCPURef->getNextOpcodesValue().c_str());
		ImGui::Text("SP:     0x%X", *(mCPURef->getSP()));

		ImGui::End();

		ImGui::PopStyleColor();
	}
}


void ImGuiRenderer::renderMemory()
{
	if (!mShowMemory)
		return;

	float mainMenuHeight = 0.0f;
	if (ImGui::BeginMainMenuBar()) {
		mainMenuHeight = ImGui::GetWindowSize().y;
		ImGui::EndMainMenuBar();
	}

	ImGui::SetNextWindowPos(ImVec2(0, mainMenuHeight));
	ImGui::SetNextWindowSize(ImVec2(500, 350 - mainMenuHeight));


	ImGui::Begin("Memory");

	bool search = ImGui::InputText(" ", mSearchBuffer, IM_ARRAYSIZE(mSearchBuffer), ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_EnterReturnsTrue);
	ImGui::SameLine();
	if (ImGui::Button("Search") || search) 
	{
		mSearchAddress = std::strtol(mSearchBuffer, nullptr, 16);
		mSearchScrolled = false;
	}

	ImGui::Separator();

	if (ImGui::BeginTable("MemoryTable", 17, ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollY)) 
	{
		ImGui::TableSetupColumn("Address", ImGuiTableColumnFlags_WidthFixed, 70.0f); 
		for (int i = 0; i < 16; i++) 
		{
			ImGui::TableSetupColumn((std::stringstream() << std::uppercase << std::hex << i).str().c_str());
		}
		ImGui::TableHeadersRow();

		//ROM (Cartridge)
		const auto& romData = mCartridgeRef->getROMData();
		for (u16 rowStart = 0; rowStart < CARTRIDGE_MEMORY_SIZE; rowStart += 16)
		{
			auto currAddr = rowStart;
			bool highlight = (mSearchAddress >= currAddr && mSearchAddress < currAddr + 16);
		
			ImGui::TableNextRow();
		
			if (highlight && !mSearchScrolled)
			{
				mSearchScrolled = true;
				ImGui::SetScrollHereY(0.5f);
			}
		
			ImGui::TableSetColumnIndex(0);
			if (highlight)
				ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, IM_COL32(255, 255, 0, 50));
		
			std::string sectionName = currAddr < 0x4000 ? "ROM0" : "ROM1";
			ImGui::Text("%s: %04X", sectionName.c_str(), currAddr);
		
			for (int i = 0; i < 16; i++)
			{
				u16 index = rowStart + i;
				if (index >= romData.size())
					break;
		
				ImGui::TableSetColumnIndex(i + 1);
				if (currAddr + i == mSearchAddress)
					ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(255, 0, 0, 100));
		
				ImGui::Text("%02X", romData[index]);
		
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Adresse: 0x%04X", currAddr + i);
			}

		}

		//RAM
		for (const auto& [sectionName, memoryRegion] : mMemoryRef->getMemoryRegions()) 
		{
			for (u16 rowStart = 0; rowStart < memoryRegion.size; rowStart += 16) 
			{
				auto currAddr = rowStart + memoryRegion.offset;
				bool highlight = (mSearchAddress >= currAddr && mSearchAddress < currAddr + 16);

				ImGui::TableNextRow();

				if (highlight && !mSearchScrolled)
				{
					mSearchScrolled = true;
					ImGui::SetScrollHereY(0.5f); //  Scroll to the searching line
				}
					 
				ImGui::TableSetColumnIndex(0);
				if (highlight) 
					ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, IM_COL32(255, 255, 0, 50)); // Yellow highlight whole row
				
				ImGui::Text("%s: %04X", sectionName.c_str(), currAddr); 

				for (int i = 0; i < 16; i++) 
				{
					u16 index = rowStart + i;
					if (index >= memoryRegion.size)
						break;

					ImGui::TableSetColumnIndex(i + 1);
					if (currAddr + i == mSearchAddress) 
						ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(255, 0, 0, 100)); // Red highlight for search
					
					ImGui::Text("%02X", *(mMemoryRef->getMemoryRegionData(memoryRegion) + index));

					// Tooltip on hover
					if (ImGui::IsItemHovered()) 
						ImGui::SetTooltip("Adresse: 0x%04X", currAddr + i);
					
				}
			}
		}

		ImGui::EndTable();
	}

	ImGui::End();

}


void ImGuiRenderer::renderGotoPopUp(std::string& input)
{
	if (ImGui::BeginPopup("goto") && mShowGotoPopup)
	{
	
		ImGui::Text(" Enter a 16 bit hex address you want to go to :");
		if (ImGui::InputText("GOTO address", mGotoAddrbuffer, IM_ARRAYSIZE(mGotoAddrbuffer), ImGuiInputTextFlags_EnterReturnsTrue)
			|| ImGui::Button("Accept"))
		{
			input = std::string(mGotoAddrbuffer);
			mShowGotoPopup = false;
			ImGui::CloseCurrentPopup();
			mStepMode = true;
			mOnGotoMode(input);
		}

		ImGui::SameLine();

		if (ImGui::Button("Cancel")) {
			mShowGotoPopup = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}


void ImGuiRenderer::processEvent(SDL_Event* event) const
{
	ImGui_ImplSDL2_ProcessEvent(event);
}

void ImGuiRenderer::setRegistriesReference(const Registries & registries)
{
	mRegistries = &registries;
}

void ImGuiRenderer::setCPUReference(const std::shared_ptr<CPU> cpu)
{
	mCPURef = cpu;
}

void ImGuiRenderer::setPPUReference(const std::shared_ptr<PPU> ppu)
{
	mPPURef = ppu;
}

void ImGuiRenderer::setOpcodeReference(std::shared_ptr<u8> opcode)
{
	mOpcodeValue = opcode;
}

void ImGuiRenderer::setMemoryReference(std::shared_ptr<const Memory> memory)
{
	mMemoryRef = memory;
}

void ImGuiRenderer::setCartridgeReference(std::shared_ptr<const Cartridge> cartridge)
{
	mCartridgeRef = cartridge;
}

void ImGuiRenderer::setTimerReferences(std::shared_ptr<const Timer> timer)
{
	mTimerRef = timer;
}


void ImGuiRenderer::setOpcodeDesc(const std::string& description)
{
	mOpcodeDescription = description;
}


void ImGuiRenderer::setOnStepModeCallback(onStepMode callback)
{
	mOnStepMode = callback;
}

void ImGuiRenderer::setOnGotoModeCallback(onGotoMode callback)
{
	mOnGotoMode = callback;
}

void ImGuiRenderer::setOnRomLoadedCallback(onRomLoaded callback)
{
	mOnRomLoaded = callback;
}

void ImGuiRenderer::setOnQuitCallback(onQuit callback)
{
	mOnQuit = callback;
}
