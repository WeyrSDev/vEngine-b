#include "vTime.h"


namespace vEngine {
	Time::Time()
		: m_TotalEngineTime(0.0), m_ElapsedEngineTime(0.0)
	{
	}

	double Time::TotalEngineTime() const
	{
		return m_TotalEngineTime;
	}

	void Time::SetTotalEngineTime(double p_TotalEngineTime)
	{
		m_TotalEngineTime = p_TotalEngineTime;
	}

	double Time::ElapsedEngineTime() const
	{
		return m_ElapsedEngineTime;
	}

	void Time::SetElapsedEngineTime(double p_ElapsedEngineTime)
	{
		m_ElapsedEngineTime = p_ElapsedEngineTime;
	}
}