#pragma once

//#include <functional>
//#include <SDL.h>

#include "CPU/CPU.h"
#include "PPU/PPU.h"
#include "BootRom/BootRom.h"
#include "Emulator/States/EmulatorStateFactory.h"
//#include "ImGui/ImGuiHandler.h"
//#include "Utils/Utils.h"

class WindowEventManager;
class ImGuiHandler;

class GameLoop
{
private:
	std::shared_ptr<CPU> mCPU;
	std::shared_ptr<PPU> mPPU;
	std::shared_ptr<BootRom> mBootRom;
	std::shared_ptr<Screen> mScreen;

	std::unique_ptr<EmulatorStateFactory> mStateFactory;
	std::shared_ptr<EmulatorBaseState> mCurrentEmulatorState{ nullptr };

	std::shared_ptr<ImGuiHandler> mImGuiHandler{ nullptr };
	std::shared_ptr<WindowEventManager> mWindowEventManager{ nullptr };

	bool mIsRunning;
	bool mIsPaused;

	Uint64 mFrameStart;
	Uint64 mFrameEnd;

	u32 mCycles{ 0 };

	std::vector<std::function<void()>> mSequence;
	static u16 waitingDots;

	bool mIsCartridgeLoaded{ false };

	u8 mCurrentOpcode;
	static EmulatorState mInitCurrState;
	u16 mGotoAddress{ 0x0000 };


public:
	GameLoop(std::shared_ptr<CPU> cpu, std::shared_ptr<PPU> ppu, std::shared_ptr<ImGuiHandler> imGui);
	virtual ~GameLoop() = default;

	void setEmulatorState(EmulatorState state);
	void setEmulatorStateStep(EmulatorState state);
	void setEmulatorStateGoto(u16 address);

	void startGame();
	void stopGame() { mIsRunning = false; }
	void pauseGame() { mIsPaused = true; }
	void resumeGame() { mIsPaused = false; }

	void setCartridgeLoaded();


	void addToSequence(std::function<void()> task);
	void endSequence();

	void waitForNextFrame();

	static void addVirtualWaitingDots(u16 dots);
	static void decVirtualWaitingDots(u16 dots);

	static EmulatorState getCurrentEmulatorState() { return mInitCurrState; }

private:
	inline void setCallbacks();

	inline void handleFrame();
	inline void handleBootFrame();
	inline void handleScreenFrame();
	inline u8 step();
	inline u8 bootStep();
	inline void synchroniseFrame();
	inline void render(std::array<std::array<Pixel, SCREEN_WIDTH>, SCREEN_HEIGHT>& pixelArray);
	inline void logInfos() const;
	//inline void render(u8* pixelArray);
};

