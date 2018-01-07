#pragma once

namespace vEngine {
	class Time
	{
	public:
		Time();
	public:
		double TotalEngineTime() const;
		void SetTotalEngineTime(double p_TotalEngineTime);
		double ElapsedEngineTime() const;
		void SetElapsedEngineTime(double p_ElapsedEngineTime);
	private:
		double m_TotalEngineTime;
		double m_ElapsedEngineTime;
	};
}