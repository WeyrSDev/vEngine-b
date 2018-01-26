#pragma once
#include "vInclude.h"

namespace vEngine {
	class BoundingSphere {
	public:
		BoundingSphere();
		BoundingSphere(FXMVECTOR center, float radius);
		BoundingSphere(const XMFLOAT3& center, float radius);
	public:
		XMFLOAT3& Center();
		float& Radius();
	private:
		XMFLOAT3 mCenter;
		float mRadius;
	};
}
