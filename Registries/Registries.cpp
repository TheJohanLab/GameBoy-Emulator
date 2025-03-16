#include "pch.h"

#include "Registries.h"
#include "CPU/CPU.h"

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

	mRegistries = { A, F.F, B, C, D, E, H, L};
}

std::vector<std::reference_wrapper<u8>>& Registries::getRegistriesRef()
{
	return mRegistries;
}

const std::vector<std::reference_wrapper<const u8>>& Registries::getRegistriesRef() const
{
	//TODO
	return std::vector<std::reference_wrapper<const u8>>();
}

const u16& Registries::getPCRef() const
{
	return PC;
}

u16& Registries::getPCRef()
{
	return PC;
}

const u16& Registries::getSPRef() const
{
	return SP;
}

u16& Registries::getSPRef()
{
	return SP;
}

const flags& Registries::getFlagsRef() const
{
	return F;
}

flags& Registries::getFlagsRef()
{
	return F;
}

u16& Registries::getAFRef()
{
	return mAF;
}

u16& Registries::getBCRef()
{
	return mBC;
}

u16& Registries::getDERef()
{
	return mDE;
}

u16& Registries::getHLRef()
{
	return mHL;
}


