#include "Registries.h"

Registries::Registries() : A(0x00), B(0x00), C(0x00), D(0x00), E(0x00), H(0x00), L(0x00)
{
	F.F = 0x00;
	
	AF.reg1 = &A;
	AF.reg2 = &F.F;

	BC.reg1 = &B;
	BC.reg2 = &C;

	DE.reg1 = &D;
	DE.reg2 = &E;
	
	HL.reg1 = &H;
	HL.reg2 = &L;

	PC = 0xC000;
}