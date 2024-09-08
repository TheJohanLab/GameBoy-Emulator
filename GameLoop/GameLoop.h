#pragma once

#include "../CPU/CPU.h"
#include "../PPU/PPU.h"
#include "../Utils/Utils.h"
#include <SDL.h>

#include <functional>

class GameLoop
{
private:
	CPU* mCPU;
	PPU* mPPU;
	bool mIsRunning;
	bool mIsPaused;

	Uint64 mFrameStart;
	Uint64 mFrameEnd;

	u32 mCycles = 0;

	std::vector<std::function<void()>> mSequence;

public:
	GameLoop(CPU* cpu, PPU* ppu);
	virtual ~GameLoop() = default;

	void startGame();
	void stopGame() { mIsRunning = false; }
	void pauseGame() { mIsPaused = true; }
	void resumeGame() { mIsPaused = false; }

	void addToSequence(std::function<void()> task);
	void endSequence();

	void waitForNextFrame();

private:
	inline void handleFrame();
	inline void handleScreenFrame();
	inline u8 step();
	inline void synchroniseFrame();
};

