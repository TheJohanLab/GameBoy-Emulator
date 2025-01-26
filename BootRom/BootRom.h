#pragma once



//#include <vector>
//#include <memory>
//#include <functional>

//#include "Utils/Utils.h"
#include "Emulator/States/EmulatorBaseState.h"

class PPU;
class Bus;
class CPU;

class BootRom
{
	using onStateChange = std::function<void(EmulatorState)>;

private:
	std::shared_ptr<Bus> mBus;
	std::shared_ptr<PPU> mPPU;
	std::weak_ptr<CPU> mCPU_weak;
	std::vector<u8> mExtractedBootLogo;

	bool mIsBootFinished{ false };
	u8 mScrollingIter{ 0 };
	u8 mVBLankCnt{ 0 };
	u8 DEBUG_SCROLL_LOGO_IT{ 0 };
	const u16 mTotalScrollingIter{ 0x64 };
	//const u16 mTotalScrollingIter{ 0x1 };

	onStateChange mOnStateChange{ nullptr };
	
public:
	BootRom(std::shared_ptr<Bus> bus, std::shared_ptr<PPU> ppu, std::weak_ptr<CPU> cpu_weak);
	~BootRom();

	void initializeBootRom();
	void execute();
	void scrollLogo();

	void setStateCallback(onStateChange callback) { mOnStateChange = callback; }

private:

	void extractBootLogo();
	void convertToTile(const u16 tileRawBytes);
	void initRegistries();


};

//duplicateBis  : CE ED -> F0 FC FC F3
//upscalePixels : F0 F0 F0 F0 FC FC FC FC FC FC FC FC F3 F3 F3 F3