#include "pch.h"

#include "BootRom.h"

//#include "Utils/Addresses.h"
//#include "Utils/Log.h"

#include "PPU/PPU.h"
#include "Bus/Bus.h"
#include "CPU/CPU.h"
#include "GameLoop/GameLoop.h"

BootRom::BootRom(std::shared_ptr<Bus> bus, std::shared_ptr<PPU> ppu, std::weak_ptr<CPU> cpu_weak)
	:mBus(bus), mPPU(ppu), mCPU_weak(cpu_weak)
{
}

BootRom::~BootRom()
{
}

void BootRom::initializeBootRom()
{
	extractBootLogo();
	mScrollingIter = 0;
	mBus->write(SCY, 0x64);
	auto cpu = mCPU_weak.lock();
	cpu->setIMEFlag();
	cpu->setInterruptEnable(0x01); // VBLANK interrupt only
}

void BootRom::execute()
{

#ifdef NO_BOOT
	mIsBootFinished = true;
#endif

	if (mIsBootFinished)
	{
		//PlaySound
		initRegistries();
		
//#ifdef STEP_DEBUG
//		mOnStateChange(EmulatorState::STEP);
//#else
		switch (GameLoop::getCurrentEmulatorState())
		{
		case EmulatorState::STEP:
			mOnStateChange(EmulatorState::STEP);
			break;
		case EmulatorState::RUN:
			mOnStateChange(EmulatorState::RUN);
			break;
		case EmulatorState::GOTO:
			mOnStateChange(EmulatorState::GOTO);
			break;
		};
		//GameLoop::getCurrentEmulatorState() == EmulatorState::STEP
		//	? mOnStateChange(EmulatorState::STEP)
		//	: mOnStateChange(EmulatorState::RUN);
//#endif

		mPPU->resetPPUModeDots();
		auto cpu = mCPU_weak.lock();
		cpu->getInterruptsManager()->setActiveVBlankInterrupt();
		cpu->clearIMEFlag();
#ifdef _DEBUG //TODO verifier pourquoi cette ligne est en debug uniquement
		mPPU->resetCurrCycles();
#endif
	}

}

void BootRom::scrollLogo()
{
	//auto PC = mCPU->getPC();
	//*PC = 0x0040;
	if (mScrollingIter < mTotalScrollingIter)
	{
		if (mVBLankCnt == 0)
			mVBLankCnt++;
		else
		{
			mPPU->decSCY();
			mScrollingIter++;
			mVBLankCnt = 0;
		}
	}
	else
	{
		mIsBootFinished = true;
	}

	auto cpu = mCPU_weak.lock();
	auto SP = cpu->getSP();
	*SP += 2;
	cpu->getInterruptsManager()->clearInterrupts();

	cpu->setIMEFlag();


}



///////////////////////
// PRIVATE FUNCTIONS //
///////////////////////
void BootRom::extractBootLogo()
{
	u16 headerLogoAddrOffset = 0x104;

	for (int i = 1; i < 25; i++)
	{
		u8 halfUpperTile{ mBus->read(headerLogoAddrOffset + 2*(i-1)) };
		u8 halfLowerTile{ mBus->read(headerLogoAddrOffset + 2*(i - 1) + 1) };

		convertToTile((halfUpperTile << 8) | halfLowerTile);
		u16 offset = ((i - 1) * 16);
		std::vector<u8> currTile(mExtractedBootLogo.begin() + offset, mExtractedBootLogo.begin() + offset + 16);
		mPPU->setTile(i, currTile);
	}


	const std::vector<u8> tileMapBoot{
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 ,  9, 10, 11, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	mPPU->setTileMap(0, tileMapBoot);

}

void BootRom::convertToTile(const u16 tileRawBytes)
{
	for (int nibble = 0; nibble < 4; nibble++)
	{
		auto b3 = (BIT(tileRawBytes, 4 * (4 - nibble) - 1 ));
		auto b2 = (BIT(tileRawBytes, 4 * (4 - nibble) - 2 ));
		auto b1 = (BIT(tileRawBytes, 4 * (4 - nibble) - 3 ));
		auto b0 = (BIT(tileRawBytes, 4 * (4 - nibble) - 4 ));

		u8 duplicated = b3 << 7 | b3 << 6 | b2 << 5 | b2 << 4 | b1 << 3 | b1 << 2 | b0 << 1 | b0 ;

		for (int i = 0; i < 4; i++)
			mExtractedBootLogo.push_back(duplicated);
	}
}

void BootRom::initRegistries()
{ 
	// On utilise DMG
	// CPU Registries
	auto cpu = mCPU_weak.lock();
	cpu->setRegistries("A", 0x01);
	cpu->setRegistries("B", 0x00);
	cpu->setRegistries("C", 0x13);
	cpu->setRegistries("D", 0x00);
	cpu->setRegistries("E", 0xD8);
	cpu->setRegistries("H", 0x01);
	cpu->setRegistries("L", 0x4D);
	cpu->setFlagRegistry(0x80);

	auto PC = cpu->getPC();
	auto SP = cpu->getSP();
	*PC = 0x100;
	*SP = 0xFFFE;

	// Hardware registries
	mBus->write(0xFF00, 0xCF);
	mBus->write(0xFF01, 0x00);
	mBus->write(0xFF02, 0x7E);
	mBus->write(0xFF04, 0xAB);
	mBus->write(0xFF05, 0x00);
	mBus->write(0xFF06, 0x00);
	mBus->write(0xFF07, 0xF8);
	mBus->write(0xFF0F, 0xE1);
	mBus->write(0xFF10, 0x80);
	mBus->write(0xFF11, 0xBF);
	mBus->write(0xFF12, 0xF3);
	mBus->write(0xFF13, 0xFF);
	mBus->write(0xFF14, 0xBF);
	mBus->write(0xFF16, 0x3F);
	mBus->write(0xFF17, 0x00);
	mBus->write(0xFF18, 0xFF);
	mBus->write(0xFF19, 0xBF);
	mBus->write(0xFF1A, 0x7F);
	mBus->write(0xFF1B, 0xFF);
	mBus->write(0xFF1C, 0x9F);
	mBus->write(0xFF1D, 0xFF);
	mBus->write(0xFF1E, 0xBF);
	mBus->write(0xFF20, 0xFF);
	mBus->write(0xFF21, 0x00);
	mBus->write(0xFF22, 0x00);
	mBus->write(0xFF23, 0xBF);
	mBus->write(0xFF24, 0x77);
	mBus->write(0xFF25, 0xF3);
	mBus->write(0xFF26, 0xF1);
	mBus->write(0xFF40, 0x91);
	mBus->write(0xFF41, 0x86);
	mBus->write(0xFF42, 0x00);
	mBus->write(0xFF43, 0x00);
	mBus->write(0xFF44, 0x00);
	mBus->write(0xFF45, 0x00);
	mBus->write(0xFF46, 0xFF);
	mBus->write(0xFF47, 0xFC);
	mBus->write(0xFF4A, 0x00);
	mBus->write(0xFF4B, 0x00);
	mBus->write(0xFFFF, 0x00);
	//Palettes Objets
	mBus->write(0xFF48, 0x00);
	mBus->write(0xFF49, 0x00);

}
