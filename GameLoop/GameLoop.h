#pragma once

#include "../CPU/CPU.h"
#include "../Utils/Utils.h"
#include <SDL.h>

class GameLoop
{
private:
	CPU mCPU;
	bool mIsRunning;
	bool mIsPaused;

public:
	GameLoop(CPU & cpu);
	virtual ~GameLoop() = default;

	void startGame();
	void stopGame() { mIsRunning = false; }
	void pauseGame() { mIsPaused = true; }
	void resumeGame() { mIsPaused = false; }

};

