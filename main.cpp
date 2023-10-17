#include <iostream>
#include "Bus/Bus.h"
#include "Clock/Clock.h"
#include <chrono>

int main(int argc, char** argv)
{
	//Bus bus;
	Clock clock = Clock();


	std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

	clock.emulateCycles(1);
	/*while ()
	{

		// Lecture opcode
		// executeOpCode 
		// clock.emulateCycles(instruction.get)

	}*/
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;


	return 0;
}