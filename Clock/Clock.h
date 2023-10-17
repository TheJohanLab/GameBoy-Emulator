#pragma once

#include "../Utils/Utils.h"

class Clock
{
	private:
		long const cycleDuration = (1 / 4.19e6) * 1e9; //238 ns

	public:
		Clock();
		virtual ~Clock() = default;

		void emulateCycles(u8 cyclesNb) const;

};

