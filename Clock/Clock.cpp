#include "Clock.h"
#include <windows.h>
#include <chrono>
#include <thread>

Clock::Clock(){}

void Clock::emulateCycles(u8 cyclesNb) const
{
	std::this_thread::sleep_for(std::chrono::milliseconds(3));
	
}