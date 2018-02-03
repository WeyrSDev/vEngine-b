#include "vSpotLight.h"
#include "vVectorHelper.h"

namespace vEngine {
	RTTI_DEFINITIONS(SpotLight)
	const float SpotLight::DefaultInnerAngle = 0.75f;
	const float SpotLight::DefaultOuterAngle = 0.25f;
	SpotLight::SpotLight(Engine& game)
		: PointLight(game), mInnerAngle(DefaultInnerAngle), mOuterAngle(DefaultOuterAngle),
		mDirection(Vector3Helper::Forward), mUp(Vector3Helper::Up), mRight(Vector3Helper::Right)
	{
	}

	SpotLight::~SpotLight()
	{
	}

	const DirectX::XMFLOAT3& SpotLight::Direction() const
	{
		return mDirection;
	}

	const DirectX::XMFLOAT3& SpotLight::Up() const
	{
		return mUp;
	}

	const DirectX::XMFLOAT3& SpotLight::Right() const
	{
		return mRight;
	}

	DirectX::XMVECTOR SpotLight::DirectionVector() const
	{
		return XMLoadFloat3(&mDirection);
	}

	DirectX::XMVECTOR SpotLight::UpVector() const
	{
		return XMLoadFloat3(&mUp);
	}

	DirectX::XMVECTOR SpotLight::RightVector() const
	{
		return XMLoadFloat3(&mRight);
	}

	float SpotLight::InnerAngle()
	{
		return mInnerAngle;
	}

	void SpotLight::SetInnerAngle(float value)
	{
		mInnerAngle = value;
	}

	float SpotLight::OuterAngle()
	{
		return mOuterAngle;
	}

	void SpotLight::SetOuterAngle(float value)
	{
		mOuterAngle = value;
	}

	void SpotLight::ApplyRotation(DirectX::CXMMATRIX transform)
	{
		DirectX::XMVECTOR direction = XMLoadFloat3(&mDirection);
		DirectX::XMVECTOR up = XMLoadFloat3(&mUp);

		direction = XMVector3TransformNormal(direction, transform);
		direction = XMVector3Normalize(direction);

		up = XMVector3TransformNormal(up, transform);
		up = XMVector3Normalize(up);

		DirectX::XMVECTOR right = XMVector3Cross(direction, up);
		up = XMVector3Cross(right, direction);

		XMStoreFloat3(&mDirection, direction);
		XMStoreFloat3(&mUp, up);
		XMStoreFloat3(&mRight, right);
	}

	void SpotLight::ApplyRotation(const DirectX::XMFLOAT4X4& transform)
	{
		DirectX::XMMATRIX transformMatrix = XMLoadFloat4x4(&transform);
		ApplyRotation(transformMatrix);
	}
}