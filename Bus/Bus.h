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

		interrupt_flag getInterruptEnable() const;
		interrupt_flag getInterruptFlag() const;

		void setInterruptEnable(const u8 flags);
		void setInterruptFlag(const u8 flags);

};

