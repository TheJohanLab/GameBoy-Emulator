#include "pch.h"

#include "Cartridge.h"

//Cartridge::Cartridge(std::shared_ptr<Bus> bus)
//	:mBus(bus)
//{
//}

void Cartridge::loadCartridge(const std::wstring& filePath)
{
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << std::endl;
        return;
    }

    std::streamsize size = file.tellg(); 
    file.seekg(0, std::ios::beg);
    mROMData.resize(size);

    if (!file.read(reinterpret_cast<char*>(mROMData.data()), size)) {
        std::cerr << "Erreur : impossible de lire le contenu du fichier de la cartouche." << std::endl;
        return;
    }

    //mLoadCartridgeCallback();
}

void Cartridge::setLoadCallback(std::function<void()> callback)
{
    mLoadCartridgeCallback = callback;
}

u8 Cartridge::read(u16 address) const
{
    if (address < mROMData.size()) {
        return mROMData[address];
    }
    else {
        std::cerr << "Erreur : adresse hors de portee lors de la lecture de la cartouche." << std::endl;
        return 0xFF; // valeur de retour par defaut (souvent 0xFF lorsque la lecture est invalide)
    }
}
