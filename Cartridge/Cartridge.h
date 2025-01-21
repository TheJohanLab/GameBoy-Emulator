#pragma once
//#include <memory>
//#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

//#include <vector>
#include "Utils/Utils.h"

//#include <functional>

class Cartridge
{
using loadCallback = std::function<void()>;

private:
	//std::shared_ptr<Bus> mBus = nullptr;

	std::vector<u8> mROMData;
	std::vector<u8> mRAMData;

	loadCallback mLoadCartridgeCallback = nullptr;
public:
	Cartridge() {}
	//Cartridge(std::shared_ptr<Bus> bus);

	void loadCartridge(const std::wstring& filePath);

	void setLoadCallback(std::function<void()> callback);

	u8 read(u16 address) const;

};