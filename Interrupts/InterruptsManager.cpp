#include "InterruptsManager.h"

#include "CPU/CPU.h"
#include "Utils/Utils.h"

InterruptsManager::InterruptsManager(std::shared_ptr<CPU> cpu)
	:mCPU(cpu)
{
}

void InterruptsManager::callInterrupt(InterruptsTypes type) const
{
	mInterruptsList[type]();
}

void InterruptsManager::setActiveInterrupts()
{

}

void InterruptsManager::initInterrupts()
{
	mVBlankInterrupt = BIND_FUNC_NO_ARGS(this, InterruptsManager::mVBlankInterrupt);
}

void InterruptsManager::vblankInterrupt() const
{
	*(mCPU->getPC()) = 0x40;
}
