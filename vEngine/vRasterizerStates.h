#pragma once
#include "vInclude.h"

namespace vEngine {
	class RasterizerStates {
	private:
		RasterizerStates();
		RasterizerStates(const RasterizerStates& rhs);
		RasterizerStates& operator=(const RasterizerStates& rhs);
	public:
		static ID3D11RasterizerState* BackCulling;
		static ID3D11RasterizerState* FrontCulling;
		static ID3D11RasterizerState* DisabledCulling;
		static ID3D11RasterizerState* Wireframe;
	public:
		static void Initialize(ID3D11Device* direct3DDevice);
		static void Release();
	};
}