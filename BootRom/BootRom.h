#pragma once

#include <vector>
#include <memory>
#include "Utils/Utils.h"

#include "PPU/PPU.h"
#include "Bus/Bus.h"


class BootRom
{
private:
	std::shared_ptr<Bus> mBus;
	std::shared_ptr<PPU> mPPU;
	std::vector<u8> mExtractedBootLogo;
	
public:
	BootRom(std::shared_ptr<Bus> bus, std::shared_ptr<PPU> ppu);

	void initializeBootRom();

private:

	void extractBootLogo();
	void convertToTile(const u16 tileRawBytes);


};

//duplicateBis  : CE ED -> F0 FC FC F3
//upscalePixels : F0 F0 F0 F0 FC FC FC FC FC FC FC FC F3 F3 F3 F3