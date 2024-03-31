#pragma once

#include "../Bus/Bus.h"
#include "../Screen/Screen.h"

class PPU
{
private:
	Bus* mBus;
	Screen* mScreen;

public:
	PPU(Bus* bus, Screen* screen);
	~PPU();

private:
};

