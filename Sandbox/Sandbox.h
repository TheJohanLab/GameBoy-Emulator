
#include <iostream>
#include "Emulator/Emulator.h"

#define TASK(action) [this]() -> void { action }

class EmulatorSandbox : public gbe::Emulator
{
public:
	void addTestSequence()
	{
		if (mPPU && mGameLoop)
		{
			
			mPPU->writeOAM(1, 20, 50, 2, 0);
			mPPU->writeOAM(2, 22, 52, 0, 0);

			mGameLoop->addToSequence(
				TASK({ 
					mPPU->writeOAM_XPos(1, 51);
					mPPU->writeOAM_YPos(1, 22);
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->writeOAM_XPos(1, 53);
					mPPU->writeOAM_YPos(1, 24);
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->writeOAM_XPos(1, 55);
					mPPU->writeOAM_YPos(1, 26);
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->writeOAM_XPos(1, 57);
					mPPU->writeOAM_YPos(1, 28);
					})
			);
			mGameLoop->addToSequence(
				TASK({
					mPPU->writeOAM_XPos(1, 59);
					mPPU->writeOAM_YPos(1, 30);
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->writeOAM_XPos(1, 61);
					mPPU->writeOAM_YPos(1, 32);
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->writeOAM_XPos(1, 64);
					mPPU->writeOAM_YPos(1, 34);
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->writeOAM_XPos(1, 66);
					mPPU->writeOAM_YPos(1, 36);
					})
			);
			mGameLoop->addToSequence(
				TASK({
					mPPU->writeOAM_XPos(1, 68);
					mPPU->writeOAM_YPos(1, 38);
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->writeOAM_XPos(1, 70);
					mPPU->writeOAM_YPos(1, 40);
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->writeOAM_XPos(1, 72);
					mPPU->writeOAM_YPos(1, 42);
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->writeOAM_XPos(1, 74);
					mPPU->writeOAM_YPos(1, 44);
					})
			);
			mGameLoop->addToSequence(
				TASK({
					mPPU->writeOAM_XPos(1, 76);
					mPPU->writeOAM_YPos(1, 46);
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->writeOAM_XPos(1, 78);
					mPPU->writeOAM_YPos(1, 48);
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->writeOAM_XPos(1, 80);
					mPPU->writeOAM_YPos(1, 50);
					})
			);

			mGameLoop->addToSequence(
				TASK({
					mPPU->writeOAM_XPos(1, 82);
					mPPU->writeOAM_YPos(1, 52);
					})
			); 
		}
	}

};
