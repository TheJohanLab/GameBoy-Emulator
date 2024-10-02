#pragma once

enum class EmulatorState
{
	INIT, BOOT, START, PAUSE, STOP
};

class IEmulatorState
{
public:
	virtual void execute() = 0;

};