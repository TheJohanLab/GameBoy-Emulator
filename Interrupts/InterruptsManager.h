#pragma once

#include <memory>
#include <functional>

class Bus;

enum InterruptsTypes
{
	VBLANK
};

class InterruptsManager
{
using interrupt = std::function<void()>;

private:
	std::shared_ptr<Bus> mBus;

	std::vector<interrupt> mInterruptsList;
	interrupt mVBlankInterrupt{ nullptr };
	


public:
	InterruptsManager(std::shared_ptr<Bus> bus);

	void callInterrupt(InterruptsTypes type) const;

	void setActiveInterrupts();

private:
	void initInterrupts();
};