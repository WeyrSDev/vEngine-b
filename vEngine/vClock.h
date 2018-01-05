#pragma once
#include <windows.h>
#include <exception>

namespace vEngine {
	class Time;
	class Clock
	{
	public:
		Clock();
	private:
		Clock(const Clock& rhs);
		Clock& operator=(const Clock& rhs);
	public:
		const LARGE_INTEGER& StartTime() const;
		const LARGE_INTEGER& CurrentTime() const;
		const LARGE_INTEGER& LastTime() const;
		void Reset();
		double GetFrequency() const;
		void GetTime(LARGE_INTEGER& time) const;
		void UpdateGameTime(Time& gameTime);
	private:
		LARGE_INTEGER mStartTime;
		LARGE_INTEGER mCurrentTime;
		LARGE_INTEGER mLastTime;
		double mFrequency;
	};
}