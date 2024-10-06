#include "Registries.h"
#include "../CPU/CPU.h"

Registries::Registries()
{
	AF.highRegistry = &A;
	AF.lowRegistry = &F.F;

	BC.highRegistry = &B;
	BC.lowRegistry = &C;

	DE.highRegistry = &D;
	DE.lowRegistry = &E;

	HL.highRegistry = &H;
	HL.lowRegistry = &L;


}

Registries::Registries(CPU& cpu)
{
	AF.highRegistry = &A;
	AF.lowRegistry = &F.F;

	BC.highRegistry = &B;
	BC.lowRegistry = &C;

	DE.highRegistry = &D;
	DE.lowRegistry = &E;
	
	HL.highRegistry = &H;
	HL.lowRegistry = &L;

}