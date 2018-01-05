#include "vClock.h"
#include "vTime.h"


namespace vEngine {
	Clock::Clock()
		: mStartTime(), mCurrentTime(), mLastTime(), mFrequency()
	{
		mFrequency = GetFrequency();
		Reset();
	}

	const LARGE_INTEGER& Clock::StartTime() const
	{
		return mStartTime;
	}

	const LARGE_INTEGER& Clock::CurrentTime() const
	{
		return mCurrentTime;
	}

	const LARGE_INTEGER& Clock::LastTime() const
	{
		return mLastTime;
	}

	void Clock::Reset()
	{
		GetTime(mStartTime);
		mCurrentTime = mStartTime;
		mLastTime = mCurrentTime;
	}

	double Clock::GetFrequency() const
	{
		LARGE_INTEGER frequency;

		if (QueryPerformanceFrequency(&frequency) == false)
		{
			throw std::exception("QueryPerformanceFrequency() failed.");
		}

		return (double)frequency.QuadPart;
	}

	void Clock::GetTime(LARGE_INTEGER& time) const
	{
		QueryPerformanceCounter(&time);
	}

	void Clock::UpdateGameTime(Time& gameTime)
	{
		GetTime(mCurrentTime);
		gameTime.SetTotalGameTime((mCurrentTime.QuadPart - mStartTime.QuadPart) / mFrequency);
		gameTime.SetElapsedGameTime((mCurrentTime.QuadPart - mLastTime.QuadPart) / mFrequency);

		mLastTime = mCurrentTime;
	}

}