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

		void setA(u8 A) { this->A = A; }
		void setB(u8 A) { this->B = B; }
		void setC(u8 A) { this->C = C; }
		void setD(u8 A) { this->D = D; }
		void setE(u8 A) { this->E = E; }
		void setF(u8 A) { this->F = F; }
		void setH(u8 A) { this->H = H; }
		void setL(u8 A) { this->L = L; }
		void setAF(u16 AF) { this->A = (AF & 0xF0) >> 8; this->F.F = AF & 0x0F; }
		void setBC(u16 BC) { this->B = (BC & 0xF0) >> 8; this->C = BC & 0x0F; }
		void setDE(u16 DE) { this->D = (DE & 0xF0) >> 8; this->E = DE & 0x0F; }
		void setHL(u16 HL) { this->H = (HL & 0xF0) >> 8; this->L = HL & 0x0F; }

		void setSP(u16 SP) { this->SP = SP; }
		void setPC(u16 PC) { this->PC = PC; }
		


};

