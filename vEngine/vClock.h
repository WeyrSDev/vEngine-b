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
		Clock(const Clock& p_Rhs);
		Clock& operator=(const Clock& p_Rhs);
	public:
		const LARGE_INTEGER& StartTime() const;
		const LARGE_INTEGER& CurrentTime() const;
		const LARGE_INTEGER& LastTime() const;
		void Reset();
		double GetFrequency() const;
		void GetTime(LARGE_INTEGER& p_Time) const;
		void UpdateEngineTime(Time& p_EngineTime);
	private:
		LARGE_INTEGER m_StartTime;
		LARGE_INTEGER m_CurrentTime;
		LARGE_INTEGER m_LastTime;
		double m_Frequency;
	};
}