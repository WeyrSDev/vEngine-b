#pragma once
#include "vInclude.h"

namespace vEngine {
	class BlendStates {
	private:
		BlendStates();
		BlendStates(const BlendStates& rhs);
		BlendStates& operator=(const BlendStates& rhs);
	public:
		static ID3D11BlendState* MultiplicativeBlending;
		static ID3D11BlendState* AlphaBlending;
	public:
		static void Initialize(ID3D11Device* direct3DDevice);
		static void Release();
	};
}