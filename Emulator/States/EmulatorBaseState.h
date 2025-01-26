#pragma once

//#include <functional>
//#include <memory>

enum class EmulatorState
{
	INIT, BOOT, RUN, PAUSE, STOP, STEP
};

class EmulatorBaseState
{
using Callback = std::function<void()>;

public:
	virtual void execute() = 0;
	void setHandleFrameCallback(Callback callback) { mHandleFrameCallback = callback; }
	void setHandleBootFrameCallback(Callback callback) { mHandleBootFrameCallback = callback; }
	void setDrawCallback(Callback callback) { mDrawCallback = callback; }
	void setStepCallback(Callback callback) { mStepCallback = callback; }

protected:

	Callback mHandleFrameCallback;
	Callback mHandleBootFrameCallback;
	Callback mDrawCallback;
	Callback mStepCallback;

};