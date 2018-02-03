#include "vBoundingSphere.h"

namespace vEngine
{
	BoundingSphere::BoundingSphere()
		: mCenter(0.0f, 0.0f, 0.0f), mRadius(0.0f)
	{
	}

	BoundingSphere::BoundingSphere(DirectX::FXMVECTOR center, float radius)
		: mCenter(), mRadius(radius)
	{
		XMStoreFloat3(&mCenter, center);
	}

	BoundingSphere::BoundingSphere(const DirectX::XMFLOAT3& center, float radius)
		: mCenter(center), mRadius(radius)
	{
	}

	DirectX::XMFLOAT3& BoundingSphere::Center()
	{
		return mCenter;
	}

	float& BoundingSphere::Radius()
	{
		return mRadius;
	}
}
