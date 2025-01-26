#include "pch.h"

#include "OAM.h"

OAM::OAM()
{
	for (auto& object : mObjects)
	{
		object.AttributeFlags.byte = 0x00;
		object.XPos = 0x00;
		object.YPos = 0x00;
		object.tileIndex = 0x00;
	}
}

void OAM::write(u8 index, const u8& YPos, const u8& XPos, const u8& tileIndex, const u8& attrs)
{
	mObjects[index].AttributeFlags.byte = attrs;
	mObjects[index].YPos = YPos;
	mObjects[index].XPos = XPos;
	mObjects[index].tileIndex = tileIndex;
}


void OAM::writeYPos(u8 index, const u8& YPos)
{
	mObjects[index].YPos = YPos;
}

void OAM::writeXPos(u8 index, const u8& XPos)
{
	mObjects[index].XPos = XPos;
}

void OAM::writeTileIndex(u8 index, const u8& tileIndex)
{
	mObjects[index].tileIndex = tileIndex;
}

void OAM::writeAttrs(u8 index, const u8& attrs)
{
	mObjects[index].AttributeFlags.byte = attrs;
}


OAM::Object OAM::read(u8 index) const
{
	return mObjects[index];
}

u8 OAM::readYPos(u8 index) const
{
	return mObjects[index].YPos;
}

std::array<OAM::Object, MAX_OBJECTS>& OAM::getObjects()
{
	 return mObjects;
}

u8 OAM::readXPos(u8 index) const
{
	return mObjects[index].XPos;
}

u8 OAM::readTileIndex(u8 index) const
{
	return mObjects[index].tileIndex;
}

u8 OAM::readAttrs(u8 index) const
{
	return mObjects[index].AttributeFlags.byte;
}



