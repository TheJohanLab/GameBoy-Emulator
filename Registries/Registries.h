#pragma once
#include "../Utils/Utils.h"
#include <iostream>

struct combinedRegistries 
{
	u8* highRegistry;
	u8* lowRegistry;
	

	u8* getLowRegistry() 
	{
		return lowRegistry;
	}

	u8* getHighRegistry() 
	{
		return highRegistry;
	}

	u16 getValue() const
	{
		return static_cast<u16>((*highRegistry << 8) & 0xFF00 | (*lowRegistry & 0x00FF));
	}

	void setValue(u16 value)
	{
		*highRegistry = (value >> 8) & 0xFF;
		*lowRegistry = value & 0xFF;
	}

	combinedRegistries& operator++(int)
	{
		combinedRegistries tmp = *this;
		uint16_t u16Registries = static_cast<u16>(*(tmp.highRegistry)) << 8 | static_cast<u16>(*tmp.lowRegistry);
		u16Registries += 1;

		*highRegistry = static_cast<u8>((u16Registries >> 8) & 0xFF);
		*lowRegistry = static_cast<u8>(u16Registries & 0xFF);

		return *this;
	}

	combinedRegistries& operator++()
	{
		uint16_t u16Registries = static_cast<u16>(*highRegistry) << 8 | static_cast<u16>(*lowRegistry);
		u16Registries += 1;

		*highRegistry = static_cast<u8>((u16Registries >> 8) & 0xFF);
		*lowRegistry = static_cast<u8>(u16Registries & 0xFF);

		return *this;
	}

	combinedRegistries& operator--(int)
	{
		combinedRegistries tmp = *this;
		uint16_t u16Registries = static_cast<u16>(*(tmp.highRegistry)) << 8 | static_cast<u16>(*tmp.lowRegistry);
		u16Registries -= 1;

		*highRegistry = static_cast<u8>((u16Registries >> 8) & 0xFF);
		*lowRegistry = static_cast<u8>(u16Registries & 0xFF);

		return *this;
	}

	combinedRegistries& operator--()
	{
		uint16_t u16Registries = static_cast<u16>(*highRegistry) << 8 | static_cast<u16>(*lowRegistry);
		u16Registries -= 1;

		*highRegistry = static_cast<u8>((u16Registries >> 8) & 0xFF);
		*lowRegistry = static_cast<u8>(u16Registries & 0xFF);

		return *this;
	}

};


class Registries
{
	private:

		u8 A,B,C,D,E,H,L;
		combinedRegistries AF, BC, DE, HL;
		flags F;
		u16 SP,PC;

	public:
		Registries();
		virtual ~Registries() = default;

		u8* getA() { return &A; }
		u8* getB() { return &B; }
		u8* getC() { return &C; }
		u8* getD() { return &D; }
		u8* getE() { return &E; }
		flags* getF() { return &F; }
		u8* getH() { return &H; }
		u8* getL() { return &L; }

		/*u16 getAF() { return (((0x00 + A) << 8) + F.F); }
		u16 getBC() { return ((0x00 + B) << 8) + C; }
		u16 getDE() { return ((0x00 + D) << 8) + E; }
		u16 getHL() { return ((0x00 + H) << 8) + L; }
		*/
		combinedRegistries* getAF() { return &AF; }
		combinedRegistries* getBC() { return &BC; }
		combinedRegistries* getDE() { return &DE; }
		combinedRegistries* getHL() { return &HL; }

		u16* getSP() { return &SP; }
		u16* getPC() { return &PC; }

		void setA(u8 value) { this->A = value; }
		void setB(u8 value) { this->B = value; }
		void setC(u8 value) { this->C = value; }
		void setD(u8 value) { this->D = value; }
		void setE(u8 value) { this->E = value; }
		void setF(u8 value) { this->F.F = value; }
		void setH(u8 value) { this->H = value; }
		void setL(u8 value) { this->L = value; }
		void setAF(u16 value) { this->A = (value & 0xFF00) >> 8; this->F.F = value & 0x00FF; }
		void setBC(u16 value) { this->B = (value & 0xFF00) >> 8; this->C = value & 0x00FF; }
		void setDE(u16 value) { this->D = (value & 0xFF00) >> 8; this->E = value & 0x00FF; }
		void setHL(u16 value) { this->H = (value & 0xFF00) >> 8; this->L = value & 0x00FF; }

		void setSP(u16 value) { this->SP = value; }
		void setPC(u16 value) { this->PC = value; }

};

