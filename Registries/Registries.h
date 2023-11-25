#pragma once
#include "../Utils/Utils.h"
#include <iostream>

class Registries
{
	private:

		u8 A;
		u8 B;
		u8 C; 
		u8 D;
		u8 E;
		u8 H;
		u8 L;
		flags F;
		u16 SP;
		u16 PC;



	public:
		Registries();
		virtual ~Registries() = default;

		//void setAF(u16 value) { AF = value;
		//						std::cout << "AF = " << AF << "\n"; }


		u8 getA() { return A; }
		u8 getB() { return B; }
		u8 getC() { return C; }
		u8 getD() { return D; }
		u8 getE() { return E; }
		flags getF() { return F; }
		u8 getH() { return H; }
		u8 getL() { return L; }
		u16 getAF() { return ((0x00 + A) << 8) + F.F; }
		u16 getBC() { return ((0x00 + B) << 8) + C; }
		u16 getDE() { return ((0x00 + D) << 8) + E; }
		u16 getBC() { return ((0x00 + H) << 8) + L; }
		u16 getSP() { return SP; }
		u16 getPC() { return PC; }

		void setA(u8 A) { A = A; }
		void setB(u8 A) { B = B; }
		void setC(u8 A) { C = C; }
		void setD(u8 A) { D = D; }
		void setE(u8 A) { E = E; }
		void setF(u8 A) { F = F; }
		void setH(u8 A) { H = H; }
		void setL(u8 A) { L = L; }
		void setAF(u16 AF) { A = (AF & 0xF0) >> 8; F.F = AF & 0x0F; }
		void setBC(u16 BC) { B = (BC & 0xF0) >> 8; C = BC & 0x0F; }
		void setDE(u16 DE) { D = (DE & 0xF0) >> 8; E = DE & 0x0F; }
		void setHL(u16 HL) { H = (HL & 0xF0) >> 8; L = HL & 0x0F; }

		void setSP(u16 SP) { SP = SP; }
		void setPC(u16 PC) { PC = PC; }
		


};

