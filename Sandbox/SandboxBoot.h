
#include <iostream>
#include "Emulator/Emulator.h"
#include "resources/gbBootRes.h"
#include "Registries/IORegistries.h"

#define TASK(action) [this]() -> void { action }


class SandboxBoot : public gbe::Emulator
{
public:

	void initTiles()
	{

		for (int i = 1; i < 26; i++)
		{
			u16 offset = ((i-1) * 16);
			std::vector<u8> currTile(nintendoLogo.begin() + offset, nintendoLogo.begin() + offset + 16);
			mPPU->setTile(i, currTile);
		}
		mPPU->setTile(0, EmptyTile);
		mPPU->setTile(26, tile1);
		mPPU->setTile(27, tile2);
	}

	void initTileMaps()
	{
		//std::vector<u8>tileMap2(1024, 1);

		mPPU->setTileMap(0, tileMapBoot);
	}

	void initRegistries()
	{
		u_LCD_control LCDControl{};
		LCDControl.flags.windowTileMap = 1;
		LCDControl.flags.BGtileMap = 0;
		LCDControl.flags.BG_WindowTiles = 1;
		LCDControl.flags.BG_WindowEnable = 1;
		LCDControl.flags.windowEnable = 0;
		mBus->write(LCD_CONTROL, LCDControl.byte);
		//mPPU->setBGP(0b10011010);
		//mPPU->setOBP0(0b00011011);
		//mPPU->setOBP1(0b00011011);

		//u8 wxValue = 150;
		//u8 wyValue = 150;
		//mBus->write(WINDOW_X, wxValue);
		//mBus->write(WINDOW_Y, wyValue);
	}

	void addTestSequence()
	{
		if (mPPU && mGameLoop)
		{
			for (int i = 0; i < 60; i++)
			{
				mGameLoop->addToSequence(
					TASK({
						mPPU->decSCY();
						})
				);
			}

			for (int i = 0; i < 100; i++)
			{
				mGameLoop->addToSequence(
					TASK({
						mPPU->waitForNextFrame();
						})
				);
			}

			mGameLoop->addToSequence(
				TASK({
					mBus->write(SCY, 0);
					})
			);


		}
	}

};
