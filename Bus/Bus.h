#pragma once

#include "../Memory/Memory.h"
#include "../Utils/Utils.h"

class Bus
{

	private:
		Memory mMemory;

	public:
		Bus();
		virtual ~Bus() = default;

		//u8 read(u16 address);
		//void write(u16 address, u8 data);

};

