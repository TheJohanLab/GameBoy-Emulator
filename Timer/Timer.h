#pragma once



typedef struct s_TAC {
	u8 clock_select : 2;
	u8 enable : 1;
	u8 unused : 5;
}s_TAC;

typedef union u_TAC {
	u8 raw;
	s_TAC bits;
}u_TAC;



class Timer
{

	std::unordered_map<u8, u16> mIncrementPeriodMap =
	{
		{0x00, 256 * 4},
		{0x01, 4 * 4},
		{0x02, 16 * 4},
		{0x03, 64 * 4}
	};

	private:


		u8& mTIMARef;
		u8& mTMARef;
		const u_TAC& mTACRef;

		u32 mElapsedDots{ 0 };


	public:
		Timer(u8& TIMARef, u8& TMARef, const u8& TACRef);
		//void setReferences(u8& TIMA, u8& TMA, const u8& TAC);

		void incTIMA();
		void resetTIMA();

		void handleTimer(const u8 opcodeDots);

		const u8& getTIMA() const;
		const u8& getTMA() const;
		const u_TAC& getTAC() const;
		



};

