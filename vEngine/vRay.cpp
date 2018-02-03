#include "vRay.h"


namespace vEngine
{
	Ray::Ray(DirectX::FXMVECTOR position, DirectX::FXMVECTOR direction)
		: mPosition(), mDirection()
	{
		XMStoreFloat3(&mPosition, position);
		XMStoreFloat3(&mDirection, direction);
	}

	Ray::Ray(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& direction)
		: mPosition(position), mDirection(direction)
	{
	}

	const DirectX::XMFLOAT3& Ray::Position() const
	{
		return mPosition;
	}

	const DirectX::XMFLOAT3& Ray::Direction() const
	{
		return mDirection;
	}

	DirectX::XMVECTOR Ray::PositionVector() const
	{
		return XMLoadFloat3(&mPosition);
	}

	DirectX::XMVECTOR Ray::DirectionVector() const
	{
		return XMLoadFloat3(&mDirection);
	}

	void Ray::SetPosition(FLOAT x, FLOAT y, FLOAT z)
	{
		DirectX::XMVECTOR position = XMVectorSet(x, y, z, 1.0f);
		SetPosition(position);
	}

	void Ray::SetPosition(DirectX::FXMVECTOR position)
	{
		XMStoreFloat3(&mPosition, position);
	}

	void Ray::SetPosition(const DirectX::XMFLOAT3& position)
	{
		mPosition = position;
	}

	void Ray::SetDirection(FLOAT x, FLOAT y, FLOAT z)
	{
		DirectX::XMVECTOR direction = XMVectorSet(x, y, z, 0.0f);
		SetDirection(direction);
	}

	void Ray::SetDirection(DirectX::FXMVECTOR direction)
	{
		XMStoreFloat3(&mDirection, direction);
	}

	void Ray::SetDirection(const DirectX::XMFLOAT3& direction)
	{
		mDirection = direction;
	}
}
