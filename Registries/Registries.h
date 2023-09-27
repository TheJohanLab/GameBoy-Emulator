#pragma once
#include "../Utils/Utils.h"

class Registries
{
	private:
		u16 AF;
		u16 BC;
		u16 DE;
		u16 HL;
		u16 SP;
		u16 PC;


	public:
		Registries();
		virtual ~Registries() = default;


};

