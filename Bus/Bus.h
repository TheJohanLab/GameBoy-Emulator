#pragma once

//#include <memory>

#include "Memory/Memory.h"
#include "Cartridge/Cartridge.h"

#include "Registries/IORegistries.h"


class Bus
{
	private:
		Memory mMemory;
		//std::shared_ptr<Memory> mMemory{nullptr};
		std::shared_ptr<Cartridge> mCartridge;

	public:
		Bus();
		virtual ~Bus() = default;

		u8 read(const u16 address) const;
		void write(const u16 address, const u8 data);
		u8* getDataPtr(const u16 address);

		//Interrupts
		interrupt_flag getInterruptEnable() const;
		interrupt_flag getInterruptFlag() const;
		void setInterruptEnable(const u8 flags);
		void setInterruptFlag(const u8 flags);

		void setDMATransfertCallback(std::function<void(const u8)> callback) { mMemory.setDMACallback(callback); }
		//void setLoadCartridgeCallback(std::function<void()> callback) { mCartridge->setLoadCallback(callback); }

		std::shared_ptr<Cartridge> getCartrige() { return mCartridge; }
		const MemoryUnion& getMemoryReference() const { return mMemory.getMemory(); } // TODO check if still needed
		std::shared_ptr<const Memory> getMemoryRef() { return std::shared_ptr<const Memory>(& mMemory); }

		void reset();

};

