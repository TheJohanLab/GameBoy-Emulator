#pragma once
#include "../Utils/Utils.h"
#include <iostream>

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

		void setAF(u16 value) { AF = value;
								std::cout << "AF = " << AF << "\n"; }


};

