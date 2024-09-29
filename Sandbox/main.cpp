#include <iostream>

#include "SandboxEmulator.h"
#include "SandboxBoot.h"

int main(int argc, char** argv)
{
	//EmulatorSandbox emulator{};
	SandboxBoot emulator{};
	//emulator.initTiles();
	//emulator.initTileMaps();
	emulator.initRegistries();
	emulator.addTestSequence();
	//emulator.startDMATransfer();
	
	emulator.startEmulator();
	return 0;
}