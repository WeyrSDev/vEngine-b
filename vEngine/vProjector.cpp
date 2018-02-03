#include "vProjector.h"
#include "vEngine.h"
#include "vTime.h"
#include "vVectorHelper.h"
#include "vMatrixHelper.h"

namespace vEngine
{
	RTTI_DEFINITIONS(Projector)

	const float Projector::DefaultFieldOfView = XM_PIDIV4;
	const float Projector::DefaultAspectRatio = 4.0f / 3.0f;
	const float Projector::DefaultNearPlaneDistance = .5f;
	const float Projector::DefaultFarPlaneDistance = 100.0f;

	Projector::Projector(Engine& game)
		: Component(game),
		mFieldOfView(DefaultFieldOfView), mAspectRatio(DefaultAspectRatio), mNearPlaneDistance(DefaultNearPlaneDistance), mFarPlaneDistance(DefaultFarPlaneDistance),
		mPosition(), mDirection(), mUp(), mRight(), mViewMatrix(), mProjectionMatrix()
	{
	}

	Projector::Projector(Engine& game, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
		: Component(game),
		mFieldOfView(fieldOfView), mAspectRatio(aspectRatio), mNearPlaneDistance(nearPlaneDistance), mFarPlaneDistance(farPlaneDistance),
		mPosition(), mDirection(), mUp(), mRight(), mViewMatrix(), mProjectionMatrix()
	{
	}

	Projector::~Projector()
	{
	}

	const DirectX::XMFLOAT3& Projector::Position() const
	{
		return mPosition;
	}

	const DirectX::XMFLOAT3& Projector::Direction() const
	{
		return mDirection;
	}

	const DirectX::XMFLOAT3& Projector::Up() const
	{
		return mUp;
	}

	const DirectX::XMFLOAT3& Projector::Right() const
	{
		return mRight;
	}

	DirectX::XMVECTOR Projector::PositionVector() const
	{
		return XMLoadFloat3(&mPosition);
	}

	DirectX::XMVECTOR Projector::DirectionVector() const
	{
		return XMLoadFloat3(&mDirection);
	}

	DirectX::XMVECTOR Projector::UpVector() const
	{
		return XMLoadFloat3(&mUp);
	}

	DirectX::XMVECTOR Projector::RightVector() const
	{
		return XMLoadFloat3(&mRight);
	}

	float Projector::AspectRatio() const
	{
		return mAspectRatio;
	}

	float Projector::FieldOfView() const
	{
		return mFieldOfView;
	}

	float Projector::NearPlaneDistance() const
	{
		return mNearPlaneDistance;
	}

	float Projector::FarPlaneDistance() const
	{
		return mFarPlaneDistance;
	}

	DirectX::XMMATRIX Projector::ViewMatrix() const
	{
		return XMLoadFloat4x4(&mViewMatrix);
	}

	DirectX::XMMATRIX Projector::ProjectionMatrix() const
	{
		return XMLoadFloat4x4(&mProjectionMatrix);
	}

	DirectX::XMMATRIX Projector::ViewProjectionMatrix() const
	{
		DirectX::XMMATRIX viewMatrix = XMLoadFloat4x4(&mViewMatrix);
		DirectX::XMMATRIX projectionMatrix = XMLoadFloat4x4(&mProjectionMatrix);

		return XMMatrixMultiply(viewMatrix, projectionMatrix);
	}

	void Projector::SetPosition(FLOAT x, FLOAT y, FLOAT z)
	{
		DirectX::XMVECTOR position = XMVectorSet(x, y, z, 1.0f);
		SetPosition(position);
	}

	void Projector::SetPosition(DirectX::FXMVECTOR position)
	{
		XMStoreFloat3(&mPosition, position);
	}

	void Projector::SetPosition(const DirectX::XMFLOAT3& position)
	{
		mPosition = position;
	}

	void Projector::Reset()
	{
		mPosition = Vector3Helper::Zero;
		mDirection = Vector3Helper::Forward;
		mUp = Vector3Helper::Up;
		mRight = Vector3Helper::Right;

		UpdateViewMatrix();
	}

	void Projector::Initialize()
	{
		UpdateProjectionMatrix();
		Reset();
	}

	void Projector::Update(const Time& gameTime)
	{
		UpdateViewMatrix();
	}

	void Projector::UpdateViewMatrix()
	{
		DirectX::XMVECTOR eyePosition = XMLoadFloat3(&mPosition);
		DirectX::XMVECTOR direction = XMLoadFloat3(&mDirection);
		DirectX::XMVECTOR upDirection = XMLoadFloat3(&mUp);

		DirectX::XMMATRIX viewMatrix = XMMatrixLookToRH(eyePosition, direction, upDirection);
		XMStoreFloat4x4(&mViewMatrix, viewMatrix);
	}

	void Projector::UpdateProjectionMatrix()
	{
		DirectX::XMMATRIX projectionMatrix = XMMatrixPerspectiveFovRH(mFieldOfView, mAspectRatio, mNearPlaneDistance, mFarPlaneDistance);
		XMStoreFloat4x4(&mProjectionMatrix, projectionMatrix);
	}

	void Projector::ApplyRotation(DirectX::CXMMATRIX transform)
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

	void Projector::ApplyRotation(const DirectX::XMFLOAT4X4& transform)
	{
		DirectX::XMMATRIX transformMatrix = XMLoadFloat4x4(&transform);
		ApplyRotation(transformMatrix);
	}
}