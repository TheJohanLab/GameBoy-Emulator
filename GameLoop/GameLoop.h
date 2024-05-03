#pragma once

#include "../CPU/CPU.h"
#include "../PPU/PPU.h"
#include "../Utils/Utils.h"
#include <SDL.h>

class GameLoop
{
private:
	CPU mCPU;
	PPU* mPPU;
	bool mIsRunning;
	bool mIsPaused;

	Uint64 mFrameStart;
	Uint64 mFrameEnd;

public:
	GameLoop(CPU & cpu, PPU * ppu);
	virtual ~GameLoop() = default;

	void startGame();
	void stopGame() { mIsRunning = false; }
	void pauseGame() { mIsPaused = true; }
	void resumeGame() { mIsPaused = false; }

private:
	void handleFrame(u32 & cycle);
	u8 step();
	void synchroniseFrame();
};

