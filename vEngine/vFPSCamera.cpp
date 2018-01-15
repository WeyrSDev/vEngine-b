#include "vFPSCamera.h"
#include "vEngine.h"
#include "vTime.h"
#include "vKeyboard.h"
#include "vMouse.h"
#include "vEnums.h"
#include "vStructs.h"
#include "vVectorHelper.h"

namespace vEngine {
	RTTI_DEFINITIONS(FPSCamera)
	const float FPSCamera::DefaultRotationRate = XMConvertToRadians(1.0f);
	const float FPSCamera::DefaultMovementRate = 10.0f;
	const float FPSCamera::DefaultMouseSensitivity = 100.0f;
	FPSCamera::FPSCamera(Engine& game)
		: Camera(game), mKeyboard(nullptr), mMouse(nullptr),
		mMouseSensitivity(DefaultMouseSensitivity), mRotationRate(DefaultRotationRate), mMovementRate(DefaultMovementRate)
	{
	}

	FPSCamera::FPSCamera(Engine& game, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
		: Camera(game, fieldOfView, aspectRatio, nearPlaneDistance, farPlaneDistance), mKeyboard(nullptr), mMouse(nullptr),
		mMouseSensitivity(DefaultMouseSensitivity), mRotationRate(DefaultRotationRate), mMovementRate(DefaultMovementRate)

	{
	}

	FPSCamera::~FPSCamera()
	{
		mKeyboard = nullptr;
		mMouse = nullptr;
	}

	const Keyboard& FPSCamera::GetKeyboard() const
	{
		return *mKeyboard;
	}

	void FPSCamera::SetKeyboard(Keyboard& keyboard)
	{
		mKeyboard = &keyboard;
	}

	const Mouse& FPSCamera::GetMouse() const
	{
		return *mMouse;
	}

	void FPSCamera::SetMouse(Mouse& mouse)
	{
		mMouse = &mouse;
	}

	float& FPSCamera::MouseSensitivity()
	{
		return mMouseSensitivity;
	}


	float& FPSCamera::RotationRate()
	{
		return mRotationRate;
	}

	float& FPSCamera::MovementRate()
	{
		return mMovementRate;
	}

	void FPSCamera::Initialize()
	{
		mKeyboard = (Keyboard*)mGame->Services().GetService(Keyboard::TypeIdClass());
		mMouse = (Mouse*)mGame->Services().GetService(Mouse::TypeIdClass());

		Camera::Initialize();
	}

	void FPSCamera::Update(const Time& gameTime)
	{
		XMFLOAT2 movementAmount = Vector2Helper::Zero;
		if (mKeyboard != nullptr)
		{
			if (mKeyboard->IsKeyDown(DIK_W))
			{
				movementAmount.y = 1.0f;
			}

			if (mKeyboard->IsKeyDown(DIK_S))
			{
				movementAmount.y = -1.0f;
			}

			if (mKeyboard->IsKeyDown(DIK_A))
			{
				movementAmount.x = -1.0f;
			}

			if (mKeyboard->IsKeyDown(DIK_D))
			{
				movementAmount.x = 1.0f;
			}
		}

		XMFLOAT2 rotationAmount = Vector2Helper::Zero;
		if ((mMouse != nullptr) && (mMouse->IsButtonHeldDown(MouseButtonsLeft)))
		{
			LPDIMOUSESTATE mouseState = mMouse->CurrentState();
			rotationAmount.x = -mouseState->lX * mMouseSensitivity;
			rotationAmount.y = -mouseState->lY * mMouseSensitivity;
		}

		float elapsedTime = (float)gameTime.ElapsedGameTime();
		XMVECTOR rotationVector = XMLoadFloat2(&rotationAmount) * mRotationRate * elapsedTime;
		XMVECTOR right = XMLoadFloat3(&mRight);

		XMMATRIX pitchMatrix = XMMatrixRotationAxis(right, XMVectorGetY(rotationVector));
		XMMATRIX yawMatrix = XMMatrixRotationY(XMVectorGetX(rotationVector));

		ApplyRotation(XMMatrixMultiply(pitchMatrix, yawMatrix));

		XMVECTOR position = XMLoadFloat3(&mPosition);
		XMVECTOR movement = XMLoadFloat2(&movementAmount) * mMovementRate * elapsedTime;

		XMVECTOR strafe = right * XMVectorGetX(movement);
		position += strafe;

		XMVECTOR forward = XMLoadFloat3(&mDirection) * XMVectorGetY(movement);
		position += forward;

		XMStoreFloat3(&mPosition, position);

		Camera::Update(gameTime);
	}
}