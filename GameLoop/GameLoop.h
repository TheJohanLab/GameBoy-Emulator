#pragma once

#include "../CPU/CPU.h"
#include "../PPU/PPU.h"
#include "../Utils/Utils.h"
#include <SDL.h>

#include <functional>

class GameLoop
{
private:
	std::shared_ptr<CPU> mCPU;
	std::shared_ptr<PPU> mPPU;
	bool mIsRunning;
	bool mIsPaused;

	Uint64 mFrameStart;
	Uint64 mFrameEnd;

	u32 mCycles{ 0 };

	std::vector<std::function<void()>> mSequence;
	static u16 waitingDots;

public:
	GameLoop(std::shared_ptr<CPU> cpu, std::shared_ptr<PPU> ppu);
	virtual ~GameLoop() = default;

	void startGame();
	void stopGame() { mIsRunning = false; }
	void pauseGame() { mIsPaused = true; }
	void resumeGame() { mIsPaused = false; }

	void addToSequence(std::function<void()> task);
	void endSequence();

	void waitForNextFrame();

	static void addVirtualWaitingDots(u16 dots);
	static void decVirtualWaitingDots(u16 dots);

private:
	inline void handleFrame();
	inline void handleScreenFrame();
	inline u8 step();
	inline void synchroniseFrame();
};

