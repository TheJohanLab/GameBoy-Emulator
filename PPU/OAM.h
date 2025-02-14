#pragma once

//#include "../Utils/Utils.h"
//#include <array>

class OAM {


public:
	typedef struct s_Attributes_Flags {
		u8 CGBAttr : 4; // Not used in DMG
		u8 DMGPalette : 1;
		u8 XFlip : 1;
		u8 YFlip : 1;
		u8 priority : 1; // 1 : BG Over OBJ
	};

	typedef union u_Attributes_Flags {
		u8 byte;
		s_Attributes_Flags attr;
	}Attributes_Flags;

	typedef struct Object {
		u8 YPos;
		u8 XPos;
		u8 tileIndex;
		Attributes_Flags AttributeFlags;
	} Object;


private:
	std::array<Object, MAX_OBJECTS> mObjects;

public:
	OAM();
	~OAM() = default;

	void write(u8 index, const u8& YPos, const u8& XPos, const u8& tileIndex, const u8& attrs);

	void writeYPos(u8 index, const u8& YPos);
	void writeXPos(u8 index, const u8& XPos);
	void writeTileIndex(u8 index, const u8& tileIndex);
	void writeAttrs(u8 index, const u8& attrs);

	Object read(u8 index) const;
	u8 readYPos(u8 index) const;
	u8 readXPos(u8 index) const;
	u8 readTileIndex(u8 index) const;
	u8 readAttrs(u8 index) const;

	std::array<Object, MAX_OBJECTS>& getObjects();

	void reset();
};