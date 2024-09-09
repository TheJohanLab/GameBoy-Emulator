#include <iostream>

#include "Sandbox.h"

int main(int argc, char** argv)
{
	EmulatorSandbox emulator{};
	emulator.addTestSequence();

	emulator.startEmulator();
	return 0;
}