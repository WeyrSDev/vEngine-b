#include "vDirectionalLight.h"
#include "vVectorHelper.h"

namespace vEngine {
	RTTI_DEFINITIONS(DirectionalLight)

	DirectionalLight::DirectionalLight(Engine& game)
		: Light(game), mDirection(Vector3Helper::Forward), mUp(Vector3Helper::Up), mRight(Vector3Helper::Right)
	{
	}

	DirectionalLight::~DirectionalLight()
	{
	}

	const DirectX::XMFLOAT3& DirectionalLight::Direction() const
	{
		return mDirection;
	}

	const DirectX::XMFLOAT3& DirectionalLight::Up() const
	{
		return mUp;
	}

	const DirectX::XMFLOAT3& DirectionalLight::Right() const
	{
		return mRight;
	}

	DirectX::XMVECTOR DirectionalLight::DirectionVector() const
	{
		return XMLoadFloat3(&mDirection);
	}

	DirectX::XMVECTOR DirectionalLight::UpVector() const
	{
		return XMLoadFloat3(&mUp);
	}

	DirectX::XMVECTOR DirectionalLight::RightVector() const
	{
		return XMLoadFloat3(&mRight);
	}

	void DirectionalLight::ApplyRotation(DirectX::CXMMATRIX transform)
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

	void DirectionalLight::ApplyRotation(const DirectX::XMFLOAT4X4& transform)
	{
		DirectX::XMMATRIX transformMatrix = XMLoadFloat4x4(&transform);
		ApplyRotation(transformMatrix);
	}
}