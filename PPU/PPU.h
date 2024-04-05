#pragma once

#include "../Bus/Bus.h"
#include "../Screen/Screen.h"

class PPU
{
private:
	Bus* mBus;
	Screen* mScreen;

public:
	PPU(Bus* bus, Screen* screen);
	~PPU();

	LCD_control getLCDControl() const; //FF40
	LCD_status getLCDStatus() const; //FF41
	void setLCDControl(const u8 flags);
	void setLCDStatus(const u8 flags);

	u8 readSCY() const; //FF42
	u8 readSCX() const; //FF43
	u8 readLY() const; //FF44
	u8 readLYC() const; //FF45


	BG_palette_data getBGP() const; //FF47
	void setBGP(const u8 flags);

	u8 readOBP0() const; // FF48
	u8 readOBP1() const; // FF49

	u8 readWY() const; //FF4A
	u8 readWX() const; //FF4B

private:
};

