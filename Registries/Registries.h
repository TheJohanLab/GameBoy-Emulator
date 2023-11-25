#pragma once
#include "../Utils/Utils.h"
#include <iostream>

class Registries
{
	private:

		u8 A,B,C,D,E,H,L;
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
		u16 getAF() { return ((0x00 + A) << 8) + F.F; }
		u16 getBC() { return ((0x00 + B) << 8) + C; }
		u16 getDE() { return ((0x00 + D) << 8) + E; }
		u16 getHL() { return ((0x00 + H) << 8) + L; }
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
		void setAF(u16 value) { this->A = (value & 0xF0) >> 8; this->F.F = value & 0x0F; }
		void setBC(u16 value) { this->B = (value & 0xF0) >> 8; this->C = value & 0x0F; }
		void setDE(u16 value) { this->D = (value & 0xF0) >> 8; this->E = value & 0x0F; }
		void setHL(u16 value){ this->H = (value & 0xF0) >> 8; this->L = value & 0x0F; }

		void setSP(u16 value) { this->SP = value; }
		void setPC(u16 value) { this->PC = value; }
		


};

