#include "vTime.h"


namespace vEngine {
	Time::Time()
		: mTotalGameTime(0.0), mElapsedGameTime(0.0)
	{
	}

	double Time::TotalGameTime() const
	{
		return mTotalGameTime;
	}

	void Time::SetTotalGameTime(double totalGameTime)
	{
		mTotalGameTime = totalGameTime;
	}

	double Time::ElapsedGameTime() const
	{
		return mElapsedGameTime;
	}

	void Time::SetElapsedGameTime(double elapsedGameTime)
	{
		mElapsedGameTime = elapsedGameTime;
	}

}