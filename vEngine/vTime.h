#pragma once

namespace vEngine {
	class Time
	{
	public:
		Time();
	public:
		double TotalGameTime() const;
		void SetTotalGameTime(double totalGameTime);
		double ElapsedGameTime() const;
		void SetElapsedGameTime(double elapsedGameTime);
	private:
		double mTotalGameTime;
		double mElapsedGameTime;
	};
}