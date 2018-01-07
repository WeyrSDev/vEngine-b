#include "vClock.h"
#include "vTime.h"


namespace vEngine {
	Clock::Clock()
		: m_StartTime(), m_CurrentTime(), m_LastTime(), m_Frequency()
	{
		m_Frequency = GetFrequency();
		Reset();
	}

	const LARGE_INTEGER& Clock::StartTime() const
	{
		return m_StartTime;
	}

	const LARGE_INTEGER& Clock::CurrentTime() const
	{
		return m_CurrentTime;
	}

	const LARGE_INTEGER& Clock::LastTime() const
	{
		return m_LastTime;
	}

	void Clock::Reset()
	{
		GetTime(m_StartTime);
		m_CurrentTime = m_StartTime;
		m_LastTime = m_CurrentTime;
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

	void Clock::GetTime(LARGE_INTEGER& p_Time) const
	{
		QueryPerformanceCounter(&p_Time);
	}

	void Clock::UpdateEngineTime(Time& p_EngineTime)
	{
		GetTime(m_CurrentTime);
		p_EngineTime.SetTotalEngineTime((m_CurrentTime.QuadPart - m_StartTime.QuadPart) / m_Frequency);
		p_EngineTime.SetElapsedEngineTime((m_CurrentTime.QuadPart - m_LastTime.QuadPart) / m_Frequency);

		m_LastTime = m_CurrentTime;
	}
}