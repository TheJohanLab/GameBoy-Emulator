#pragma once

#include <memory>
#include <functional>

class CPU;

enum InterruptsTypes
{
	VBLANK
};

class InterruptsManager
{
using interrupt = std::function<void()>;

private:
	CPU* mCPU;

	std::vector<interrupt> mInterruptsList = std::vector<interrupt>();
	interrupt mVBlankInterrupt{ nullptr };
	interrupt mSTATInterrupt{ nullptr };
	interrupt mTimerInterrupt{ nullptr };
	interrupt mSerialInterrupt{ nullptr };
	interrupt mJoypadInterrupt{ nullptr };
	


public:
	InterruptsManager(CPU* cpu);
	~InterruptsManager();

	void callInterrupt(InterruptsTypes type) const;

	void setActiveVBlankInterrupt();

private:
	void initInterrupts();

	void vblankInterrupt() const;
	void statInterrupt() const;
	void timerInterrupt() const;
	void serialInterrupt() const;
	void joypadInterrupt() const;
};