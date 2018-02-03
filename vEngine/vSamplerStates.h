#pragma once
#include "vInclude.h"


namespace vEngine {
	class SamplerStates {
	private:
		SamplerStates();
		SamplerStates(const SamplerStates& rhs);
		SamplerStates& operator=(const SamplerStates& rhs);
	public:
		static ID3D11SamplerState* TrilinearWrap;
		static ID3D11SamplerState* TrilinearMirror;
		static ID3D11SamplerState* TrilinearClamp;
		static ID3D11SamplerState* TrilinerBorder;
		static DirectX::XMVECTORF32 BorderColor;
	public:
		static void Initialize(ID3D11Device* direct3DDevice);
		static void Release();
	};
}