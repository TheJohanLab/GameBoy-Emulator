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

		u8 read(const u16 &address) const;
		void write(const u16 &address, const u8 &data);
		u8* getDataPtr(const u16& address);

		interrupt_flag getInterruptFlag();
		void setInterruptFlags(u8 flags);
		void setInterruptFlags(interrupt_flag flags);

};

