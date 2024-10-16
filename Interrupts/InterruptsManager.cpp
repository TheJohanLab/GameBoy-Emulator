#include "InterruptsManager.h"

#include "CPU/CPU.h"
#include "Utils/Utils.h"
#include "BootRom/BootRom.h"

InterruptsManager::InterruptsManager(CPU* cpu)
	:mCPU(cpu)
{
	initInterrupts();
}

InterruptsManager::~InterruptsManager()
{
	delete mCPU;
}

void InterruptsManager::callInterrupt(InterruptsTypes type) const
{
	mInterruptsList[type]();
}

void InterruptsManager::setActiveVBlankInterrupt()
{
	mVBlankInterrupt = BIND_FUNC_NO_ARGS(this, InterruptsManager::vblankInterrupt);
}

void InterruptsManager::initInterrupts()
{
	mVBlankInterrupt = BIND_FUNC_NO_ARGS(mCPU->getBootRom(), BootRom::scrollLogo);
	mSTATInterrupt = BIND_FUNC_NO_ARGS(this, InterruptsManager::statInterrupt);
	mTimerInterrupt = BIND_FUNC_NO_ARGS(this, InterruptsManager::timerInterrupt);
	mSerialInterrupt = BIND_FUNC_NO_ARGS(this, InterruptsManager::serialInterrupt);
	mJoypadInterrupt = BIND_FUNC_NO_ARGS(this, InterruptsManager::joypadInterrupt);

	mInterruptsList.push_back(mVBlankInterrupt);
	mInterruptsList.push_back(mSTATInterrupt);
	mInterruptsList.push_back(mTimerInterrupt);
	mInterruptsList.push_back(mSerialInterrupt);
	mInterruptsList.push_back(mJoypadInterrupt);
}

void InterruptsManager::vblankInterrupt() const
{
	*(mCPU->getPC()) = 0x40;
}

void InterruptsManager::statInterrupt() const
{
	*(mCPU->getPC()) = 0x48;
}

void InterruptsManager::timerInterrupt() const
{
	*(mCPU->getPC()) = 0x50;
}

void InterruptsManager::serialInterrupt() const
{
	*(mCPU->getPC()) = 0x58;
}

void InterruptsManager::joypadInterrupt() const
{
	*(mCPU->getPC()) = 0x60;
}
