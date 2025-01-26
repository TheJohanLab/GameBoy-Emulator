#include "pch.h"

#include "InterruptsManager.h"

#include "CPU/CPU.h"
//#include "Utils/Utils.h"
#include "BootRom/BootRom.h"

//#include "Utils/Log.h"

InterruptsManager::InterruptsManager(std::weak_ptr<CPU> cpu_weak)
	:mCPU_weak(cpu_weak)
{
	
}

InterruptsManager::~InterruptsManager()
{
}

void InterruptsManager::setInterrupt(InterruptsTypes type)
{
	u8 interruptFlag = 0x01 << type;
	auto cpu = mCPU_weak.lock();

	std::pair< interrupt_flag, interrupt_flag> interruptFlags = cpu->getInterruptFlags();
	cpu->setInterruptFlag(interruptFlags.second.byte | interruptFlag);

}

void InterruptsManager::clearInterrupts()
{
	mActiveInterruptFlags.flags.Vblank = 0;
	mActiveInterruptFlags.flags.Joypad= 0;
	mActiveInterruptFlags.flags.LCD_STAT= 0;
	mActiveInterruptFlags.flags.Timer= 0;
	mActiveInterruptFlags.flags.SerialTransferCompletion = 0;
}

//void InterruptsManager::callInterruptHandler()
//{
//	if (!mCPU->getIMEFlag())
//		return;
//
//	/*std::pair< interrupt_flag, interrupt_flag> interruptFlags = mCPU->getInterruptFlags();
//
//	interrupt_flag activeInterrupts;
//	activeInterrupts.byte = ((interruptFlags.first.byte & interruptFlags.second.byte) & 0x0F);*/
//
//	//if (mCurrentInterrupt != InterruptsTypes::NONE)
//	//{
//	//	mCPU->clearIMEFlag();
//	//	InstructionJump::PUSH_PC(*mCPU);
//
//	//	mInterruptsList[mCurrentInterrupt]();
//	//}
//}

void InterruptsManager::callInterruptHandler()
{
	auto cpu = mCPU_weak.lock();
	if (!cpu->getIMEFlag())
		return;

	getActiveInterruptFlags();

	if (mActiveInterruptFlags.byte > 0x00)
	{
		cpu->resumeCPUFromInterrupt();
		cpu->clearIMEFlag(); 
		InstructionJump::PUSH_PC(*cpu);

		if (mActiveInterruptFlags.flags.Vblank)
			(*mInterruptsList[VBLANK])();
		else if (mActiveInterruptFlags.flags.LCD_STAT)
			(*mInterruptsList[LCD_STAT])();
		else if (mActiveInterruptFlags.flags.Timer)
			(*mInterruptsList[TIMER])();
		else if (mActiveInterruptFlags.flags.SerialTransferCompletion)
			(*mInterruptsList[SERIAL])();
		else if (mActiveInterruptFlags.flags.Joypad)
			(*mInterruptsList[JOYPAD])();

		cpu->setInterruptFlag(mActiveInterruptFlags.byte);

	}

}
void InterruptsManager::setActiveVBlankInterrupt()
{
	mVBlankInterrupt = BIND_FUNC_NO_ARGS(this, InterruptsManager::vblankInterrupt);
}

void InterruptsManager::initInterrupts()
{
	if (auto cpu = mCPU_weak.lock())
		mVBlankInterrupt = BIND_FUNC_NO_ARGS(cpu->getBootRom(), BootRom::scrollLogo);
	else
		GBE_LOG_ERROR("Impossible de recuperer BootRom");

	mSTATInterrupt = BIND_FUNC_NO_ARGS(this, InterruptsManager::statInterrupt);
	mTimerInterrupt = BIND_FUNC_NO_ARGS(this, InterruptsManager::timerInterrupt);
	mSerialInterrupt = BIND_FUNC_NO_ARGS(this, InterruptsManager::serialInterrupt);
	mJoypadInterrupt = BIND_FUNC_NO_ARGS(this, InterruptsManager::joypadInterrupt);
	mNone = BIND_FUNC_NO_ARGS(this, InterruptsManager::none);

	mInterruptsList.emplace_back(&mVBlankInterrupt);
	mInterruptsList.emplace_back(&mSTATInterrupt);
	mInterruptsList.emplace_back(&mTimerInterrupt);
	mInterruptsList.emplace_back(&mSerialInterrupt);
	mInterruptsList.emplace_back(&mJoypadInterrupt);
	mInterruptsList.emplace_back(&mNone);
}

void InterruptsManager::vblankInterrupt() 
{
	auto cpu = mCPU_weak.lock();
	*(cpu->getPC()) = 0x40;
	mActiveInterruptFlags.flags.Vblank = 0;
	
}

void InterruptsManager::statInterrupt() 
{	
	auto cpu = mCPU_weak.lock();
	*(cpu->getPC()) = 0x48;
	mActiveInterruptFlags.flags.LCD_STAT = 0;
}

void InterruptsManager::timerInterrupt() 
{
	auto cpu = mCPU_weak.lock();
	*(cpu->getPC()) = 0x50;
	mActiveInterruptFlags.flags.Timer = 0;
}

void InterruptsManager::serialInterrupt() 
{
	auto cpu = mCPU_weak.lock();
	*(cpu->getPC()) = 0x58;
	mActiveInterruptFlags.flags.SerialTransferCompletion = 0;
}

void InterruptsManager::joypadInterrupt() 
{
	auto cpu = mCPU_weak.lock();
	*(cpu->getPC()) = 0x60;
	mActiveInterruptFlags.flags.Joypad = 0;
}

void InterruptsManager::none()
{

}

void InterruptsManager::getActiveInterruptFlags()
{
	auto cpu = mCPU_weak.lock();
	std::pair< interrupt_flag, interrupt_flag> interruptFlags = cpu->getInterruptFlags();
	mActiveInterruptFlags.byte = ((interruptFlags.first.byte & interruptFlags.second.byte) & 0x0F);
}
