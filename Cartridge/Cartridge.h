#pragma once
//#include <memory>
//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include <string>
//#include <sstream>

//#include <vector>
#include "Utils/Utils.h"

#include <functional>

class Cartridge
{
using loadCallback = std::function<void()>;

private:
	std::vector<u8> mROMData;

	loadCallback mLoadCartridgeCallback = nullptr;
public:
	Cartridge() {}
	//Cartridge(std::shared_ptr<Bus> bus);

	void loadCartridge(const std::wstring& filePath);

	void setLoadCallback(std::function<void()> callback);

	u8 read(u16 address) const;
	u8& read(u16 address);


	const std::vector<u8>& getROMData() const { return mROMData; }


};