#include "pch.h"

#include "ImGuiHandler.h"
#include "CPU/CPU.h"
#include "PPU/PPU.h"

#include <regex>

ImGuiHandler::ImGuiHandler( SDL_Window* window, SDL_Renderer* renderer)
{
	mImGuiRenderer = std::make_unique<ImGuiRenderer>(window, renderer);

	//callbacks
	mImGuiRenderer->setOnStepModeCallback(BIND_FUNC_1_ARG(this, ImGuiHandler::setStepMode));
	mImGuiRenderer->setOnGotoModeCallback(BIND_FUNC_1_ARG(this, ImGuiHandler::setGotoMode));
	mImGuiRenderer->setOnRomLoadedCallback(BIND_FUNC_1_ARG(this, ImGuiHandler::loadRom));
	mImGuiRenderer->setOnQuitCallback(BIND_FUNC_NO_ARGS(this, ImGuiHandler::quit));
}

void ImGuiHandler::setOnStepModeCallback(onSetModeCallback callback)
{
	mOnSetMode = callback;
}

void ImGuiHandler::setOnGotoModeCallback(onGotoModeCallback callback)
{
	mOnGotoMode = callback;
}

void ImGuiHandler::setOnRomLoadedCallback(onRomLoaded callback)
{
	mOnRomLoaded = callback;
}

void ImGuiHandler::setOnLoadCartridgeCallback(onCartridgeLoaded callback)
{
	mOnCartridgeLoaded = callback;
}

void ImGuiHandler::setOnQuitCallback(onRomLoaded callback)
{
	mOnQuit = callback;
}



void ImGuiHandler::setRegistriesReference(std::shared_ptr<Registries> registries)
{
	mImGuiRenderer->setRegistriesReference(registries);
}

void ImGuiHandler::setCPUReference(std::shared_ptr<CPU> cpu)
{
	mImGuiRenderer->setCPUReference(cpu);
}

void ImGuiHandler::setPPUReference(std::shared_ptr<PPU> ppu)
{
	mImGuiRenderer->setPPUReference(ppu);
}

void ImGuiHandler::setOpcodeReference(std::shared_ptr<u8> opcode)
{
	mImGuiRenderer->setOpcodeReference(opcode);
}

void ImGuiHandler::setMemoryReference(std::shared_ptr<const Memory> memory)
{
	mImGuiRenderer->setMemoryReference(memory);
}

void ImGuiHandler::setCartridgeReference(std::shared_ptr<const Cartridge> cartridge)
{
	mImGuiRenderer->setCartridgeReference(cartridge);
}


void ImGuiHandler::setStepMode(bool stepMode)
{
	mOnSetMode(stepMode ? EmulatorState::STEP : EmulatorState::RUN);
}

void ImGuiHandler::setGotoMode(std::string& inputBuffer)
{
	if (!isValidHex16(inputBuffer)) {
		GBE_LOG_ERROR("Invalid format. Please enter a correct 16 bits hex value : {0}\n", 
			inputBuffer.c_str());

		mOnSetMode(EmulatorState::STEP);
		return;
	}

	mOnGotoMode(convertToU16(inputBuffer));
}

void ImGuiHandler::render()
{
	mImGuiRenderer->render();
}


bool ImGuiHandler::isValidHex16(const std::string& input) {
	std::regex hexPattern("^(0x|0X)?[0-9a-fA-F]{1,4}$");
	return std::regex_match(input, hexPattern);
}

uint16_t ImGuiHandler::convertToU16(const std::string& input) {
	u16 value;
	std::stringstream ss;
	ss << std::hex << input;
	ss >> value;
	return value;
}

void ImGuiHandler::loadRom(bool reload)
{
	if (!reload)
	{
		mRomFilePath.clear();
		mRomFilePath = openFileDialog();
	}

	if (!mRomFilePath.empty()) {
		loadFile(mRomFilePath);
	}
	else
		GBE_LOG_ERROR("Error, no rom loaded. Load a ROM first");
}

void ImGuiHandler::quit() const
{
	mOnQuit();
}


std::wstring ImGuiHandler::openFileDialog() const
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

void ImGuiHandler::loadFile(const std::wstring& filePath) const
{
	//printRomInHex(filePath);
	mOnCartridgeLoaded(filePath);
	mOnRomLoaded(); // TODO Remove this callback and merge it with the previous one


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

std::string ImGuiHandler::wstringToString(const std::wstring& wstr) const
{
	// Convertir wchar_t* vers char*
	std::string str(wstr.begin(), wstr.end());
	return str;
}