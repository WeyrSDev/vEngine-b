#pragma once
#include "vInclude.h"

namespace vEngine {
	class BoundingSphere {
	public:
		BoundingSphere();
		BoundingSphere(DirectX::FXMVECTOR center, float radius);
		BoundingSphere(const DirectX::XMFLOAT3& center, float radius);
	public:
		DirectX::XMFLOAT3& Center();
		float& Radius();
	private:
		DirectX::XMFLOAT3 mCenter;
		float mRadius;
	};
}
