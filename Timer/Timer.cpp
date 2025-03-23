#include "pch.h"
#include "Timer.h"

#include "Interrupts/InterruptsManager.h"


Timer::Timer(u8& TIMARef, u8& TMARef, const u8& TACRef)
	:mTIMARef(TIMARef), mTMARef(TMARef), mTACRef(reinterpret_cast<u_TAC&>(const_cast<u8&>(TACRef)))
{

}
//void Timer::setReferences(u8& TIMA, u8& TMA, const u8& TAC)
//{
//	mTIMARef = &TIMA;
//	mTMARef = &TMA;
//
//
//	mTACRef = reinterpret_cast<u_TAC*>(;
//}

void Timer::incTIMA()
{
	u8 prevValue = mTIMARef;

	(mTIMARef)++;

	if (prevValue > mTIMARef)
	{
		resetTIMA();
		InterruptsManager::setInterrupt(InterruptsTypes::TIMER);
	}

}

void Timer::resetTIMA()
{
	mTIMARef = mTMARef;
}

void Timer::handleTimer(const u8 opcodeDots)
{
	mElapsedDots += opcodeDots;

	u16 incrementPeriod = mIncrementPeriodMap[(mTACRef).bits.clock_select];
	if (mElapsedDots >= incrementPeriod)
	{
		if ((mTACRef).bits.enable)
			incTIMA();

		mElapsedDots -= incrementPeriod;
	}
}


const u8& Timer::getTIMA() const
{
	return mTIMARef;
}

const u8& Timer::getTMA() const
{
	return mTMARef;
}

const u_TAC& Timer::getTAC() const
{
	return mTACRef;
}