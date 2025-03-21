#pragma once

//#include <memory>
//#include <functional>
#include "Registries/IORegistries.h"

class CPU;

enum InterruptsTypes
{
	VBLANK,
	LCD_STAT,
	TIMER,
	SERIAL,
	JOYPAD,
	NONE
};

class InterruptsManager
{
using interrupt = std::function<void()>;

private:
	static std::weak_ptr<CPU> mCPU_weak;

	std::vector<interrupt*> mInterruptsList = std::vector<interrupt*>();
	interrupt mVBlankInterrupt{ nullptr };
	interrupt mSTATInterrupt{ nullptr };
	interrupt mTimerInterrupt{ nullptr };
	interrupt mSerialInterrupt{ nullptr };
	interrupt mJoypadInterrupt{ nullptr };
	interrupt mNone{ nullptr };
	
	interrupt_flag mActiveInterruptFlags{ 0x00 };

public:
	InterruptsManager();
	~InterruptsManager();

	void initInterrupts();
	
	static void setInterrupt(InterruptsTypes type);
	static void setCPU(std::weak_ptr<CPU> cpu);
	
	void clearInterrupts();
	
	void callInterruptHandler();

	void setActiveVBlankInterrupt();

	

private:

	void vblankInterrupt();
	void statInterrupt();
	void timerInterrupt();
	void serialInterrupt();
	void joypadInterrupt();
	void none();

	void getActiveInterruptFlags();
};