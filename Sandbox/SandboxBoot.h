
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
		mPPU->setTile(0, EmptyTile);
		//N
		mPPU->setTile(1, N1Tile);
		mPPU->setTile(2, N2Tile);
		mPPU->setTile(3, N3Tile);
		mPPU->setTile(4, N4Tile);
		//I
		mPPU->setTile(5, I1Tile);
		mPPU->setTile(6, I2Tile);
		//n
		mPPU->setTile(7, n1Tile);
		mPPU->setTile(8, n2Tile);
		mPPU->setTile(9, n3Tile);
		mPPU->setTile(10, n4Tile);
		//t
		mPPU->setTile(11, t1Tile);
		mPPU->setTile(12, t2Tile);
		//e
		mPPU->setTile(13, e1Tile);
		mPPU->setTile(14, e2Tile);
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
		mBus->write(LCD_CONTROL, LCDControl.byte);

		u8 wxValue = 150;
		u8 wyValue = 150;
		mBus->write(WINDOW_X, wxValue);
		mBus->write(WINDOW_Y, wyValue);
	}

	void addTestSequence()
	{
		if (mPPU && mGameLoop)
		{

			

			mGameLoop->addToSequence(
				TASK({
					mPPU->incSCY();
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->incSCY();
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->incSCY();
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->incSCY();
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->incSCY();
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->incSCY();
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->incSCY();
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->incSCY();
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->incSCY();
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->incSCY();
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->incSCY();
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->incSCY();
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->incSCY();
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->incSCY();
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->incSCY();
					})
			);
		}
	}

};
