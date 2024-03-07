#include "Registries.h"

Registries::Registries() : A(0x00), B(0x00), C(0x00), D(0x00), E(0x00), H(0x00), L(0x00)
{
	F.F = 0x00;
	
	AF.highRegistry = &A;
	AF.lowRegistry = &F.F;

	BC.highRegistry = &B;
	BC.lowRegistry = &C;

	DE.highRegistry = &D;
	DE.lowRegistry = &E;
	
	HL.highRegistry = &H;
	HL.lowRegistry = &L;

	PC = 0xC000;
}