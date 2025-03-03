#pragma once

#include "Memory/Memory.h"
#include "Cartridge/Cartridge.h"

#include "Registries/IORegistries.h"


class Bus
{
	private:
		std::shared_ptr<Memory> mMemory{ nullptr };
		std::shared_ptr<Cartridge> mCartridge{ nullptr };

	public:
		Bus(std::shared_ptr<Memory>, std::shared_ptr<Cartridge>);
		virtual ~Bus() = default;

		u8 read(const u16 address) const;
		void write(const u16 address, const u8 data);
		u8* getDataPtr(const u16 address);

		void reset();

		//Interrupts
		interrupt_flag getInterruptEnable() const;
		interrupt_flag getInterruptFlag() const;
		void setInterruptEnable(const u8 flags);
		void setInterruptFlag(const u8 flags);


		//Callbacks
		void setDMATransfertCallback(std::function<void(const u8)> callback) { mMemory->setDMACallback(callback); }


};

