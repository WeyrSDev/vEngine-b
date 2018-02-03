#include "vCamera.h"
#include "vEngine.h"
#include "vTime.h"
#include "vMatrixHelper.h"
#include "vVectorHelper.h"


namespace vEngine {
	RTTI_DEFINITIONS(Camera)
	const float Camera::DefaultFieldOfView = XM_PIDIV4;
	const float Camera::DefaultNearPlaneDistance = 0.01f;
	const float Camera::DefaultFarPlaneDistance = 1000.0f;
	Camera::Camera(Engine& game)
		: Component(game),
		mFieldOfView(DefaultFieldOfView), mAspectRatio(game.AspectRatio()), mNearPlaneDistance(DefaultNearPlaneDistance), mFarPlaneDistance(DefaultFarPlaneDistance),
		mPosition(), mDirection(), mUp(), mRight(), mViewMatrix(), mProjectionMatrix()
	{
	}

	Camera::Camera(Engine& game, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
		: Component(game),
		mFieldOfView(fieldOfView), mAspectRatio(aspectRatio), mNearPlaneDistance(nearPlaneDistance), mFarPlaneDistance(farPlaneDistance),
		mPosition(), mDirection(), mUp(), mRight(), mViewMatrix(), mProjectionMatrix()
	{
	}

	Camera::Camera(Engine& game, float nearPlaneDistance, float farPlaneDistance) :
		Component(game),
		mNearPlaneDistance(nearPlaneDistance), mFarPlaneDistance(farPlaneDistance),
		mPosition(), mDirection(), mUp(), mRight(), mViewMatrix(), mProjectionMatrix()
	{
	}


	Camera::~Camera()
	{
	}

	const DirectX::XMFLOAT3& Camera::Position() const
	{
		return mPosition;
	}

	const DirectX::XMFLOAT3& Camera::Direction() const
	{
		return mDirection;
	}

	const DirectX::XMFLOAT3& Camera::Up() const
	{
		return mUp;
	}

	const DirectX::XMFLOAT3& Camera::Right() const
	{
		return mRight;
	}

	DirectX::XMVECTOR Camera::PositionVector() const
	{
		return XMLoadFloat3(&mPosition);
	}

	DirectX::XMVECTOR Camera::DirectionVector() const
	{
		return XMLoadFloat3(&mDirection);
	}

	DirectX::XMVECTOR Camera::UpVector() const
	{
		return XMLoadFloat3(&mUp);
	}

	DirectX::XMVECTOR Camera::RightVector() const
	{
		return XMLoadFloat3(&mRight);
	}

	float Camera::AspectRatio() const
	{
		return mAspectRatio;
	}

	float Camera::FieldOfView() const
	{
		return mFieldOfView;
	}

	float Camera::NearPlaneDistance() const
	{
		return mNearPlaneDistance;
	}

	float Camera::FarPlaneDistance() const
	{
		return mFarPlaneDistance;
	}

	DirectX::XMMATRIX Camera::ViewMatrix() const
	{
		return XMLoadFloat4x4(&mViewMatrix);
	}

	DirectX::XMMATRIX Camera::ProjectionMatrix() const
	{
		return XMLoadFloat4x4(&mProjectionMatrix);
	}

	DirectX::XMMATRIX Camera::ViewProjectionMatrix() const
	{
		DirectX::XMMATRIX viewMatrix = XMLoadFloat4x4(&mViewMatrix);
		DirectX::XMMATRIX projectionMatrix = XMLoadFloat4x4(&mProjectionMatrix);

		return XMMatrixMultiply(viewMatrix, projectionMatrix);
	}

	void Camera::SetPosition(FLOAT x, FLOAT y, FLOAT z)
	{
		DirectX::XMVECTOR position = XMVectorSet(x, y, z, 1.0f);
		SetPosition(position);
	}

	void Camera::SetPosition(DirectX::FXMVECTOR position)
	{
		XMStoreFloat3(&mPosition, position);
	}

	void Camera::SetPosition(const DirectX::XMFLOAT3& position)
	{
		mPosition = position;
	}

	void Camera::Reset()
	{
		mPosition = Vector3Helper::Zero;
		mDirection = Vector3Helper::Forward;
		mUp = Vector3Helper::Up;
		mRight = Vector3Helper::Right;

		UpdateViewMatrix();
	}

	void Camera::Initialize()
	{
		UpdateProjectionMatrix();
		Reset();
	}

	void Camera::Update(const Time& gameTime)
	{
		UpdateViewMatrix();
	}

	void Camera::UpdateViewMatrix()
	{
		DirectX::XMVECTOR eyePosition = XMLoadFloat3(&mPosition);
		DirectX::XMVECTOR direction = XMLoadFloat3(&mDirection);
		DirectX::XMVECTOR upDirection = XMLoadFloat3(&mUp);

		DirectX::XMMATRIX viewMatrix = XMMatrixLookToRH(eyePosition, direction, upDirection);
		XMStoreFloat4x4(&mViewMatrix, viewMatrix);
	}

	void Camera::UpdateProjectionMatrix()
	{
		DirectX::XMMATRIX projectionMatrix = XMMatrixPerspectiveFovRH(mFieldOfView, mAspectRatio, mNearPlaneDistance, mFarPlaneDistance);
		XMStoreFloat4x4(&mProjectionMatrix, projectionMatrix);
	}

	void Camera::ApplyRotation(DirectX::CXMMATRIX transform)
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

	void Camera::ApplyRotation(const DirectX::XMFLOAT4X4& transform)
	{
		DirectX::XMMATRIX transformMatrix = XMLoadFloat4x4(&transform);
		ApplyRotation(transformMatrix);
	}

}