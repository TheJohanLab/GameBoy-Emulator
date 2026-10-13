#include "pch.h"

#include "InterruptsManager.h"

#include "CPU/CPU.h"
//#include "Utils/Utils.h"
#include "BootRom/BootRom.h"

//#include "Utils/Log.h"

std::weak_ptr<CPU> InterruptsManager::mCPU_weak;

InterruptsManager::InterruptsManager()
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

void InterruptsManager::setCPU(std::weak_ptr<CPU> cpu)
{
	mCPU_weak = cpu;
}

void InterruptsManager::clearInterrupts()
{
	mActiveInterruptFlags.flags.Vblank = 0;
	mActiveInterruptFlags.flags.Joypad= 0;
	mActiveInterruptFlags.flags.LCD_STAT= 0;
	mActiveInterruptFlags.flags.Timer= 0;
	mActiveInterruptFlags.flags.SerialTransferCompletion = 0;
}


void InterruptsManager::callInterruptHandler()
{
	auto cpu = mCPU_weak.lock();

	getActiveInterruptFlags();

	if (!cpu->getIMEFlag())
	{
		handleHaltInterrupt(cpu);
		return;
	}

	if (mActiveInterruptFlags.byte > 0x00)
	{
		const u8 pendingBefore = mActiveInterruptFlags.byte;
		cpu->resumeCPUFromInterrupt();
		cpu->setIMEFlag(0x00); 
		// Push the address of the NEXT instruction. PC already points to it here (executeOpcode() ran
		// incPC()), whereas InstructionJump::PUSH_PC() is made for CALL/RST and pushes PC + 1: every
		// RETI used to resume one byte too far.
		{
			u16* SP = cpu->getSP();
			const u16 returnAddress = *cpu->getPC();
			(*SP)--;
			cpu->writeMemory(*SP, static_cast<u8>(returnAddress >> 8));
			(*SP)--;
			cpu->writeMemory(*SP, static_cast<u8>(returnAddress & 0xFF));
		}

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

		// Acknowledge only the serviced interrupt: the other IF bits (including requests that are not
		// enabled in IE) must stay set.
		const u8 servicedBit = pendingBefore & ~mActiveInterruptFlags.byte;
		cpu->setInterruptFlag(static_cast<u8>(cpu->getInterruptFlags().second.byte & ~servicedBit));

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
	mActiveInterruptFlags.byte = ((interruptFlags.first.byte & interruptFlags.second.byte) & 0x1F); // 5 sources incl. joypad
}


void InterruptsManager::handleHaltInterrupt(std::shared_ptr<CPU> cpu)
{
	// IME = 0: a pending interrupt only wakes the CPU from HALT; it is not serviced. This runs after
	// EVERY instruction, so it must not arm the HALT bug: doing so froze PC (incPC() added 0) for as
	// long as IE & IF != 0, i.e. forever, because nothing could reach the code that clears IF.
	if (mActiveInterruptFlags.byte > 0x00 && cpu->getCPUHaltedStatus())
		cpu->resumeCPUFromInterrupt();
}