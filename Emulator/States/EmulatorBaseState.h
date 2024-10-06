#pragma once

#include <functional>

enum class EmulatorState
{
	INIT, BOOT, RUN, PAUSE, STOP
};

class EmulatorBaseState
{
using Callback = std::function<void()>;

public:
	virtual void execute() = 0;
	void setHandleFrameCallback(Callback callback) { mHandleFrameCallback = callback; }
	void setHandleBootFrameCallback(Callback callback) { mHandleBootFrameCallback = callback; }
	void setDrawCallback(Callback callback) { mDrawCallback = callback; }

protected:
	Callback mHandleFrameCallback;
	Callback mHandleBootFrameCallback;
	Callback mDrawCallback;

};