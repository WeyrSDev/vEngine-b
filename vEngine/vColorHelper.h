#pragma once
#include "vInclude.h"

namespace vEngine {
	class ColorHelper
	{
	private:
		ColorHelper();
		ColorHelper(const ColorHelper& rhs);
		ColorHelper& operator=(const ColorHelper& rhs);
	public:
		static const DirectX::XMVECTORF32 Black;
		static const DirectX::XMVECTORF32 White;
		static const DirectX::XMVECTORF32 Red;
		static const DirectX::XMVECTORF32 Green;
		static const DirectX::XMVECTORF32 Blue;
		static const DirectX::XMVECTORF32 Yellow;
		static const DirectX::XMVECTORF32 BlueGreen;
		static const DirectX::XMVECTORF32 Purple;
		static const DirectX::XMVECTORF32 CornflowerBlue;
		static const DirectX::XMVECTORF32 Wheat;
		static const DirectX::XMVECTORF32 LightGray;
	public:
		static DirectX::XMFLOAT4 RandomColor();
	private:
		static std::random_device sDevice;
		static std::default_random_engine sGenerator;
		static std::uniform_real_distribution<float>sDistribution;
	};
}